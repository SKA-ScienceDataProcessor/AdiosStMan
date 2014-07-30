
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
			virtual void setShapeColumn (const IPosition& aShape);
			IPosition getShapeColumn();
			~AdiosStManColumn ();

			// Put an array value in the given row.
			// <group>
			virtual void putArrayBoolV     (uInt rownr, const Array<Bool>* dataPtr);
			virtual void putArrayuCharV    (uInt rownr, const Array<uChar>* dataPtr);
			virtual void putArrayShortV    (uInt rownr, const Array<Short>* dataPtr);
			virtual void putArrayuShortV   (uInt rownr, const Array<uShort>* dataPtr);
			virtual void putArrayIntV      (uInt rownr, const Array<Int>* dataPtr);
			virtual void putArrayuIntV     (uInt rownr, const Array<uInt>* dataPtr);
			virtual void putArrayfloatV    (uInt rownr, const Array<float>* dataPtr);
			virtual void putArraydoubleV   (uInt rownr, const Array<double>* dataPtr);
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
			virtual void putfloatV    (uInt aRowNr, const float* aDataPtr);
			virtual void putdoubleV   (uInt aRowNr, const double* aDataPtr);
			virtual void putComplexV  (uInt aRowNr, const Complex* aDataPtr);
			virtual void putDComplexV (uInt aRowNr, const DComplex* aDataPtr);
			virtual void putStringV   (uInt aRowNr, const String* aDataPtr);
			// </group>

			void initAdiosWriteIDs(uInt NrRows);
			void putAdiosWriteIDs(uInt row, int64_t writeID);

		private:

			int64_t *itsAdiosWriteIDs;

			// The shape of the column.
			IPosition itsShape;

			// Pointer to the parent storage manager.
			AdiosStMan *itsStManPtr;

			// Number of elements in a value for this column.
			uInt itsNrElem;
	};



}


#endif
