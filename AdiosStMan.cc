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
		itsAdiosFile(0)
	{
		MPI_Init(0,0);
		MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
		MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

	}

	AdiosStMan::AdiosStMan (int rank, int size)
		:DataManager(),
		itsAdiosFile(0)
	{
		mpi_rank = rank;
		mpi_size = size;
	}

	AdiosStMan::AdiosStMan (const AdiosStMan& that)
		:DataManager(),
		itsAdiosFile(0)
	{
	}

	AdiosStMan::~AdiosStMan ()
	{
		if(itsAdiosFile){
			adios_close(itsAdiosFile);
		}
		cout << itsAdiosFile <<endl;
		adios_finalize(mpi_rank);
	}


	DataManager* AdiosStMan::clone() const
	{
		return new AdiosStMan (*this);
	}

	String AdiosStMan::dataManagerType() const
	{
		return "AdiosStMan";
	}

	void AdiosStMan::create (uInt aNrRows)
	{

		itsNrRows = aNrRows;
		itsNrCols = ncolumn();

		itsAdiosBufsize = 100;
		itsAdiosGroupsize = 10000;

		adios_init_noxml(MPI_COMM_WORLD);
		adios_allocate_buffer(ADIOS_BUFFER_ALLOC_NOW, itsAdiosBufsize);

		adios_declare_group(&itsAdiosGroup, "root", "", adios_flag_yes);
		adios_select_method(itsAdiosGroup, "POSIX", "", "");

		adios_define_var(itsAdiosGroup, "T", "", adios_integer, "","","");
		adios_define_var(itsAdiosGroup, "X", "", adios_integer, "","","");
		adios_define_var(itsAdiosGroup, "Y", "", adios_integer, "","","");

//		for(t=0; t<T; t++){
//			adios_define_var(itsAdiosGroup, "t", "", adios_integer, "","","");
//			adios_define_var(itsAdiosGroup, "image", "", adios_real, "1,X,Y","T,X,Y","t,0,0");
//		}

		adios_open(&itsAdiosFile, "root", fileName().c_str(), "w", MPI_COMM_WORLD);

		adios_group_size(itsAdiosFile, itsAdiosGroupsize, &itsAdiosTotalsize);

//		int T =1;
//		int X =2;
//		adios_write(itsAdiosFile, "T", &T);                                              
//		adios_write(itsAdiosFile, "X", &X);



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
		//# Extend itsPtrColumn block if needed.
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
		makeDirArrColumn(name, aDataType, dataTypeId);
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

