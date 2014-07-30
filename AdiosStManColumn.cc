#include "AdiosStManColumn.h"

namespace casa{

	AdiosStManColumn::AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
		:StManColumn (aDataType),
		itsAdiosWriteIDs (0),
		itsStManPtr (aParent),
		itsShape(0)
	{
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

//		cout << "AdiosStManColumn::setShapeColumn(), Column: " << columnName() << ", Shape: " << aShape << endl;
//		cout << itsShape(0) << endl;
	}

	IPosition AdiosStManColumn::getShapeColumn (){
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
	}

	void AdiosStManColumn::putArrayuCharV (uInt rownr, const Array<uChar>* dataPtr){
	}

	void AdiosStManColumn::putArrayShortV (uInt rownr, const Array<Short>* dataPtr){
	}

	void AdiosStManColumn::putArrayuShortV (uInt rownr, const Array<uShort>* dataPtr){
	}

	void AdiosStManColumn::putArrayIntV (uInt rownr, const Array<Int>* dataPtr){
	}

	void AdiosStManColumn::putArrayuIntV (uInt rownr, const Array<uInt>* dataPtr){
	}

	void AdiosStManColumn::putArrayfloatV (uInt rownr, const Array<float>* dataPtr){
	}

	void AdiosStManColumn::putArraydoubleV (uInt rownr, const Array<double>* dataPtr){
	}

	void AdiosStManColumn::putArrayComplexV (uInt rownr, const Array<Complex>* dataPtr){
	}

	void AdiosStManColumn::putArrayDComplexV (uInt rownr, const Array<DComplex>* dataPtr){
	}

	void AdiosStManColumn::putArrayStringV (uInt rownr, const Array<String>* dataPtr){
	}
	// ------------ array puts -----------------//


	// ------------ scalar puts -----------------//
	void AdiosStManColumn::putBoolV (uInt rownr, const Bool* dataPtr){
	}

	void AdiosStManColumn::putuCharV (uInt rownr, const uChar* dataPtr){
	}

	void AdiosStManColumn::putShortV (uInt rownr, const Short* dataPtr){
	}

	void AdiosStManColumn::putuShortV (uInt rownr, const uShort* dataPtr){
	}

	void AdiosStManColumn::putIntV (uInt rownr, const Int* dataPtr){
	}

	void AdiosStManColumn::putuIntV (uInt rownr, const uInt* dataPtr){

		cout << "rownr = " << rownr << endl;
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
//		adios_write(itsStManPtr->itsAdiosFile, columnName().c_str(), &dataPtr);
		
	}

	void AdiosStManColumn::putfloatV (uInt rownr, const float* dataPtr){
	}

	void AdiosStManColumn::putdoubleV (uInt rownr, const double* dataPtr){
	}

	void AdiosStManColumn::putComplexV (uInt rownr, const Complex* dataPtr){
	}

	void AdiosStManColumn::putDComplexV (uInt rownr, const DComplex* dataPtr){
	}

	void AdiosStManColumn::putStringV (uInt rownr, const String* dataPtr){
	}
	// ------------ scalar puts -----------------//




}




