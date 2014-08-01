#include "AdiosStManColumn.h"
#include <casa/Arrays/Array.h>
#include <casa/Utilities/DataType.h>

namespace casa{

	AdiosStManColumn::AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
		:StManColumn (aDataType),
		itsAdiosWriteIDs (0),
		itsStManPtr (aParent),
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

	ADIOS_DATATYPES AdiosStManColumn::getAdiosDataType(){
		return itsAdiosDataType;
	}

	int AdiosStManColumn::getDataTypeSize(){
		return itsDataTypeSize;
	}

	AdiosStManColumn::~AdiosStManColumn (){
		if (itsAdiosWriteIDs){
			delete [] itsAdiosWriteIDs;
		}
	}

	void AdiosStManColumn::setShapeColumn (const IPosition& aShape)
	{
		itsNrElem = aShape.product();
		itsShape  = aShape;
	}

	IPosition AdiosStManColumn::getShapeColumn (){
		return itsShape;
	}

	IPosition AdiosStManColumn::shape (uInt RowID){
		return itsShape;
	}

	void AdiosStManColumn::initAdiosWriteIDs (uInt NrRows){
		itsAdiosWriteIDs = new int64_t[NrRows];
	}

	void AdiosStManColumn::putAdiosWriteIDs(uInt row, int64_t writeID){
		itsAdiosWriteIDs[row] = writeID;
	}

	// ------------ array puts -----------------//
	void AdiosStManColumn::putArrayBoolV (uInt rownr, const Array<Bool>* dataPtr){
		Bool deleteIt;
		const Bool* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayCharV (uInt rownr, const Array<Char>* dataPtr){
		Bool deleteIt;
		const Char* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayuCharV (uInt rownr, const Array<uChar>* dataPtr){
		Bool deleteIt;
		const uChar* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayShortV (uInt rownr, const Array<Short>* dataPtr){
		Bool deleteIt;
		const Short* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayuShortV (uInt rownr, const Array<uShort>* dataPtr){
		Bool deleteIt;
		const uShort* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayIntV (uInt rownr, const Array<Int>* dataPtr){
		Bool deleteIt;
		const Int* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayuIntV (uInt rownr, const Array<uInt>* dataPtr){
		Bool deleteIt;
		const uInt* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayfloatV (uInt rownr, const Array<Float>* dataPtr){
		Bool deleteIt;
		const Float* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArraydoubleV (uInt rownr, const Array<Double>* dataPtr){
		Bool deleteIt;
		const Double* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayComplexV (uInt rownr, const Array<Complex>* dataPtr){
		Bool deleteIt;
		const Complex* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayDComplexV (uInt rownr, const Array<DComplex>* dataPtr){
		Bool deleteIt;
		const DComplex* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayStringV (uInt rownr, const Array<String>* dataPtr){
		Bool deleteIt;
		const String* data = dataPtr->getStorage (deleteIt);
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)data);
		dataPtr->freeStorage (data, deleteIt);
	}
	// ------------ array puts -----------------//


	// ------------ scalar puts -----------------//
	void AdiosStManColumn::putBoolV (uInt rownr, const Bool* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putuCharV (uInt rownr, const uChar* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putShortV (uInt rownr, const Short* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putuShortV (uInt rownr, const uShort* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putIntV (uInt rownr, const Int* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putuIntV (uInt rownr, const uInt* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putfloatV (uInt rownr, const float* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putdoubleV (uInt rownr, const double* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putComplexV (uInt rownr, const Complex* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putDComplexV (uInt rownr, const DComplex* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumn::putStringV (uInt rownr, const String* dataPtr){
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}
	// ------------ scalar puts -----------------//




}




