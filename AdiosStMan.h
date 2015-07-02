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

#include "casacore_version.h"

#ifdef CASACORE_VERSION_1
#include <casa/aips.h>
#include <casa/Containers/Block.h>
#include <tables/Tables/DataManager.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/casa/aips.h>
#include <casacore/casa/Containers/Block.h>
#include <casacore/tables/DataMan/DataManager.h>
#endif

#include <adios.h>
#include <adios_read.h>


namespace casa {

    class AdiosStManColumn;
    class AdiosStManColumnA;
    class AdiosStManColumnV;

    class AdiosStMan : public DataManager
    {
        public:

            enum StManColumnType{
                ARRAY = 0,
                VAR = 1,
            };

            AdiosStMan(int aType=0, string aMethod="MPI", string aPara="", uint64_t aBufsize=1000);
            ~AdiosStMan();

            virtual DataManager* clone() const;
            virtual String dataManagerType() const;
            virtual String dataManagerName() const;
            virtual void create (uInt aNrRows);
            virtual void open (uInt aRowNr, AipsIO&);
            virtual void resync (uInt aRowNr);
            virtual Bool flush (AipsIO&, Bool doFsync);

            DataManagerColumn* makeColumnMeta (const String& aName,
                    int aDataType,
                    const String& aDataTypeID);
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

            void adiosWriteOpen();
            void adiosWriteClose();
            uInt getNrRows();
            char getMode();

            void setStManColumnType(StManColumnType aType);
            int getStManColumnType();
            void logdbg(string func, string stat);

        private:

            AdiosStMan(const AdiosStMan& that);

            String  itsDataManName;
            int64_t itsAdiosFile;
            int64_t itsAdiosGroup;
            uint64_t itsNrAdiosFiles;
            uint64_t itsAdiosBufsize;
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
