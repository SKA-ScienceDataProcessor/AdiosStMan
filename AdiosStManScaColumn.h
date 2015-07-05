//    AdiosStManScaColumn.h: StManColumn class for AdiosStMan,
//    managing all rows in a single array for a column
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

#ifndef ADIOSSTMANSCACOLUMN_H
#define ADIOSSTMANSCACOLUMN_H

#include "AdiosStManColumn.h"

namespace casacore {
    class AdiosStManScaColumn : public AdiosStManColumn
    {
        public:
            AdiosStManScaColumn(AdiosStMan *aParent, int aDataType, uInt aColNr);
            ~AdiosStManScaColumn();
            virtual void initAdiosWrite(uInt aNrRows);
            virtual void initAdiosRead();
            virtual void flush();
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
        private:
            void getScalarMetaV (uint64_t row, void* data);
            bool gotScalarColumn;
            void *columnCache;
    }; // end of class AdiosStManScaColumn
} // end of namespace casa

#endif
