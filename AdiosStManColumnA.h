//    AdiosStManColumnA.h: StManColumn class for AdiosStMan, 
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

#ifndef ADIOSSTMANCOLUMNA_H
#define ADIOSSTMANCOLUMNA_H


#include <casa/Arrays/IPosition.h>
#include "AdiosStMan.h"
#include "AdiosStManColumn.h"


namespace casa { 

	class AdiosStManColumnA : public AdiosStManColumn
	{
		public:

			AdiosStManColumnA(AdiosStMan *aParent, int aDataType, uInt aColNr);
			
			void initAdiosRead();
			void initAdiosWrite(uInt aNrRows);

			Bool canAccessArrayColumn(Bool &reask) const;
			Bool canAccessColumnSlice(Bool &reask) const;
			Bool canAccessSlice(Bool &reask) const;

		private:

			// access a row for a scalar column 
			void putGeneralV (uInt aRowNr, const void* aDataPtr);
			void getGeneralV (uInt aRowNr, void* aDataPtr);

			// access a row for an array column 
			void putArrayGeneralV (uInt aRowNr, const void* aDataPtr);
			void getArrayGeneralV (int64_t aRowNr, void* data);

			void getSliceGeneralV (int64_t aRowNr, const Slicer& ns, void* data);

			void getArrayColumnGeneralV (void* data);

			void getColumnSliceGeneralV (const Slicer& ns, void* data);

	}; // end of class AdiosStManColumnA

} // end of namespace casa


#endif
