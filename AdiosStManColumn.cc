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


	void AdiosStManColumn::initAdiosRead(){

		itsAdiosVarInfo = adios_inq_var(itsStManPtr->getAdiosReadFile(), itsColumnName.c_str());

		int ndim = itsShape.size();
		// if array column, allocate dimension vectors 
		if (ndim > 0){
			readStart = new uint64_t[ndim+1];
			readCount = new uint64_t[ndim+1];
		}
	}

	int AdiosStManColumn::getDataTypeSize(){
		return itsDataTypeSize;
	}

	AdiosStManColumn::~AdiosStManColumn (){
		if (readStart)   delete [] readStart;
		if (readCount)   delete [] readCount;
		if (itsAdiosWriteIDs)	free(itsAdiosWriteIDs);
	}

	void AdiosStManColumn::setShapeColumn (const IPosition& aShape){
		itsNrElem = aShape.product();
		itsShape  = aShape;
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


	void AdiosStManColumn::initAdiosWrite(uInt aNrRows){
		int mpiRank;
		MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);  


		for(int j=0; j<aNrRows; j++){
			// if not allocated
			if(itsAdiosWriteIDs == 0){
				itsNrIDsAllocated = aNrRows;
				itsAdiosWriteIDs = (int64_t*) malloc(sizeof(int64_t) * itsNrIDsAllocated);
			}

			stringstream NrRows, RowID;
			NrRows << aNrRows;
			RowID << itsNrIDs;


			if (itsShape.nelements() == 0){   
				
				itsAdiosWriteIDs[itsNrIDs] = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, "1", NrRows.str().c_str(), RowID.str().c_str() ); ////
			}
			else{

				string columnShape = itsShape.toString().substr(1, itsShape.toString().length()-2);
				string dimensions = "1," + columnShape;
				string global_dimensions = NrRows.str() + "," + columnShape;
				string local_offsets = RowID.str(); 
				for (int k=0; k<itsShape.nelements(); k++){
					local_offsets += ",0";
				}
				itsAdiosWriteIDs[itsNrIDs] = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, dimensions.c_str(), global_dimensions.c_str(), local_offsets.c_str());
			}
			itsNrIDs++;
		}
	}

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


	void AdiosStManColumn::put (uInt rownr, const Array<Bool>* dataPtr){
		putArrayBoolV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<uChar>* dataPtr){
		putArrayuCharV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Short>* dataPtr){
		putArrayShortV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<uShort>* dataPtr){
		putArrayuShortV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Int>* dataPtr){
		putArrayIntV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<uInt>* dataPtr){
		putArrayuIntV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Float>* dataPtr){
		putArrayfloatV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Double>* dataPtr){
		putArraydoubleV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<Complex>* dataPtr){
		putArrayComplexV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<DComplex>* dataPtr){
		putArrayDComplexV(rownr, dataPtr);
	}
	void AdiosStManColumn::put (uInt rownr, const Array<String>* dataPtr){
		putArrayStringV(rownr, dataPtr);
	}




	// ------------ array puts -----------------//
	void AdiosStManColumn::putArrayBoolV (uInt rownr, const Array<Bool>* dataPtr){
		Bool deleteIt;
		const Bool* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayuCharV (uInt rownr, const Array<uChar>* dataPtr){
		Bool deleteIt;
		const uChar* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayShortV (uInt rownr, const Array<Short>* dataPtr){
		Bool deleteIt;
		const Short* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayuShortV (uInt rownr, const Array<uShort>* dataPtr){
		Bool deleteIt;
		const uShort* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayIntV (uInt rownr, const Array<Int>* dataPtr){
		Bool deleteIt;
		const Int* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayuIntV (uInt rownr, const Array<uInt>* dataPtr){
		Bool deleteIt;
		const uInt* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayfloatV (uInt rownr, const Array<Float>* dataPtr){
		Bool deleteIt;
		const float* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArraydoubleV (uInt rownr, const Array<Double>* dataPtr){
		Bool deleteIt;
		const Double* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayComplexV (uInt rownr, const Array<Complex>* dataPtr){
		Bool deleteIt;
		const Complex* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayDComplexV (uInt rownr, const Array<DComplex>* dataPtr){
		Bool deleteIt;
		const DComplex* data = dataPtr->getStorage (deleteIt);
		putGeneralV(rownr, data);
		dataPtr->freeStorage (data, deleteIt);
	}

	void AdiosStManColumn::putArrayStringV (uInt rownr, const Array<String>* dataPtr){
		cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at the moment!" << endl;
	}



	// ------------ array puts -----------------//


	// ------------ scalar puts -----------------//
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

	void AdiosStManColumn::putGeneralV (uInt rownr, const void* dataPtr){
		itsStManPtr->adiosOpen();
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	// ------------ scalar puts -----------------//


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


	void AdiosStManColumn::getArrayGeneralV (uInt aRowNr, void* data){

		if(itsStManPtr->getAdiosReadFile()){
			readStart[0] = aRowNr;
			readCount[0] = 1;

			for (int i=1; i<=itsShape.size(); i++){
				readStart[i] = 0;
				readCount[i] = itsShape(i-1);
			}

			ADIOS_SELECTION *sel = adios_selection_boundingbox (itsAdiosVarInfo->ndim, readStart, readCount);
			adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, data);
			adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
		}
		else{
			cout << "AdiosStManColumn Error: AdiosStMan is working in write mode!" << endl;
		}
	}

	//////////

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

	void AdiosStManColumn::getGeneralV (uInt aRowNr, void* aValue){
		if(itsStManPtr->getAdiosReadFile()){
			uint64_t rowid = aRowNr;
			ADIOS_SELECTION *sel = adios_selection_points (itsAdiosVarInfo->ndim, 1, &rowid);
			adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, aValue);
			adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
		}
		else{
			cout << "AdiosStManColumn Error: AdiosStMan is working in write mode!" << endl;
		}
	}

}




