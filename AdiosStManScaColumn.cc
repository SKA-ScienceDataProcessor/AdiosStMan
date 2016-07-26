//    (c) University of Western Australia
//    International Centre of Radio Astronomy Research
//    M468, 35 Stirling Hwy
//    Crawley, Perth WA 6009
//    Australia
//
//    Shanghai Astronomical Observatory, Chinese Academy of Sciences
//    80 Nandan Road, Shanghai 200030, China
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
//    lbq@shao.ac.cn, jason.wang@icrar.org

#include "AdiosStManScaColumn.h"


namespace casacore {

    AdiosStManScaColumn::AdiosStManScaColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
        :gotScalarColumn(false),
        AdiosStManColumn (aParent, aDataType, aColNr){
        }

    AdiosStManScaColumn::~AdiosStManScaColumn (){
        if (columnCache){
            switch (itsCasaDataType){
                case TpBool:
                    delete [] (Bool*)columnCache;
                    break;
                case TpChar:
                    delete [] (Char*)columnCache;
                    break;
                case TpUChar:
                    delete [] (uChar*)columnCache;
                    break;
                case TpShort:
                    delete [] (Short*)columnCache;
                    break;
                case TpUShort:
                    delete [] (uShort*)columnCache;
                    break;
                case TpInt:
                    delete [] (Int*)columnCache;
                    break;
                case TpUInt:
                    delete [] (uInt*)columnCache;
                    break;
                case TpFloat:
                    delete [] (float*)columnCache;
                    break;
                case TpDouble:
                    delete [] (double*)columnCache;
                    break;
                case TpComplex:
                    delete [] (Complex*)columnCache;
                    break;
                case TpDComplex:
                    delete [] (DComplex*)columnCache;
                    break;
                case TpString:
                    break;
            }
        }
        if (itsAdiosWriteIDs){
            delete [] itsAdiosWriteIDs;
        }
    }

    // *** access a row for a scalar column ***
    // put
    void AdiosStManScaColumn::putBoolV (uInt rownr, const Bool* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){ 
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putuCharV (uInt rownr, const uChar* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putShortV (uInt rownr, const Short* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putuShortV (uInt rownr, const uShort* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putIntV (uInt rownr, const Int* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putuIntV (uInt rownr, const uInt* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putfloatV (uInt rownr, const float* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putdoubleV (uInt rownr, const double* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putComplexV (uInt rownr, const Complex* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putDComplexV (uInt rownr, const DComplex* dataPtr){
        if((rownr-itsStManPtr->getMpiRank()*itsStManPtr->getRowsPerProcess())%itsStManPtr->getBufRows()==0){    
          itsStManPtr->adiosWriteClose();
        }
        itsStManPtr->adiosWriteOpen(rownr);
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[(rownr-(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows())] , (void*)dataPtr);
    }
    void AdiosStManScaColumn::putStringV (uInt rownr, const String* dataPtr){
        cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at the moment!" << endl;
    }

    // get
    void AdiosStManScaColumn::getBoolV (uInt aRowNr, Bool* aValue){
        if(columnCache == 0) {columnCache = new Bool[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Bool*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getuCharV (uInt aRowNr, uChar* aValue){
        if(columnCache == 0) {columnCache = new uChar[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((uChar*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getShortV (uInt aRowNr, Short* aValue){
        if(columnCache == 0) {columnCache = new Short[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Short*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getuShortV (uInt aRowNr, uShort* aValue){
        if(columnCache == 0) {columnCache = new uShort[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((uShort*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getIntV (uInt aRowNr, Int* aValue){
        if(columnCache == 0) {columnCache = new Int[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Int*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getuIntV (uInt aRowNr, uInt* aValue){
        if(columnCache == 0) {columnCache = new uInt[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((uInt*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getfloatV (uInt aRowNr, float* aValue){
        if(columnCache == 0) {columnCache = new float[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((float*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getdoubleV (uInt aRowNr, double* aValue){
        if(columnCache == 0) {columnCache = new double[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((double*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getComplexV (uInt aRowNr, Complex* aValue){
        if(columnCache == 0) {columnCache = new Complex[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((Complex*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getDComplexV (uInt aRowNr,DComplex* aValue){
        if(columnCache == 0) {columnCache = new DComplex[itsStManPtr->getNrRows()];}
        getScalarMetaV(aRowNr, aValue);
        *aValue = ((DComplex*)columnCache)[aRowNr];
    }
    void AdiosStManScaColumn::getStringV (uInt aRowNr, String* aValue){
        cout << "AdiosStManColumn Error: Sorry, AdiosStMan does not support string type at this point!" << endl;
    }

    void AdiosStManScaColumn::initAdiosRead(){
    }

    void AdiosStManScaColumn::initAdiosWrite(uInt aNrRows){
        itsStManPtr->logdbg("AdiosStManScaColumn::initAdiosWrite","start");
        if(!itsAdiosWriteIDs){
            itsAdiosWriteIDs = new int64_t[itsStManPtr->getBufRows()];
        }
        for(uInt j=0; j<aNrRows; j++){
            stringstream NrRows, RowID;
            NrRows << aNrRows;
            RowID << j+(itsStManPtr->getAdiosNrBufRows()-1)*itsStManPtr->getBufRows();
            itsAdiosWriteIDs[j] = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, "1", NrRows.str().c_str(), RowID.str().c_str() );
            cout<<RowID.str().c_str()<<endl;
        }
    }

    void AdiosStManScaColumn::getScalarMetaV (uint64_t row, void* data){
        itsStManPtr->logdbg("AdiosStManScaColumn::getScalarMetaV","start");
        if(gotScalarColumn == false){
            if(itsStManPtr->getAdiosReadFile()!=0){
                readStart[0] = 0;
                readCount[0] = itsStManPtr->getNrRows();
                ADIOS_SELECTION *sel = adios_selection_boundingbox (1, readStart, readCount);
                adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, columnCache);
                adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
                gotScalarColumn = true;
            }
            else{
                cout << "AdiosStManColumn Error: AdiosStMan is not working in the read mode!" << endl;
            }
        }
    }

    void AdiosStManScaColumn::flush(){
    }
}

