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

#include "casacore_version.h"

#ifdef CASACORE_VERSION_1
#include <tables/Tables/StManColumn.h>
#include <casa/Arrays/IPosition.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/tables/DataMan/StManColumn.h>
#include <casacore/casa/Arrays/IPosition.h>
#endif

#include "AdiosStMan.h"


namespace casacore { //# NAMESPACE CASA - BEGIN

    class AdiosStManColumn : public StManColumn
    {
        public:

            AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr);
            ~AdiosStManColumn ();

            virtual void setShapeColumn (const IPosition& aShape);
            IPosition getShapeColumn();
            virtual IPosition shape(uInt RowID);

            int getDataTypeSize();
            int getDataType();
            void setColumnName(String aName);
            String getColumnName();

            virtual void initAdiosRead();
            virtual void initAdiosWrite(uInt aNrRows) = 0;

            // *** access a row for a scalar column ***
            // put
            virtual void putBoolV     (uInt aRowNr, const Bool* aDataPtr);
            virtual void putuCharV    (uInt aRowNr, const uChar* aDataPtr);
            virtual void putShortV    (uInt aRowNr, const Short* aDataPtr);
            virtual void putuShortV   (uInt aRowNr, const uShort* aDataPtr);
            virtual void putIntV      (uInt aRowNr, const Int* aDataPtr);
            virtual void putuIntV     (uInt aRowNr, const uInt* aDataPtr);
            virtual void putfloatV    (uInt aRowNr, const Float* aDataPtr);
            virtual void putdoubleV   (uInt aRowNr, const Double* aDataPtr);
            virtual void putComplexV  (uInt aRowNr, const Complex* aDataPtr);
            virtual void putDComplexV (uInt aRowNr, const DComplex* aDataPtr);
            virtual void putStringV   (uInt aRowNr, const String* aDataPtr);
            // get
            virtual void getBoolV     (uInt aRowNr, Bool* aDataPtr);
            virtual void getuCharV    (uInt aRowNr, uChar* aDataPtr);
            virtual void getShortV    (uInt aRowNr, Short* aDataPtr);
            virtual void getuShortV   (uInt aRowNr, uShort* aDataPtr);
            virtual void getIntV      (uInt aRowNr, Int* aDataPtr);
            virtual void getuIntV     (uInt aRowNr, uInt* aDataPtr);
            virtual void getfloatV    (uInt aRowNr, float* aDataPtr);
            virtual void getdoubleV   (uInt aRowNr, double* aDataPtr);
            virtual void getComplexV  (uInt aRowNr, Complex* aDataPtr);
            virtual void getDComplexV (uInt aRowNr, DComplex* aDataPtr);
            virtual void getStringV   (uInt aRowNr, String* aDataPtr);

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
            virtual void getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* data) = 0;
            virtual void putArrayMetaV (uint64_t row, const void* data) = 0;

            virtual void getScalarMetaV (uint64_t row, void* data) = 0;
            virtual void putScalarMetaV (uint64_t row, const void* data) = 0;

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
            uint64_t *readStart;
            uint64_t *readCount;

            // ADIOS write
            int64_t *itsAdiosWriteIDs;
            void *scalarCache;
    };

}


#endif
