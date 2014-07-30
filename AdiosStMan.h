//# AdiosStMan.h: The Standard Storage Manager
//# Copyright (C) 2000,2002
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
//# $Id: AdiosStMan.h 20551 2009-03-25 00:11:33Z Malte.Marquarding $

#ifndef ADIOSSTMAN_H
#define ADIOSSTMAN_H

#include <casa/aips.h>
#include <tables/Tables/DataManager.h>
#include <casa/Containers/Block.h>
#include <adios.h>


namespace casa { //# NAMESPACE CASA - BEGIN

	class AdiosStManColumn;

	class AdiosStMan : public DataManager
	{
		public:

			AdiosStMan();
			AdiosStMan(int rank, int size);
			~AdiosStMan();

			virtual DataManager* clone() const;
			virtual String dataManagerType() const;
			virtual void create (uInt aNrRows);
			virtual void open (uInt aRowNr, AipsIO&);
			virtual void resync (uInt aRowNr);
			virtual Bool flush (AipsIO&, Bool doFsync);
			virtual DataManagerColumn* makeScalarColumn (const String& aName,
					int aDataType,
					const String& aDataTypeID);
			virtual DataManagerColumn* makeDirArrColumn (const String& aName,
					int aDataType,
					const String& aDataTypeID);
			virtual DataManagerColumn* makeIndArrColumn (const String& aName,
					int aDataType,
					const String& aDataTypeID);
			virtual void deleteManager();

			int64_t getAdiosFile();

		private:

			AdiosStMan(const AdiosStMan& that);

			int64_t itsAdiosFile;
			int64_t itsAdiosGroup;
			uint64_t itsAdiosBufsize;
			uint64_t itsAdiosGroupsize;
			uint64_t itsAdiosTotalsize;


			int mpiRank;
			int mpiSize; 
			bool isMpiInitInternal;

			// The assembly of all columns.
			PtrBlock<AdiosStManColumn*> itsColumnPtrBlk;

			uInt itsNrRows;
			uInt itsNrCols;
	};



} //# NAMESPACE CASA - END

#endif
