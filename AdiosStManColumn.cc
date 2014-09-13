//    AdiosStManColumn.cc: DataManagerColumn class for AdiosStMan
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

#include "AdiosStManColumn.h"
#include <casa/Arrays/Array.h>
#include <casa/Utilities/DataType.h>

namespace casa{

	AdiosStManColumn::AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
		:StManColumn (aDataType),
		itsAdiosWriteIDs (0),
		itsNrIDs (0),
		itsNrIDsAllocated (0),
		readStart (0),
		readCount (0),
		itsAdiosVarInfo (0),
		itsStManPtr (aParent),
		itsCasaDataType(aDataType),
		itsShape(0)
	{
		switch (aDataType){
			case TpBool:
			case TpArrayBool:
				itsAdiosDataType = adios_byte;
				itsDataTypeSize = sizeof(Bool);
				break;
			case TpChar:
			case TpArrayChar:
				itsAdiosDataType = adios_byte;
				itsDataTypeSize = sizeof(Char);
				break;
			case TpUChar:
			case TpArrayUChar:
				itsAdiosDataType = adios_unsigned_byte;
				itsDataTypeSize = sizeof(uChar);
				break;
			case TpShort:
			case TpArrayShort:
				itsAdiosDataType = adios_short;
				itsDataTypeSize = sizeof(Short);
				break;
			case TpUShort:
			case TpArrayUShort:
				itsAdiosDataType = adios_unsigned_short;
				itsDataTypeSize = sizeof(uShort);
				break;
			case TpInt:
			case TpArrayInt:
				itsAdiosDataType = adios_integer;
				itsDataTypeSize = sizeof(Int);
				break;
			case TpUInt:
			case TpArrayUInt:
				itsAdiosDataType = adios_unsigned_integer;
				itsDataTypeSize = sizeof(uInt);
				break;
			case TpFloat:
			case TpArrayFloat:
				itsAdiosDataType = adios_real;
				itsDataTypeSize = sizeof(Float);
				break;
			case TpDouble:
			case TpArrayDouble:
				itsAdiosDataType = adios_double;
				itsDataTypeSize = sizeof(Double);
				break;
			case TpComplex:
			case TpArrayComplex:
				itsAdiosDataType = adios_complex;
				itsDataTypeSize = sizeof(Complex);
				break;
			case TpDComplex:
			case TpArrayDComplex:
				itsAdiosDataType = adios_double_complex;
				itsDataTypeSize = sizeof(DComplex);
				break;
			case TpString:
			case TpArrayString:
				itsAdiosDataType = adios_string;
				itsDataTypeSize = -1;
				break;
		}
	}

	AdiosStManColumn::~AdiosStManColumn (){
		if (readStart)   delete [] readStart;
		if (readCount)   delete [] readCount;
		if (itsAdiosWriteIDs)	free(itsAdiosWriteIDs);
	}

	void AdiosStManColumn::setColumnName (String aName){
		itsColumnName = aName;
	}

	IPosition AdiosStManColumn::getShapeColumn (){
		return itsShape;
	}

	IPosition AdiosStManColumn::shape (uInt RowID){
		return itsShape;
	}

	int AdiosStManColumn::getDataTypeSize(){
		return itsDataTypeSize;
	}

