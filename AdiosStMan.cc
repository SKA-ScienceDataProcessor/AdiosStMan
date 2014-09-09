//    AdiosStMan.cc: Storage Manager for general CASA tables using ADIOS
//    as the underlying IO & storage library
//
//    (c) University of Western Australia
//    International Centre of Radio Astronomy Research
//    M468, 35 Stirling Hwy
//    Crawley, Perth WA 6009
//    Australia
//
//    This library is free software: you can redistribute it and/or
//    modify it under the terms of the GNU General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//   
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//   
//    You should have received a copy of the GNU General Public License along
//    with this library. If not, see <http://www.gnu.org/licenses/>.
//
//    Any bugs, questions, concerns and/or suggestions please email to
//    jason.wang@icrar.org

#include <casa/IO/AipsIO.h>
#include "AdiosStMan.h"
#include "AdiosStManColumnA.h"


namespace casa { 

	AdiosStMan::AdiosStMan ()
		:DataManager(),
		itsAdiosFile(0),
		itsAdiosReadFile(0),
		itsNrAdiosFiles(0),
		itsMpiComm(MPI_COMM_WORLD),
		isAdiosOpened(false),
		itsNrColsSlave(0),
		itsStManColumnType('A'),
		isMpiInitInternal(false)
	{
		int isMpiInitialized;
		MPI_Initialized(&isMpiInitialized);
		if(!isMpiInitialized){
			MPI_Init(0,0);
			isMpiInitInternal = true;
		}
		MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
		MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	}


	AdiosStMan::AdiosStMan (const AdiosStMan& that)
		:DataManager(),
		itsAdiosFile(0),
		itsAdiosReadFile(0),
		itsNrAdiosFiles(0),
		itsMpiComm(MPI_COMM_WORLD),
		isAdiosOpened(false),
		itsNrColsSlave(0),
		itsStManColumnType('A'),
		isMpiInitInternal(false)
	{
		MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
		MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	}


	DataManager* AdiosStMan::makeObject (const casa::String& aDataManType, const casa::Record& spec){
		return new AdiosStMan();
	}



	AdiosStMan::~AdiosStMan ()
	{
		if(itsAdiosFile){
			adios_close(itsAdiosFile);
			adios_finalize(mpiRank);
		}

		if(itsAdiosReadFile){
			adios_read_close(itsAdiosReadFile);
			MPI_Barrier(MPI_COMM_WORLD);
			adios_read_finalize_method(ADIOS_READ_METHOD_BP);
		}

		int isMpiInitialized;
		MPI_Initialized(&isMpiInitialized);
		if(isMpiInitInternal && isMpiInitialized){
			MPI_Finalize();
		}
	}


	DataManager* AdiosStMan::clone() const
	{
		return new AdiosStMan (*this);
	}

	String AdiosStMan::dataManagerType() const
	{
		return "AdiosStMan";
	}

	int64_t AdiosStMan::getAdiosGroup(){ 
		return itsAdiosGroup;
	}

	int64_t AdiosStMan::getAdiosFile(){ 
		return itsAdiosFile;
	}

	ADIOS_FILE* AdiosStMan::getAdiosReadFile(){
		return itsAdiosReadFile;
	}

	void AdiosStMan::addRow (uInt aNrRows){


	}

	void AdiosStMan::adiosOpen(){
		if(!isAdiosOpened){

			string itsFileName;
			int itsFileNameLen;

			if(mpiRank == 0){
				itsFileName = fileName();
				itsFileNameLen = itsFileName.length();
			}

			// broadcast the length of the filename string for allocating 
			// memory on slave ranks
			MPI_Bcast(&itsFileNameLen, 1, MPI_INT, 0, itsMpiComm);

			char *itsFileNameChar = new char [itsFileNameLen + 1];
			sprintf(itsFileNameChar, itsFileName.c_str());

			// broadcast the filename string from the master to slaves.
			MPI_Bcast(itsFileNameChar, itsFileNameLen + 1, MPI_CHAR, 0, itsMpiComm);

			adios_open(&itsAdiosFile, "casatable", itsFileNameChar, "w", itsMpiComm);

			delete [] itsFileNameChar;

			adios_group_size(itsAdiosFile, itsAdiosGroupsize, &itsAdiosTotalsize);

			isAdiosOpened = true;
		}
	}

