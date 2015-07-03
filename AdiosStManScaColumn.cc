//    AdiosStManScaColumn.cc: StManColumn class for AdiosStMan,
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

#include "casacore_version.h"

#ifdef CASACORE_VERSION_1
#include <casa/Arrays/Array.h>
#include <casa/Utilities/DataType.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/casa/Arrays/Array.h>
#include <casacore/casa/Utilities/DataType.h>
#endif


#include "AdiosStManScaColumn.h"

namespace casa{

    AdiosStManScaColumn::AdiosStManScaColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
        :gotScalarColumn(false),
        AdiosStManColumn (aParent, aDataType, aColNr){
        }

    AdiosStManScaColumn::~AdiosStManScaColumn (){
        if (itsAdiosWriteIDs){
            delete itsAdiosWriteIDs;
        }
    }

    void AdiosStManScaColumn::initAdiosWrite(uInt aNrRows){
        itsStManPtr->logdbg("AdiosStManScaColumn::initAdiosWrite","start");
        if(!itsAdiosWriteIDs){
            itsAdiosWriteIDs = new int64_t;
        }
        for(uInt j=0; j<aNrRows; j++){
            stringstream NrRows;
            NrRows << aNrRows;
            *itsAdiosWriteIDs = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, NrRows.str().c_str(), NrRows.str().c_str(), "0" );
        }
    }

    void AdiosStManScaColumn::putArrayMetaV (uint64_t row, const void* data){
    }

    void AdiosStManScaColumn::getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* data){
    }

    void AdiosStManScaColumn::putScalarMetaV (uint64_t row, const void* data){
    }

    void AdiosStManScaColumn::getScalarMetaV (uint64_t row, void* data){
        itsStManPtr->logdbg("AdiosStManScaColumn::getScalarMetaV","start");
        if(gotScalarColumn == false){
            if(itsStManPtr->getAdiosReadFile()!=0){
                readStart[0] = 0;
                readCount[0] = itsStManPtr->getNrRows();
                ADIOS_SELECTION *sel = adios_selection_boundingbox (1, readStart, readCount);
                adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, scalarCache);
                adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
                gotScalarColumn = true;
            }
            else{
                cout << "AdiosStManColumn Error: AdiosStMan is not working in the read mode!" << endl;
            }
        }
    }

    void AdiosStManScaColumn::flush(){
        itsStManPtr->logdbg("AdiosStManScaColumn::flush","");
        itsStManPtr->adiosWriteOpen();
        adios_write_byid(itsStManPtr->getAdiosFile(), *itsAdiosWriteIDs , (void*)scalarCache);
    }
}

