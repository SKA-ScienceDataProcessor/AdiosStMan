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


namespace casacore {

    AdiosStManColumn::AdiosStManColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
        :StManColumn (aDataType),
        itsAdiosWriteIDs (0),
        itsStManPtr (aParent),
        itsCasaDataType(aDataType),
        itsShape(0),
        scalarCache(0)
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
        if (scalarCache){
            switch (itsCasaDataType){
                case TpBool:
                    delete [] (Bool*)scalarCache;
                    break;
                case TpChar:
                    delete [] (Char*)scalarCache;
                    break;
                case TpUChar:
                    delete [] (uChar*)scalarCache;
                    break;
                case TpShort:
                    delete [] (Short*)scalarCache;
                    break;
                case TpUShort:
                    delete [] (uShort*)scalarCache;
                    break;
                case TpInt:
                    delete [] (Int*)scalarCache;
                    break;
                case TpUInt:
                    delete [] (uInt*)scalarCache;
                    break;
                case TpFloat:
                    delete [] (float*)scalarCache;
                    break;
                case TpDouble:
                    delete [] (double*)scalarCache;
                    break;
                case TpComplex:
                    delete [] (Complex*)scalarCache;
                    break;
                case TpDComplex:
                    delete [] (DComplex*)scalarCache;
                    break;
                case TpString:
                    break;
            }
        }
    }

    void AdiosStManColumn::setColumnName (String aName){
        itsColumnName = aName;
    }

    String AdiosStManColumn::getColumnName (){
        return itsColumnName;
    }

    IPosition AdiosStManColumn::getShapeColumn (){
        return itsShape;
    }

    int AdiosStManColumn::getDataTypeSize(){
        return itsDataTypeSize;
    }

    int AdiosStManColumn::getDataType(){
        return itsCasaDataType;
    }

    // ------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------


    // *** access a row for a scalar column ***
    // put
    void AdiosStManColumn::putBoolV (uInt rownr, const Bool* dataPtr){
        if(scalarCache == 0) {scalarCache = new Bool[itsStManPtr->getNrRows()];}
        ((Bool*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putuCharV (uInt rownr, const uChar* dataPtr){
        if(scalarCache == 0) {scalarCache = new uChar[itsStManPtr->getNrRows()];}
        ((uChar*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putShortV (uInt rownr, const Short* dataPtr){
        if(scalarCache == 0) {scalarCache = new Short[itsStManPtr->getNrRows()];}
        ((Short*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putuShortV (uInt rownr, const uShort* dataPtr){
        if(scalarCache == 0) {scalarCache = new uShort[itsStManPtr->getNrRows()];}
        ((uShort*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putIntV (uInt rownr, const Int* dataPtr){
        if(scalarCache == 0) {scalarCache = new Int[itsStManPtr->getNrRows()];}
        ((Int*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putuIntV (uInt rownr, const uInt* dataPtr){
        if(scalarCache == 0) {scalarCache = new uInt[itsStManPtr->getNrRows()];}
        ((uInt*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putfloatV (uInt rownr, const float* dataPtr){
        if(scalarCache == 0) {scalarCache = new float[itsStManPtr->getNrRows()];}
        ((float*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putdoubleV (uInt rownr, const double* dataPtr){
        if(scalarCache == 0) {scalarCache = new double[itsStManPtr->getNrRows()];}
        ((double*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putComplexV (uInt rownr, const Complex* dataPtr){
        if(scalarCache == 0) {scalarCache = new Complex[itsStManPtr->getNrRows()];}
        ((Complex*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putDComplexV (uInt rownr, const DComplex* dataPtr){
        if(scalarCache == 0) {scalarCache = new DComplex[itsStManPtr->getNrRows()];}
        ((DComplex*)scalarCache)[rownr] = *dataPtr;
        putScalarMetaV(rownr, dataPtr);
    }
    void AdiosStManColumn::putStringV (uInt rownr, const String* dataPtr){
        cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at the moment!" << endl;
    }

    // get
    void AdiosStManColumn::getBoolV (uInt aRowNr, Bool* aValue){
        if(scalarCache == 0) {scalarCache = new Bool[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Bool*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getuCharV (uInt aRowNr, uChar* aValue){
        if(scalarCache == 0) {scalarCache = new uChar[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((uChar*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getShortV (uInt aRowNr, Short* aValue){
        if(scalarCache == 0) {scalarCache = new Short[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Short*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getuShortV (uInt aRowNr, uShort* aValue){
        if(scalarCache == 0) {scalarCache = new uShort[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((uShort*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getIntV (uInt aRowNr, Int* aValue){
        if(scalarCache == 0) {scalarCache = new Int[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Int*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getuIntV (uInt aRowNr, uInt* aValue){
        if(scalarCache == 0) {scalarCache = new uInt[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((uInt*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getfloatV (uInt aRowNr, float* aValue){
        if(scalarCache == 0) {scalarCache = new float[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((float*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getdoubleV (uInt aRowNr, double* aValue){
        if(scalarCache == 0) {scalarCache = new double[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((double*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getComplexV (uInt aRowNr, Complex* aValue){
        if(scalarCache == 0) {scalarCache = new Complex[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Complex*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getDComplexV (uInt aRowNr,DComplex* aValue){
        if(scalarCache == 0) {scalarCache = new DComplex[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((DComplex*)scalarCache)[aRowNr];
    }
    void AdiosStManColumn::getStringV (uInt aRowNr, String* aValue){
        cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at this point!" << endl;
    }


    // *** access a row for an array column ***
    void AdiosStManColumn::putArrayV (uInt rownr, const void* dataPtr){
        itsStManPtr->logdbg("AdiosStManColumn::putArrayV","");
        Bool deleteIt;
        const void *data;
        switch (itsCasaDataType){
            case TpArrayBool:
            case TpBool:
                data = ((const Array<Bool>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Bool>*)dataPtr)->freeStorage((const Bool*&)data, deleteIt);
                break;
            case TpArrayChar:
            case TpChar:
                data = ((const Array<Char>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Char>*)dataPtr)->freeStorage((const Char*&)data, deleteIt);
                break;
            case TpArrayUChar:
            case TpUChar:
                data = ((const Array<uChar>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<uChar>*)dataPtr)->freeStorage((const uChar*&)data, deleteIt);
                break;
            case TpArrayShort:
            case TpShort:
                data = ((const Array<Short>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Short>*)dataPtr)->freeStorage((const Short*&)data, deleteIt);
                break;
            case TpArrayUShort:
            case TpUShort:
                data = ((const Array<uShort>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<uShort>*)dataPtr)->freeStorage((const uShort*&)data, deleteIt);
                break;
            case TpArrayInt:
            case TpInt:
                data = ((const Array<Int>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Int>*)dataPtr)->freeStorage((const Int*&)data, deleteIt);
                break;
            case TpArrayUInt:
            case TpUInt:
                data = ((const Array<uInt>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<uInt>*)dataPtr)->freeStorage((const uInt*&)data, deleteIt);
                break;
            case TpArrayFloat:
            case TpFloat:
                data = ((const Array<Float>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Float>*)dataPtr)->freeStorage((const Float*&)data, deleteIt);
                break;
            case TpArrayDouble:
            case TpDouble:
                data = ((const Array<Double>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Double>*)dataPtr)->freeStorage((const Double*&)data, deleteIt);
                break;
            case TpArrayComplex:
            case TpComplex:
                data = ((const Array<Complex>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<Complex>*)dataPtr)->freeStorage((const Complex*&)data, deleteIt);
                break;
            case TpArrayDComplex:
            case TpDComplex:
                data = ((const Array<DComplex>*)dataPtr)->getStorage (deleteIt);
                putArrayMetaV(rownr, data);
                ((const Array<DComplex>*)dataPtr)->freeStorage((const DComplex*&)data, deleteIt);
                break;
        }
    }
    void AdiosStManColumn::getArrayV (uInt rownr, void* dataPtr){
        itsStManPtr->logdbg("AdiosStManColumn::getArrayV","");
        Slicer ns(IPosition(itsShape.size(),0,0,0,0,0,0,0,0,0,0), itsShape);
        getArrayWrapper(rownr, 1, ns, dataPtr);
    }

    // *** access a slice of a row for an array column ***
    // *** inactive by default
    // *** only active when canAccessSlice() returns true in child class
    void AdiosStManColumn::getSliceV(uInt aRowNr, const Slicer& ns, void* dataPtr){
        itsStManPtr->logdbg("AdiosStManColumn::getSliceV","row number=", aRowNr);
        getArrayWrapper(aRowNr, 1, ns, dataPtr);
    }

    // *** access all rows for an array column ***
    // *** inactive by default
    // *** only active when canAccessArrayColumn() returns true in child class
    void AdiosStManColumn::getArrayColumnV(void* dataPtr){
        itsStManPtr->logdbg("AdiosStManColumn::getArrayColumnV","");
        Slicer ns(IPosition(itsShape.size(),0,0,0,0,0,0,0,0,0,0), itsShape);
        getArrayWrapper(0, 0, ns, dataPtr);
    }

    // *** access a slice of all rows for an array column ***
    // *** inactive by default
    // *** only active when canAccessColumnSlice() returns true in child class
    void AdiosStManColumn::getColumnSliceV(const Slicer& ns, void *dataPtr){
        itsStManPtr->logdbg("AdiosStManColumn::getColumnSliceV","");
        getArrayWrapper(0, 0, ns, dataPtr);
    }

    void AdiosStManColumn::getArrayWrapper(uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* dataPtr){
        Bool deleteIt;
        void *data;
        switch (itsCasaDataType){
            case TpArrayBool:
            case TpBool:
                data = ((Array<Bool>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<Bool>*)dataPtr)->putStorage ((Bool *&)data, deleteIt);
                break;
            case TpArrayChar:
            case TpChar:
                data = ((Array<Char>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<Char>*)dataPtr)->putStorage ((Char *&)data, deleteIt);
                break;
            case TpArrayUChar:
            case TpUChar:
                data = ((Array<uChar>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<uChar>*)dataPtr)->putStorage ((uChar *&)data, deleteIt);
                break;
            case TpArrayShort:
            case TpShort:
                data = ((Array<Short>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<Short>*)dataPtr)->putStorage ((Short *&)data, deleteIt);
                break;
            case TpArrayUShort:
            case TpUShort:
                data = ((Array<uShort>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<uShort>*)dataPtr)->putStorage ((uShort *&)data, deleteIt);
                break;
            case TpArrayInt:
            case TpInt:
                data = ((Array<Int>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<Int>*)dataPtr)->putStorage ((Int *&)data, deleteIt);
                break;
            case TpArrayUInt:
            case TpUInt:
                data = ((Array<uInt>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(0, 0, ns, data);
                ((Array<uInt>*)dataPtr)->putStorage ((uInt *&)data, deleteIt);
                break;
            case TpArrayFloat:
            case TpFloat:
                data = ((Array<Float>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(rowStart, nrRows, ns, data);
                ((Array<Float>*)dataPtr)->putStorage ((Float *&)data, deleteIt);
                break;
            case TpArrayDouble:
            case TpDouble:
                data = ((Array<Double>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(rowStart, nrRows, ns, data);
                ((Array<Double>*)dataPtr)->putStorage ((Double *&)data, deleteIt);
                break;
            case TpArrayComplex:
            case TpComplex:
                data = ((Array<Complex>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(rowStart, nrRows, ns, data);
                ((Array<Complex>*)dataPtr)->putStorage ((Complex *&)data, deleteIt);
                break;
            case TpArrayDComplex:
            case TpDComplex:
                data = ((Array<DComplex>*)dataPtr)->getStorage (deleteIt);
                getArrayMetaV(rowStart, nrRows, ns, data);
                ((Array<DComplex>*)dataPtr)->putStorage ((DComplex *&)data, deleteIt);
                break;
        }
    }
}

