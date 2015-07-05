//    AdiosStManIndColumn.h: StManColumn class for AdiosStMan,
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

#ifndef ADIOSSTMANINDCOLUMN_H
#define ADIOSSTMANINDCOLUMN_H

#include "AdiosStManColumn.h"

namespace casacore {

    class AdiosStManIndColumn : public AdiosStManColumn
    {
        public:
            AdiosStManIndColumn(AdiosStMan *aParent, int aDataType, uInt aColNr);
            ~AdiosStManIndColumn();
            virtual void initAdiosWrite(uInt aNrRows);
            virtual void initAdiosRead();
            Bool canAccessSlice(Bool &reask) const;
            virtual void flush();
        private:
            virtual void getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* dataPtr);
            virtual void putArrayMetaV (uint64_t row, const void* data);
    }; // end of class AdiosStManIndColumn
} // end of namespace casa

#endif
