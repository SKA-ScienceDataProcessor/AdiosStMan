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

#include "AdiosStManGlobal.h"

#ifdef CASACORE_VERSION_1
#include <tables/Tables/DataManager.h>
#include <tables/Tables/Table.h>
#include <casa/IO/AipsIO.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/tables/DataMan/DataManager.h>
#include <casacore/tables/Tables/Table.h>
#include <casacore/casa/IO/AipsIO.h>
#endif

#include <adios.h>
#include <adios_read.h>


namespace casacore {

    class AdiosStManColumn;

    class AdiosStMan : public DataManager
    {
        public:

//            AdiosStMan(string aMethod="POSIX", string aPara="", uint64_t writeBufsize=1000, uint64_t readBufsize=2000);
            AdiosStMan(string aMethod="MPI_AGGREGATE", string aPara="num_aggregators=24, num_ost=12", uint64_t writeBufsize=1000, uint64_t readBufsize=2000);
            ~AdiosStMan();

            virtual DataManager* clone() const;
            virtual String dataManagerType() const;
            virtual String dataManagerName() const;
            virtual void create (uInt aNrRows);
            virtual void open (uInt aRowNr, AipsIO&);
            virtual void resync (uInt aRowNr);
            virtual Bool flush (AipsIO&, Bool doFsync);

            DataManagerColumn* makeColumnMeta (const String& aName, int aDataType, const String& aDataTypeID, char columnType);
            virtual DataManagerColumn* makeScalarColumn (const String& aName, int aDataType, const String& aDataTypeID);
            virtual DataManagerColumn* makeDirArrColumn (const String& aName, int aDataType, const String& aDataTypeID);
            virtual DataManagerColumn* makeIndArrColumn (const String& aName, int aDataType, const String& aDataTypeID);
            virtual void deleteManager();
            virtual void addRow (uInt aNrRows);

            int64_t getAdiosFile();
            int64_t getAdiosGroup();
            ADIOS_FILE* getAdiosReadFile();

            static DataManager* makeObject (const casa::String& aDataManType, const casa::Record& spec);

            void adiosWriteOpen();
            void adiosWriteClose();
            uInt getNrRows();
            char getMode();
            uint64_t getReadBufsize();

            void logdbg(string func, string stat, int para=0);

        private:

            AdiosStMan(const AdiosStMan& that);

            String  itsDataManName;
            int64_t itsAdiosWriteFile;
            int64_t itsAdiosGroup;
            uint64_t itsNrAdiosFiles;
            uint64_t itsAdiosWriteBufsize;
            uint64_t itsAdiosReadBufsize;
            uint64_t itsAdiosGroupsize;
            uint64_t itsAdiosTotalsize;
            string itsAdiosTransMethod;
            string itsAdiosTransPara;

            ADIOS_FILE *itsAdiosReadFile;

            int mpiRank;
            int mpiSize;
            bool isMpiInitInternal;
            static int itsNrInstances;

            PtrBlock<AdiosStManColumn*> itsColumnPtrBlk;

            uInt itsNrRows;
            uInt itsNrCols;
            MPI_Comm itsMpiComm;

            char itsMode;
            int itsStManColumnType;

            string logdbgLast;
            uint64_t logdbgCount;

    }; // end of class AdiosStMan

    extern "C" void register_adiosstman();
} // end of namespace casa

#endif
