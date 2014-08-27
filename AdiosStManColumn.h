//    AdiosStManColumn.h: DataManagerColumn class for AdiosStMan
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


#include <tables/Tables/StManColumn.h>
#include <casa/Arrays/IPosition.h>
#include "AdiosStMan.h"


namespace casa { //# NAMESPACE CASA - BEGIN

	class AdiosStManColumn : public StManColumn
	{
		public:

			AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr);
			~AdiosStManColumn ();
			virtual void setShapeColumn (const IPosition& aShape);
			virtual IPosition shape(uInt RowID);


			// Put an array value in the given row.
			// <group>
			virtual void putArrayBoolV     (uInt rownr, const Array<Bool>* dataPtr);
			virtual void putArrayuCharV    (uInt rownr, const Array<uChar>* dataPtr);
			virtual void putArrayShortV    (uInt rownr, const Array<Short>* dataPtr);
			virtual void putArrayuShortV   (uInt rownr, const Array<uShort>* dataPtr);
			virtual void putArrayIntV      (uInt rownr, const Array<Int>* dataPtr);
			virtual void putArrayuIntV     (uInt rownr, const Array<uInt>* dataPtr);
			virtual void putArrayfloatV    (uInt rownr, const Array<Float>* dataPtr);
			virtual void putArraydoubleV   (uInt rownr, const Array<Double>* dataPtr);
			virtual void putArrayComplexV  (uInt rownr, const Array<Complex>* dataPtr);
			virtual void putArrayDComplexV (uInt rownr, const Array<DComplex>* dataPtr);
			virtual void putArrayStringV   (uInt rownr, const Array<String>* dataPtr);
			// </group>

			// Put the scalar value in the given row.
			// It updates the cache if the row is contained in the cache.
			// <group>
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
			// </group>

			// Get an array value in the given row.
			// <group>
			virtual void getArrayBoolV     (uInt rownr, Array<Bool>* dataPtr);
			virtual void getArrayuCharV    (uInt rownr, Array<uChar>* dataPtr);
			virtual void getArrayShortV    (uInt rownr, Array<Short>* dataPtr);
			virtual void getArrayuShortV   (uInt rownr, Array<uShort>* dataPtr);
			virtual void getArrayIntV      (uInt rownr, Array<Int>* dataPtr);
			virtual void getArrayuIntV     (uInt rownr, Array<uInt>* dataPtr);
			virtual void getArrayfloatV    (uInt rownr, Array<float>* dataPtr);
			virtual void getArraydoubleV   (uInt rownr, Array<double>* dataPtr);
			virtual void getArrayComplexV  (uInt rownr, Array<Complex>* dataPtr);
			virtual void getArrayDComplexV (uInt rownr, Array<DComplex>* dataPtr);
			virtual void getArrayStringV   (uInt rownr, Array<String>* dataPtr);
			// </group>


			// Get the scalar value in the given row.
			// <group>
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
			// </group>



			int getDataTypeSize();

			IPosition getShapeColumn();
			void setColumnName(String aName);

			void initAdiosWrite(uInt aNrRows);
			void initAdiosRead();


		private:

			void getGeneralV(uInt aRowNr, void* aDataPtr);
			void getArrayGeneralV (uInt aRowNr,	void* data);

			void putGeneralV(uInt aRowNr, const void* aDataPtr);

			// StMan pointer
			AdiosStMan *itsStManPtr;

			// Column property
			String itsColumnName;
			IPosition itsShape;
			uint64_t itsNrElem;
			int itsDataTypeSize;

			// ADIOS read
			ADIOS_VARINFO *itsAdiosVarInfo;
			uint64_t *readStart;
			uint64_t *readCount;

			// ADIOS write
			ADIOS_DATATYPES itsAdiosDataType;
			int64_t *itsAdiosWriteIDs;
			uint64_t itsNrIDs;                  // number of ADIOS write IDs that have been defined
			uint64_t itsNrIDsAllocated;			// number of ADIOS write IDs that have been allocated 




	};



}


#endif
