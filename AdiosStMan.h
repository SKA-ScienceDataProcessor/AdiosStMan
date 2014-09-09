//    AdiosStMan.h: Storage Manager for general CASA tables using ADIOS
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

#ifndef ADIOSSTMAN_H
#define ADIOSSTMAN_H

#include <casa/aips.h>
#include <tables/Tables/DataManager.h>
#include <casa/Containers/Block.h>
#include <adios.h>
#include <adios_read.h>


namespace casa { 

	class AdiosStManColumn;
	class AdiosStManColumnA;

	class AdiosStMan : public DataManager
	{
		public:

			AdiosStMan();
			~AdiosStMan();

			virtual DataManager* clone() const;
			virtual String dataManagerType() const;
			virtual void create (uInt aNrRows);
			virtual void open (uInt aRowNr, AipsIO&);
			virtual void resync (uInt aRowNr);
			virtual Bool flush (AipsIO&, Bool doFsync);

			AdiosStManColumn* makeScalarColumnSlave (const String& aName,
					int aDataType);
			AdiosStManColumn* makeDirArrColumnSlave (const String& aName,
					int aDataType);
			AdiosStManColumn* makeIndArrColumnSlave (const String& aName,
					int aDataType);
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
			virtual void addRow (uInt aNrRows);

			int64_t getAdiosFile();
			int64_t getAdiosGroup();
			ADIOS_FILE* getAdiosReadFile();

			static DataManager* makeObject (const casa::String& aDataManType,
					const casa::Record& spec);

			void adiosOpen();
			uInt getNrRows();
			char getMode();


		private:

			AdiosStMan(const AdiosStMan& that);

			int64_t itsAdiosFile;
			int64_t itsAdiosGroup;
			uint64_t itsNrAdiosFiles;
			uint64_t itsAdiosBufsize;
			uint64_t itsAdiosGroupsize;
			uint64_t itsAdiosTotalsize;

			ADIOS_FILE *itsAdiosReadFile;

			int mpiRank;
			int mpiSize; 
			bool isMpiInitInternal;
			bool isAdiosOpened;

			char itsStManColumnType;
			PtrBlock<AdiosStManColumnA*> itsColumnPtrBlk;

			uInt itsNrRows;
			uInt itsNrColsSlave;
			MPI_Comm itsMpiComm;

			char itsMode;


	}; // end of class AdiosStMan

	extern "C" void register_adiosstman();
} // end of namespace casa

#endif
