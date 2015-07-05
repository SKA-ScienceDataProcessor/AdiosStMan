//    AdiosStManColumn.h: base StManColumn class for AdiosStMan
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

#ifndef ADIOSSTMANCOLUMN_H
#define ADIOSSTMANCOLUMN_H

#include "AdiosStMan.h"

#ifdef CASACORE_VERSION_1
#include <tables/Tables/StManColumn.h>
#include <casa/Arrays/Array.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/tables/DataMan/StManColumn.h>
#include <casacore/casa/Arrays/Array.h>
#endif

namespace casacore {

    class AdiosStManColumn : public StManColumn
    {
        public:

            AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr);
            ~AdiosStManColumn ();

            IPosition getShapeColumn();

            int getDataTypeSize();
            int getDataType();
            void setColumnName(String aName);
            String getColumnName();

            virtual void initAdiosRead() = 0;
            virtual void initAdiosWrite(uInt aNrRows) = 0;

            // *** access a row for an array column ***
            virtual void putArrayV (uInt rownr, const void* dataPtr);
            virtual void getArrayV (uInt rownr, void* dataPtr);

            // *** access a slice of a row for an array column ***
            // *** inactive by default
            // *** only active when canAccessSlice() returns true in child class
            virtual void getSliceV (uInt aRowNr, const Slicer& ns, void* dataPtr);

            // *** access all rows for an array column ***
            // *** inactive by default
            // *** only active when canAccessArrayColumn() returns true in child class
            virtual void getArrayColumnV(void* dataPtr);

            // *** access a slice of all rows for an array column ***
            // *** inactive by default
            // *** only active when canAccessColumnSlice() returns true in child class
            virtual void getColumnSliceV(const Slicer& ns, void *dataPtr);

            virtual void flush() = 0;

        protected:

            void getArrayWrapper(uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* dataPtr);
            virtual void getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* data);
            virtual void putArrayMetaV (uint64_t row, const void* data);

            // StMan pointer
            AdiosStMan *itsStManPtr;

            // Column property
            String itsColumnName;
            char itsColumnType;  // 's' for scalar, 'd' for direct array, 'i' for indirect array
            IPosition itsShape;
            int itsDataTypeSize;
            int itsCasaDataType;
            ADIOS_DATATYPES itsAdiosDataType;

            // ADIOS read
            uint64_t readStart[10];
            uint64_t readCount[10];

            // ADIOS write
            int64_t *itsAdiosWriteIDs;
    };

}


#endif
