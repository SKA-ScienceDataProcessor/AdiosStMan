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

#include "casacore_version.h"

#ifdef CASACORE_VERSION_1
#include <casa/Arrays/IPosition.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/casa/Arrays/IPosition.h>
#endif

#include "AdiosStMan.h"
#include "AdiosStManColumn.h"


namespace casa {
    class AdiosStManScaColumn : public AdiosStManColumn
    {
        public:
            AdiosStManScaColumn(AdiosStMan *aParent, int aDataType, uInt aColNr);
            ~AdiosStManScaColumn();
            void initAdiosWrite(uInt aNrRows);
            virtual void flush();
        private:
            virtual void getScalarMetaV (uint64_t row, void* data);
            virtual void putScalarMetaV (uint64_t row, const void* data);
            virtual void getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* data);
            virtual void putArrayMetaV (uint64_t row, const void* data);
            bool gotScalarColumn;
    }; // end of class AdiosStManScaColumn
} // end of namespace casa

#endif
