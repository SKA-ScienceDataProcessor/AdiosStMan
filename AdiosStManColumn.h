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

            // *** put a row for an array column, for user application call ***
            // *** legacy interface for slave processes to access AdiosStManColumn,
            // *** might be removed in newer version
            void put (uInt aRowNr, const Array<Bool> dataPtr);
            void put (uInt aRowNr, const Array<uChar> dataPtr);
            void put (uInt aRowNr, const Array<Short> dataPtr);
            void put (uInt aRowNr, const Array<uShort> dataPtr);
            void put (uInt aRowNr, const Array<Int> dataPtr);
            void put (uInt aRowNr, const Array<uInt> dataPtr);
            void put (uInt aRowNr, const Array<Float> dataPtr);
            void put (uInt aRowNr, const Array<Double> dataPtr);
            void put (uInt aRowNr, const Array<Complex> dataPtr);
            void put (uInt aRowNr, const Array<DComplex> dataPtr);
            void put (uInt aRowNr, const Array<String> dataPtr);
            // *** put a row for an array column, for user application call ***

            // *** put a row for a scalar column, for user application call ***
            // *** legacy interface for slave processes to access AdiosStManColumn,
            // *** might be removed in newer version
            void put (uInt aRowNr, const Bool dataPtr);
            void put (uInt aRowNr, const uChar dataPtr);
            void put (uInt aRowNr, const Short dataPtr);
            void put (uInt aRowNr, const uShort dataPtr);
            void put (uInt aRowNr, const Int dataPtr);
            void put (uInt aRowNr, const uInt dataPtr);
            void put (uInt aRowNr, const Float dataPtr);
            void put (uInt aRowNr, const Double dataPtr);
            void put (uInt aRowNr, const Complex dataPtr);
            void put (uInt aRowNr, const DComplex dataPtr);
            void put (uInt aRowNr, const String dataPtr);
            // *** put a row for a scalar column, for user application call ***


            // *** access a row for an array column ***
            // put
            virtual void putArrayV (uInt rownr, const void* dataPtr);
            /*
            virtual void putArrayBoolV     (uInt aRowNr, const Array<Bool>* dataPtr);
            virtual void putArrayuCharV    (uInt aRowNr, const Array<uChar>* dataPtr);
            virtual void putArrayShortV    (uInt aRowNr, const Array<Short>* dataPtr);
            virtual void putArrayuShortV   (uInt aRowNr, const Array<uShort>* dataPtr);
            virtual void putArrayIntV      (uInt aRowNr, const Array<Int>* dataPtr);
            virtual void putArrayuIntV     (uInt aRowNr, const Array<uInt>* dataPtr);
            virtual void putArrayfloatV    (uInt aRowNr, const Array<Float>* dataPtr);
            virtual void putArraydoubleV   (uInt aRowNr, const Array<Double>* dataPtr);
            virtual void putArrayComplexV  (uInt aRowNr, const Array<Complex>* dataPtr);
            virtual void putArrayDComplexV (uInt aRowNr, const Array<DComplex>* dataPtr);
            virtual void putArrayStringV   (uInt aRowNr, const Array<String>* dataPtr);
            */
            // get
            virtual void getArrayBoolV     (uInt aRowNr, Array<Bool>* dataPtr);
            virtual void getArrayuCharV    (uInt aRowNr, Array<uChar>* dataPtr);
            virtual void getArrayShortV    (uInt aRowNr, Array<Short>* dataPtr);
            virtual void getArrayuShortV   (uInt aRowNr, Array<uShort>* dataPtr);
            virtual void getArrayIntV      (uInt aRowNr, Array<Int>* dataPtr);
            virtual void getArrayuIntV     (uInt aRowNr, Array<uInt>* dataPtr);
            virtual void getArrayfloatV    (uInt aRowNr, Array<float>* dataPtr);
            virtual void getArraydoubleV   (uInt aRowNr, Array<double>* dataPtr);
            virtual void getArrayComplexV  (uInt aRowNr, Array<Complex>* dataPtr);
            virtual void getArrayDComplexV (uInt aRowNr, Array<DComplex>* dataPtr);
            virtual void getArrayStringV   (uInt aRowNr, Array<String>* dataPtr);
            // *** access a row for an array column ***


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
            // *** access a row for a scalar column ***


            // *** access a slice of a row for an array column ***
            // *** inactive by default
            // *** only active when canAccessSlice() returns true in child class
            // put

            // get
            virtual void getSliceBoolV	   (uInt aRowNr, const Slicer& ns, Array<Bool>* dataPtr);
            virtual void getSliceuCharV    (uInt aRowNr, const Slicer& ns, Array<uChar>* dataPtr);
            virtual void getSliceShortV    (uInt aRowNr, const Slicer& ns, Array<Short>* dataPtr);
            virtual void getSliceuShortV   (uInt aRowNr, const Slicer& ns, Array<uShort>* dataPtr);
            virtual void getSliceIntV      (uInt aRowNr, const Slicer& ns, Array<Int>* dataPtr);
            virtual void getSliceuIntV     (uInt aRowNr, const Slicer& ns, Array<uInt>* dataPtr);
            virtual void getSlicefloatV    (uInt aRowNr, const Slicer& ns, Array<float>* dataPtr);
            virtual void getSlicedoubleV   (uInt aRowNr, const Slicer& ns, Array<double>* dataPtr);
            virtual void getSliceComplexV  (uInt aRowNr, const Slicer& ns, Array<Complex>* dataPtr);
            virtual void getSliceDComplexV (uInt aRowNr, const Slicer& ns, Array<DComplex>* dataPtr);
            // *** access a slice of a row for an array column ***


            // *** access all rows for an array column ***
            // *** inactive by default
            // *** only active when canAccessArrayColumn() returns true in child class
            // put

            // get
            virtual void getArrayColumnBoolV     (Array<Bool>* dataPtr);
            virtual void getArrayColumnuCharV    (Array<uChar>* dataPtr);
            virtual void getArrayColumnShortV    (Array<Short>* dataPtr);
            virtual void getArrayColumnuShortV   (Array<uShort>* dataPtr);
            virtual void getArrayColumnIntV      (Array<Int>* dataPtr);
            virtual void getArrayColumnuIntV     (Array<uInt>* dataPtr);
            virtual void getArrayColumnfloatV    (Array<float>* dataPtr);
            virtual void getArrayColumndoubleV   (Array<double>* dataPtr);
            virtual void getArrayColumnComplexV  (Array<Complex>* dataPtr);
            virtual void getArrayColumnDComplexV (Array<DComplex>* dataPtr);
            // *** access all rows for an array column ***


            // *** access a slice of all rows for an array column ***
            // *** inactive by default
            // *** only active when canAccessColumnSlice() returns true in child class
            // put

            // get
            virtual void getColumnSlicesBoolV	 (const Slicer& ns, Array<Bool>* dataPtr);
            virtual void getColumnSlicesuCharV	 (const Slicer& ns, Array<uChar>* dataPtr);
            virtual void getColumnSlicesShortV   (const Slicer& ns, Array<Short>* dataPtr);
            virtual void getColumnSlicesuShortV  (const Slicer& ns, Array<uShort>* dataPtr);
            virtual void getColumnSlicesIntV     (const Slicer& ns, Array<Int>* dataPtr);
            virtual void getColumnSlicesuIntV    (const Slicer& ns, Array<uInt>* dataPtr);
            virtual void getColumnSlicefloatV    (const Slicer& ns, Array<float>* dataPtr);
            virtual void getColumnSlicedoubleV   (const Slicer& ns, Array<double>* dataPtr);
            virtual void getColumnSliceComplexV  (const Slicer& ns, Array<Complex>* dataPtr);
            virtual void getColumnSliceDComplexV (const Slicer& ns, Array<DComplex>* dataPtr);
            // *** access a slice of all rows for an array column ***



        protected:

            // *** check if data is all zero ***
            // void
            bool isZero (const void *dataPtr);
            // scalar
            inline bool isZero (const Bool* dataPtr);
            inline bool isZero (const uChar* dataPtr);
            inline bool isZero (const Short* dataPtr);
            inline bool isZero (const uShort* dataPtr);
            inline bool isZero (const Int* dataPtr);
            inline bool isZero (const uInt* dataPtr);
            inline bool isZero (const float* dataPtr);
            inline bool isZero (const double* dataPtr);
            inline bool isZero (const Complex* dataPtr);
            inline bool isZero (const DComplex* dataPtr);
            // array
            inline bool isZero (const Array<Bool>* dataPtr);
            inline bool isZero (const Array<uChar>* dataPtr);
            inline bool isZero (const Array<Short>* dataPtr);
            inline bool isZero (const Array<uShort>* dataPtr);
            inline bool isZero (const Array<Int>* dataPtr);
            inline bool isZero (const Array<uInt>* dataPtr);
            inline bool isZero (const Array<float>* dataPtr);
            inline bool isZero (const Array<double>* dataPtr);
            inline bool isZero (const Array<Complex>* dataPtr);
            inline bool isZero (const Array<DComplex>* dataPtr);
            // *** check if data is all zero ***


            // access a row for a scalar column
            virtual void putGeneralV (uInt aRowNr, const void* aDataPtr);
            virtual void getGeneralV (uInt aRowNr, void* aDataPtr) = 0;

            // access a row for an array column
            virtual void getArrayGeneralV (int64_t aRowNr, void* data);

            // access a slice of a row for an array column
            virtual void getSliceGeneralV (int64_t aRowNr, const Slicer& ns, void* data) = 0;

            // access all rows for an array column
            virtual void getArrayColumnGeneralV (void* data);

            // access a slice of all rows for an array column
            virtual void getColumnSliceGeneralV (const Slicer& ns, void* data);

            // StMan pointer
            AdiosStMan *itsStManPtr;

            // Column property
            String itsColumnName;
            IPosition itsShape;
            uint64_t itsNrElem;
            int itsDataTypeSize;

            // ADIOS read
            uint64_t *readStart;
            uint64_t *readCount;

            // ADIOS write
            ADIOS_DATATYPES itsAdiosDataType;
            int64_t *itsAdiosWriteIDs;
            uint64_t itsNrIDs;                  // number of ADIOS write IDs that have been defined
            uint64_t itsNrIDsAllocated;			// number of ADIOS write IDs that have been allocated


            int itsCasaDataType;
            bool isArrayColumn;



    };



}


#endif