	void AdiosStManColumn::setShapeColumn (const IPosition& aShape){
		itsNrElem = aShape.product();
		itsShape  = aShape;
		if(itsShape.nelements() == 0){
			isArrayColumn = false;
		}
		else{
			isArrayColumn = true;
		}
	}


	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** put a row for an array column, for user application call ***
	// *** legacy interface for slave processes to access AdiosStManColumn,
	// *** might be removed in newer version
	void AdiosStManColumn::put (uInt rownr, const Array<Bool> dataPtr){
		putArrayBoolV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<uChar> dataPtr){
		putArrayuCharV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Short> dataPtr){
		putArrayShortV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<uShort> dataPtr){
		putArrayuShortV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Int> dataPtr){
		putArrayIntV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<uInt> dataPtr){
		putArrayuIntV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Float> dataPtr){
		putArrayfloatV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Double> dataPtr){
		putArraydoubleV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Complex> dataPtr){
		putArrayComplexV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<DComplex> dataPtr){
		putArrayDComplexV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<String> dataPtr){
		putArrayStringV(rownr, &dataPtr);
	}
	// *** put a row for an array column, for user application call ***


	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** put a row for a scalar column, for user application call ***
	// *** legacy interface for slave processes to access AdiosStManColumn,
	// *** might be removed in newer version
	void AdiosStManColumn::put (uInt rownr, const Bool dataPtr){
		putBoolV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const uChar dataPtr){
		putuCharV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Short dataPtr){
		putShortV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const uShort dataPtr){
		putuShortV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Int dataPtr){
		putIntV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const uInt dataPtr){
		putuIntV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Float dataPtr){
		putfloatV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Double dataPtr){
		putdoubleV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Complex dataPtr){
		putComplexV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const DComplex dataPtr){
		putDComplexV(rownr, &dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const String dataPtr){
		putStringV(rownr, &dataPtr);
	}
	// *** put a row for a scalar column, for user application call ***


	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** access a row for an array column ***
	// put
	void AdiosStManColumn::putArrayBoolV (uInt rownr, const Array<Bool>* dataPtr){
		Bool deleteIt;
		const Bool* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayuCharV (uInt rownr, const Array<uChar>* dataPtr){
		Bool deleteIt;
		const uChar* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayShortV (uInt rownr, const Array<Short>* dataPtr){
		Bool deleteIt;
		const Short* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayuShortV (uInt rownr, const Array<uShort>* dataPtr){
		Bool deleteIt;
		const uShort* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayIntV (uInt rownr, const Array<Int>* dataPtr){
		Bool deleteIt;
		const Int* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayuIntV (uInt rownr, const Array<uInt>* dataPtr){
		Bool deleteIt;
		const uInt* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayfloatV (uInt rownr, const Array<Float>* dataPtr){
		Bool deleteIt;
		const float* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArraydoubleV (uInt rownr, const Array<Double>* dataPtr){
		Bool deleteIt;
		const Double* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayComplexV (uInt rownr, const Array<Complex>* dataPtr){
		Bool deleteIt;
		const Complex* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayDComplexV (uInt rownr, const Array<DComplex>* dataPtr){
		Bool deleteIt;
		const DComplex* data = dataPtr->getStorage (deleteIt);
		putArrayGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}
	void AdiosStManColumn::putArrayStringV (uInt rownr, const Array<String>* dataPtr){
		cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at the moment!" << endl;
	}
	// get
	void AdiosStManColumn::getArrayBoolV (uInt aRowNr, Array<Bool>* aDataPtr){
		Bool deleteIt;
		Bool* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayuCharV (uInt aRowNr, Array<uChar>* aDataPtr){
		Bool deleteIt;
		uChar* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayShortV (uInt aRowNr, Array<Short>* aDataPtr){
		Bool deleteIt;
		Short* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayuShortV (uInt aRowNr, Array<uShort>* aDataPtr){
		Bool deleteIt;
		uShort* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayIntV (uInt aRowNr, Array<Int>* aDataPtr){
		Bool deleteIt;
		Int* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayuIntV (uInt aRowNr, Array<uInt>* aDataPtr){
		Bool deleteIt;
		uInt* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayfloatV (uInt aRowNr,	Array<float>* aDataPtr){
		Bool deleteIt;
		float* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArraydoubleV (uInt aRowNr, Array<double>* aDataPtr){
		Bool deleteIt;
		double* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayComplexV (uInt aRowNr, Array<Complex>* aDataPtr){
		Bool deleteIt;
		Complex* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayDComplexV (uInt aRowNr, Array<DComplex>* aDataPtr){
		Bool deleteIt;
		DComplex* data = aDataPtr->getStorage (deleteIt);
		getArrayGeneralV(aRowNr, data);
		aDataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayStringV (uInt aRowNr, Array<String>* aDataPtr){
		cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at the moment!" << endl;
	}
	// *** access a row for an array column ***


	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** access a row for an array column ***
	// put
	void AdiosStManColumn::putBoolV (uInt rownr, const Bool* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putuCharV (uInt rownr, const uChar* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putShortV (uInt rownr, const Short* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putuShortV (uInt rownr, const uShort* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putIntV (uInt rownr, const Int* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putuIntV (uInt rownr, const uInt* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putfloatV (uInt rownr, const float* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putdoubleV (uInt rownr, const double* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putComplexV (uInt rownr, const Complex* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putDComplexV (uInt rownr, const DComplex* dataPtr){
		putGeneralV(rownr, dataPtr);
	}
	void AdiosStManColumn::putStringV (uInt rownr, const String* dataPtr){
		cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at the moment!" << endl;
	}
	// get
	void AdiosStManColumn::getBoolV (uInt aRowNr, Bool* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getuCharV (uInt aRowNr, uChar* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getShortV (uInt aRowNr, Short* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getuShortV (uInt aRowNr, uShort* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getIntV (uInt aRowNr, Int* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getuIntV (uInt aRowNr, uInt* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getfloatV (uInt aRowNr, float* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getdoubleV (uInt aRowNr, double* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getComplexV (uInt aRowNr, Complex* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getDComplexV (uInt aRowNr,DComplex* aValue){
		getGeneralV(aRowNr, aValue);
	}
	void AdiosStManColumn::getStringV (uInt aRowNr, String* aValue){
		cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at this point!" << endl;
	}
	// *** access a row for an array column ***


	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** access a slice of a row for an array column ***
	// *** inactive by default
	// *** only active when canAccessSlice() returns true in child class
	// put

	// get
	void AdiosStManColumn::getSliceBoolV     (uInt aRowNr, const Slicer& ns, Array<Bool>* dataPtr){
		Bool deleteIt;
		Bool* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceuCharV    (uInt aRowNr, const Slicer& ns, Array<uChar>* dataPtr){
		Bool deleteIt;
		uChar* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceShortV    (uInt aRowNr, const Slicer& ns, Array<Short>* dataPtr){
		Bool deleteIt;
		Short* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceuShortV   (uInt aRowNr, const Slicer& ns, Array<uShort>* dataPtr){
		Bool deleteIt;
		uShort* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceIntV      (uInt aRowNr, const Slicer& ns, Array<Int>* dataPtr){
		Bool deleteIt;
		Int* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceuIntV     (uInt aRowNr, const Slicer& ns, Array<uInt>* dataPtr){
		Bool deleteIt;
		uInt* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSlicefloatV          (uInt aRowNr, const Slicer& ns, Array<float>* dataPtr){
		Bool deleteIt;
		float* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSlicedoubleV   (uInt aRowNr, const Slicer& ns, Array<double>* dataPtr){
		Bool deleteIt;
		double* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceComplexV  (uInt aRowNr, const Slicer& ns, Array<Complex>* dataPtr){
		Bool deleteIt;
		Complex* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getSliceDComplexV (uInt aRowNr, const Slicer& ns, Array<DComplex>* dataPtr){
		Bool deleteIt;
		DComplex* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV(aRowNr, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	// *** access a slice of a row for an array column ***


	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** access all rows for an array column ***
	// *** inactive by default
	// *** only active when canAccessArrayColumn() returns true in child class
	// put

	// get
	void AdiosStManColumn::getArrayColumnBoolV (Array<Bool>* dataPtr){
		Bool deleteIt;
		Bool* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnuCharV (Array<uChar>* dataPtr){
		Bool deleteIt;
		uChar* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnShortV (Array<Short>* dataPtr){
		Bool deleteIt;
		Short* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnuShortV (Array<uShort>* dataPtr){
		Bool deleteIt;
		uShort* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnIntV (Array<Int>* dataPtr){
		Bool deleteIt;
		Int* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnuIntV (Array<uInt>* dataPtr){
		Bool deleteIt;
		uInt* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnfloatV (Array<float>* dataPtr){
		Bool deleteIt;
		float* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumndoubleV (Array<double>* dataPtr){
		Bool deleteIt;
		double* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnComplexV (Array<Complex>* dataPtr){
		Bool deleteIt;
		Complex* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getArrayColumnDComplexV (Array<DComplex>* dataPtr){
		Bool deleteIt;
		DComplex* data = dataPtr->getStorage (deleteIt);
		getArrayColumnGeneralV (data);
		dataPtr->putStorage (data, deleteIt);
	}
	// *** access all rows for an array column ***
	
	
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------------------


	// *** access a slice of all rows for an array column ***
	// *** inactive by default
	// *** only active when canAccessColumnSlice() returns true in child class
	// put

	// get
	void AdiosStManColumn::getColumnSlicesBoolV	 (const Slicer& ns, Array<Bool>* dataPtr){
		Bool deleteIt;
		Bool* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicesuCharV	 (const Slicer& ns, Array<uChar>* dataPtr){
		Bool deleteIt;
		uChar* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicesShortV   (const Slicer& ns, Array<Short>* dataPtr){
		Bool deleteIt;
		Short* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicesuShortV  (const Slicer& ns, Array<uShort>* dataPtr){
		Bool deleteIt;
		uShort* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicesIntV     (const Slicer& ns, Array<Int>* dataPtr){
		Bool deleteIt;
		Int* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicesuIntV    (const Slicer& ns, Array<uInt>* dataPtr){
		Bool deleteIt;
		uInt* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicefloatV    (const Slicer& ns, Array<float>* dataPtr){
		Bool deleteIt;
		float* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSlicedoubleV   (const Slicer& ns, Array<double>* dataPtr){
		Bool deleteIt;
		double* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSliceComplexV  (const Slicer& ns, Array<Complex>* dataPtr){
		Bool deleteIt;
		Complex* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	void AdiosStManColumn::getColumnSliceDComplexV (const Slicer& ns, Array<DComplex>* dataPtr){
		Bool deleteIt;
		DComplex* data = dataPtr->getStorage (deleteIt);
		getSliceGeneralV (-1, ns, data);
		dataPtr->putStorage (data, deleteIt);
	}
	// *** access a slice of all rows for an array column ***

	// *** check if data is all zero ***
	// void
	bool AdiosStManColumn::isZero (const void *dataPtr){
		switch (itsCasaDataType){
			case TpBool:
			case TpArrayBool:
				if(isArrayColumn) return isZero((const Array<Bool>*)dataPtr);
				else return isZero((const Bool*)dataPtr);
			case TpChar:
			case TpArrayChar:
				if(isArrayColumn) return isZero((const Array<Char>*)dataPtr);
				else return isZero((const Char*)dataPtr);
			case TpUChar:
			case TpArrayUChar:
				if(isArrayColumn) return isZero((const Array<uChar>*)dataPtr);
				else return isZero((const uChar*)dataPtr);
			case TpShort:
			case TpArrayShort:
				if(isArrayColumn) return isZero((const Array<Short>*)dataPtr);
				else return isZero((const Short*)dataPtr);
			case TpUShort:
			case TpArrayUShort:
				if(isArrayColumn) return isZero((const Array<uShort>*)dataPtr);
				else return isZero((const uShort*)dataPtr);
			case TpInt:
			case TpArrayInt:
				if(isArrayColumn) return isZero((const Array<Int>*)dataPtr);
				else return isZero((const Int*)dataPtr);
			case TpUInt:
			case TpArrayUInt:
				if(isArrayColumn) return isZero((const Array<uInt>*)dataPtr);
				else return isZero((const uInt*)dataPtr);
			case TpFloat:
			case TpArrayFloat:
				if(isArrayColumn) return isZero((const Array<float>*)dataPtr);
				else return isZero((const float*)dataPtr);
			case TpDouble:
			case TpArrayDouble:
				if(isArrayColumn) return isZero((const Array<double>*)dataPtr);
				else return isZero((const double*)dataPtr);
			case TpComplex:
			case TpArrayComplex:
				if(isArrayColumn) return isZero((const Array<Complex>*)dataPtr);
				else return isZero((const Complex*)dataPtr);
			case TpDComplex:
			case TpArrayDComplex:
				if(isArrayColumn) return isZero((const Array<DComplex>*)dataPtr);
				else return isZero((const DComplex*)dataPtr);
		}
		return false;
	}
	// scalar
	inline bool AdiosStManColumn::isZero (const Bool* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const uChar* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const Short* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const uShort* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const Int* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const uInt* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const float* dataPtr){
		cout <<"float"<<endl;
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const double* dataPtr){
		if(*dataPtr==0) return true;
		else return false;
	}
	inline bool AdiosStManColumn::isZero (const Complex* dataPtr){
		return false;
	}
	inline bool AdiosStManColumn::isZero (const DComplex* dataPtr){
		return false;
	}
	// array
	bool AdiosStManColumn::isZero (const Array<Bool>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<uChar>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<Short>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<uShort>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<Int>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<uInt>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<float>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<double>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<Complex>* dataPtr){
		return false;
	}
	bool AdiosStManColumn::isZero (const Array<DComplex>* dataPtr){
		return false;
	}
	// *** check if data is all zero ***


}

