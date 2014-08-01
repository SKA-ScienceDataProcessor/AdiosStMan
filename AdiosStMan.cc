//# AdiosStMan.cc: The Standard Storage Manager
//# Copyright (C) 2000
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id: AdiosStMan.cc 20551 2009-03-25 00:11:33Z Malte.Marquarding $


#include "AdiosStMan.h"
#include "AdiosStManColumn.h"


namespace casa { //# NAMESPACE CASA - BEGIN



	AdiosStMan::AdiosStMan ()
		:DataManager(),
		itsAdiosFile(0),
		isMpiInitInternal(true)
	{
		MPI_Init(0,0);
		MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
		MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

	}

	AdiosStMan::AdiosStMan (int rank, int size)
		:DataManager(),
		itsAdiosFile(0),
		isMpiInitInternal(false)
	{
		mpiRank = rank;
		mpiSize = size;
	}

	AdiosStMan::AdiosStMan (const AdiosStMan& that)
		:DataManager(),
		itsAdiosFile(0),
		isMpiInitInternal(false)
	{
	}

	AdiosStMan::~AdiosStMan ()
	{
		if(itsAdiosFile){
			adios_close(itsAdiosFile);
			adios_finalize(mpiRank);
		}
		if(isMpiInitInternal){
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

	int64_t AdiosStMan::getAdiosFile(){ 
		return itsAdiosFile;
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
					string dimensions = "1, " + columnShape;
					string global_dimensions = NrRows.str() + ", " + columnShape;
					string local_offsets = RowID.str(); 
					for (int k=0; k<itsColumnPtrBlk[i]->getShapeColumn().nelements(); k++){
						local_offsets += " ,0";
					}
					int64_t writeID = adios_define_var(itsAdiosGroup, columnName.c_str(), "", itsColumnPtrBlk[i]->getAdiosDataType(), dimensions.c_str(), global_dimensions.c_str(), local_offsets.c_str());
					itsColumnPtrBlk[i]->putAdiosWriteIDs(j, writeID);
				}
				itsAdiosGroupsize = itsAdiosGroupsize + itsNrRows * itsColumnPtrBlk[i]->getDataTypeSize() * itsColumnPtrBlk[i]->getShapeColumn().product();
			}



		}

		itsAdiosBufsize = 100;
		adios_allocate_buffer(ADIOS_BUFFER_ALLOC_NOW, itsAdiosBufsize);

		adios_open(&itsAdiosFile, "casatable", fileName().c_str(), "w", MPI_COMM_WORLD);
		adios_group_size(itsAdiosFile, itsAdiosGroupsize, &itsAdiosTotalsize);




	}

	void AdiosStMan::deleteManager()
	{

	}

	DataManagerColumn* AdiosStMan::makeScalarColumn (const String& name,
			int aDataType,
			const String& dataTypeId)
	{

		makeDirArrColumn(name, aDataType, dataTypeId);

	}


	DataManagerColumn* AdiosStMan::makeDirArrColumn (const String&,
			int aDataType,
			const String&)
	{
		if (ncolumn() >= itsColumnPtrBlk.nelements()) {
			itsColumnPtrBlk.resize (itsColumnPtrBlk.nelements() + 32);
		}
		AdiosStManColumn* aColumn = new AdiosStManColumn (this, aDataType, ncolumn());
		itsColumnPtrBlk[ncolumn()] = aColumn;
		return aColumn;
	}

	DataManagerColumn* AdiosStMan::makeIndArrColumn (const String& name,
			int aDataType,
			const String& dataTypeId)
	{
		cout << "AdiosStMan error: Indirect array not available at this stage!" << endl;
	}


	void AdiosStMan::open (uInt aRowNr, AipsIO& ios)
	{

	}


	void AdiosStMan::resync (uInt aNrRows)
	{

	}

	Bool AdiosStMan::flush (AipsIO& ios, Bool doFsync)
	{

	}


} //# NAMESPACE CASA - END