	void AdiosStMan::create (uInt aNrRows)
	{
		itsNrRows = aNrRows;

		adios_init_noxml(itsMpiComm);

		adios_declare_group(&itsAdiosGroup, "casatable", "", adios_flag_no);
		adios_select_method(itsAdiosGroup, "POSIX", "", "");

		itsAdiosGroupsize = 0;


		uInt NrCols = ncolumn();
		MPI_Bcast(&NrCols, 1, MPI_UNSIGNED, 0, itsMpiComm);

		for (uInt i=0; i<NrCols; i++){
			itsColumnPtrBlk[i]->initAdiosWrite(aNrRows);
		}


		for (uInt i=0; i<NrCols; i++){
			// if scalar column
			if (itsColumnPtrBlk[i]->getShapeColumn().nelements() == 0){   
				itsAdiosGroupsize = itsAdiosGroupsize + aNrRows * itsColumnPtrBlk[i]->getDataTypeSize();
			}
			// if array column
			else{
				itsAdiosGroupsize = itsAdiosGroupsize + aNrRows * itsColumnPtrBlk[i]->getDataTypeSize() * itsColumnPtrBlk[i]->getShapeColumn().product();
			}
		}

		itsAdiosBufsize = itsAdiosGroupsize * 3 / 1000000;
		if(itsAdiosBufsize < 100) itsAdiosBufsize = 100;
		adios_allocate_buffer(ADIOS_BUFFER_ALLOC_NOW, itsAdiosBufsize);


	} // end of void AdiosStMan::create (uInt aNrRows)

	void AdiosStMan::open (uInt aNrRows, AipsIO& ios){

		itsNrRows = aNrRows;

		adios_read_init_method (ADIOS_READ_METHOD_BP, MPI_COMM_WORLD, "verbose=3");
		itsAdiosReadFile = adios_read_open (fileName().c_str(), ADIOS_READ_METHOD_BP, MPI_COMM_WORLD, ADIOS_LOCKMODE_NONE, 0);

		if(itsAdiosReadFile){
			for (int i=0; i<ncolumn(); i++){
				itsColumnPtrBlk[i]->initAdiosRead();
			}
		}
		else{
			cout << "AdiosStMan : Couldn't find ADIOS file. Creating new file." << endl;
			create(aNrRows);
		}


	}

	void AdiosStMan::deleteManager(){
	}

	AdiosStManColumn* AdiosStMan::makeScalarColumnSlave (const String& name, int aDataType){
		return makeDirArrColumnSlave(name, aDataType);
	}

	AdiosStManColumn* AdiosStMan::makeDirArrColumnSlave (const String& name, int aDataType){
		if (itsNrColsSlave >= itsColumnPtrBlk.nelements()) {
			itsColumnPtrBlk.resize (itsColumnPtrBlk.nelements() + 32);
		}
		AdiosStManColumnA* aColumn = new AdiosStManColumnA (this, aDataType, itsNrColsSlave);
		aColumn->setColumnName(name);
		itsColumnPtrBlk[itsNrColsSlave] = aColumn;
		itsNrColsSlave++;
		return aColumn;
	}

	AdiosStManColumn* AdiosStMan::makeIndArrColumnSlave (const String& name, int aDataType){
		cout << "AdiosStMan warning: Support of indirect arrays is currently under development, and it may not behave as expected!" << endl;
		return makeDirArrColumnSlave(name, aDataType);
	}


	
	DataManagerColumn* AdiosStMan::makeScalarColumn (const String& name, int aDataType,	const String& dataTypeId){
		return makeDirArrColumn(name, aDataType, dataTypeId);
	}

	DataManagerColumn* AdiosStMan::makeDirArrColumn (const String& name, int aDataType,	const String& dataTypeId){
		if (ncolumn() >= itsColumnPtrBlk.nelements()) {
			itsColumnPtrBlk.resize (itsColumnPtrBlk.nelements() + 32);
		}

		AdiosStManColumnA* aColumn;

		switch (itsStManColumnType){
			case 'A':
				aColumn = new AdiosStManColumnA (this, aDataType, ncolumn());
				break;
			default:
				aColumn = new AdiosStManColumnA (this, aDataType, ncolumn());
				break;
		}

		aColumn->setColumnName(name);
		itsColumnPtrBlk[ncolumn()] = aColumn;
		return aColumn;
	}

	DataManagerColumn* AdiosStMan::makeIndArrColumn (const String& name, int aDataType,	const String& dataTypeId){
		cout << "AdiosStMan warning: Support of indirect arrays is currently under development, and it may not behave as expected!" << endl;
		return makeDirArrColumn(name, aDataType, dataTypeId);
	}
	
	uInt AdiosStMan::getNrRows(){
		return itsNrRows;
	}

	void AdiosStMan::resync (uInt aNrRows){
	}

	Bool AdiosStMan::flush (AipsIO& ios, Bool doFsync){
		return true;
	}

	void register_adiosstman(){
		DataManager::registerCtor ("AdiosStMan", AdiosStMan::makeObject);
	}
} // end of namespace casa

