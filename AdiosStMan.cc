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
#include "AdiosStManColumn.h"


namespace casa { 

	AdiosStMan::AdiosStMan ()
		:DataManager(),
		itsAdiosFile(0),
		itsAdiosReadFile(0),
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
		mpiRank(that.mpiRank),
		mpiSize(that.mpiSize),
		isMpiInitInternal(false)
	{
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


	const int64_t AdiosStMan::getAdiosFile(){ 
		return itsAdiosFile;
	}

	ADIOS_FILE* AdiosStMan::getAdiosReadFile(){
		return itsAdiosReadFile;
	}

	void AdiosStMan::create (uInt aNrRows)
	{

		itsNrRows = aNrRows;

		adios_init_noxml(MPI_COMM_WORLD);

		adios_declare_group(&itsAdiosGroup, "casatable", "", adios_flag_no);
		adios_select_method(itsAdiosGroup, "POSIX", "", "");

		itsAdiosGroupsize = 0;

		// loop for columns
		for (int i=0; i<ncolumn(); i++){
			string columnName = itsColumnPtrBlk[i]->columnName();
			itsColumnPtrBlk[i]->initAdiosWriteIDs(itsNrRows);

			// if scalar column
			if (itsColumnPtrBlk[i]->getShapeColumn().nelements() == 0){   
				// loop for rows
				for (int j=0; j<itsNrRows; j++){
					stringstream NrRows, RowID;
					NrRows << itsNrRows;
					RowID << j;
					int64_t writeID = adios_define_var(itsAdiosGroup, columnName.c_str(), "", itsColumnPtrBlk[i]->getAdiosDataType(), "1", NrRows.str().c_str(), RowID.str().c_str() );
					itsColumnPtrBlk[i]->putAdiosWriteIDs(j, writeID);
				}
				itsAdiosGroupsize = itsAdiosGroupsize + itsNrRows * itsColumnPtrBlk[i]->getDataTypeSize();
			}


			// if array column
			else{
				string columnShape = itsColumnPtrBlk[i]->getShapeColumn().toString();
				columnShape = columnShape.substr(1, columnShape.length()-2);

				// loop for rows
				for (int j=0; j<itsNrRows; j++){
					stringstream NrRows, RowID;
					NrRows << itsNrRows;
					RowID << j;
					string dimensions = "1," + columnShape;
					string global_dimensions = NrRows.str() + "," + columnShape;
					string local_offsets = RowID.str(); 
					for (int k=0; k<itsColumnPtrBlk[i]->getShapeColumn().nelements(); k++){
						local_offsets += ",0";
					}
					int64_t writeID = adios_define_var(itsAdiosGroup, columnName.c_str(), "", itsColumnPtrBlk[i]->getAdiosDataType(), dimensions.c_str(), global_dimensions.c_str(), local_offsets.c_str());
					itsColumnPtrBlk[i]->putAdiosWriteIDs(j, writeID);
				}
				itsAdiosGroupsize = itsAdiosGroupsize + itsNrRows * itsColumnPtrBlk[i]->getDataTypeSize() * itsColumnPtrBlk[i]->getShapeColumn().product();
			}
		}

		itsAdiosBufsize = itsAdiosGroupsize * 1.05 / 1000000;
		if(itsAdiosBufsize < 100) itsAdiosBufsize = 100;
		adios_allocate_buffer(ADIOS_BUFFER_ALLOC_NOW, itsAdiosBufsize);

		adios_open(&itsAdiosFile, "casatable", fileName().c_str(), "w", MPI_COMM_WORLD);

		adios_group_size(itsAdiosFile, itsAdiosGroupsize, &itsAdiosTotalsize);

	} // end of void AdiosStMan::create (uInt aNrRows)

	void AdiosStMan::open (uInt aRowNr, AipsIO& ios){
		adios_read_init_method (ADIOS_READ_METHOD_BP, MPI_COMM_WORLD, "verbose=3");
		itsAdiosReadFile = adios_read_open (fileName().c_str(), ADIOS_READ_METHOD_BP, MPI_COMM_WORLD, ADIOS_LOCKMODE_NONE, 0);

		for (int i=0; i<ncolumn(); i++){
			itsColumnPtrBlk[i]->setAdiosReadFile(itsAdiosReadFile);
		}
	}

	void AdiosStMan::deleteManager()
	{

	}

	DataManagerColumn* AdiosStMan::makeScalarColumn (const String& name, int aDataType,	const String& dataTypeId){
		makeDirArrColumn(name, aDataType, dataTypeId);
	}

	DataManagerColumn* AdiosStMan::makeDirArrColumn (const String& name, int aDataType,	const String& dataTypeId){
		if (ncolumn() >= itsColumnPtrBlk.nelements()) {
			itsColumnPtrBlk.resize (itsColumnPtrBlk.nelements() + 32);
		}
		AdiosStManColumn* aColumn = new AdiosStManColumn (this, aDataType, ncolumn());
		aColumn->setColumnName(name);
		itsColumnPtrBlk[ncolumn()] = aColumn;
		return aColumn;
	}

	DataManagerColumn* AdiosStMan::makeIndArrColumn (const String& name, int aDataType,	const String& dataTypeId){
		cout << "AdiosStMan warning: Support of indirect arrays is currently under development, and it may not behave as expected!" << endl;
		makeDirArrColumn(name, aDataType, dataTypeId);
	}

	void AdiosStMan::resync (uInt aNrRows){
	}

	Bool AdiosStMan::flush (AipsIO& ios, Bool doFsync){
	}

	void register_adiosstman(){
		DataManager::registerCtor ("AdiosStMan", AdiosStMan::makeObject);
	}
} // end of namespace casa

