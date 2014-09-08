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

			// *** put a row for an array column, for user application call ***
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



			// *** put a row for an array column ***
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
			// *** put a row for an array column ***


			// *** put a row for a scalar column ***
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
			// *** put a row for a scalar column ***


			// *** get a row for an array column ***
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
			// *** get a row for an array column ***


			// *** get all rows for an array column ***
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
			virtual void getArrayColumnStringV   (Array<String>* dataPtr);
			// *** get all rows for an array column ***


			// *** get a row for a scalar column ***
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
			// *** get a row for a scalar column ***



			// *** get a slice of a row for an array column ***
			virtual void getColumnSliceCellsBoolV	  (uInt aRowNr, const Slicer& ns, Array<Bool>* dataPtr);
			virtual void getColumnSliceCellsuCharV	  (uInt aRowNr,	const Slicer& ns, Array<uChar>* dataPtr);
			virtual void getColumnSliceCellsShortV    (uInt aRowNr,	const Slicer& ns, Array<Short>* dataPtr);
			virtual void getColumnSliceCellsuShortV   (uInt aRowNr,	const Slicer& ns, Array<uShort>* dataPtr);
			virtual void getColumnSliceCellsIntV      (uInt aRowNr,	const Slicer& ns, Array<Int>* dataPtr);
			virtual void getColumnSliceCellsuIntV     (uInt aRowNr,	const Slicer& ns, Array<uInt>* dataPtr);
			virtual void getSliceCellsfloatV	      (uInt aRowNr,	const Slicer& ns, Array<float>* dataPtr);
			virtual void getColumnSliceCellsdoubleV   (uInt aRowNr,	const Slicer& ns, Array<double>* dataPtr);
			virtual void getColumnSliceCellsComplexV  (uInt aRowNr,	const Slicer& ns, Array<Complex>* dataPtr);
			virtual void getColumnSliceCellsDComplexV (uInt aRowNr,	const Slicer& ns, Array<DComplex>* dataPtr);
			// *** get a slice of a row for an array column ***


			int getDataTypeSize();

			IPosition getShapeColumn();
			void setColumnName(String aName);

			void initAdiosWrite(uInt aNrRows);
			void initAdiosRead();

//			virtual Bool canAccessScalarColumn(Bool &reask) const;
			virtual Bool canAccessArrayColumn(Bool &reask) const;
//			virtual Bool canAccessArrayColumn(Bool &reask) const;
//			virtual Bool canAccessArrayColumn(Bool &reask) const;


		private:

			void getGeneralV (uInt aRowNr, void* aDataPtr);
			void getArrayGeneralV (int64_t aRowNr, const Slicer& ns,	void* data);
			void getArrayGeneralV (int64_t aRowNr, void* data);
			void getArrayColumnGeneralV  (void* data);

			void putGeneralV (uInt aRowNr, const void* aDataPtr);

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
