//    AdiosStManDirColumn.cc: StManColumn class for AdiosStMan,
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


#include "AdiosStManDirColumn.h"

namespace casa{

    AdiosStManDirColumn::AdiosStManDirColumn (AdiosStMan* aParent, int aDataType, uInt aColNr)
        :gotScalarColumn(false),
        AdiosStManColumn (aParent, aDataType, aColNr){
        }

    AdiosStManDirColumn::~AdiosStManDirColumn (){
        if (itsAdiosWriteIDs){
            if (itsShape.nelements() == 0){
                delete itsAdiosWriteIDs;
            }
            else{
                delete [] itsAdiosWriteIDs;
            }
        }
    }

    Bool AdiosStManDirColumn::canAccessArrayColumn(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    Bool AdiosStManDirColumn::canAccessSlice(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    Bool AdiosStManDirColumn::canAccessColumnSlice(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    void AdiosStManDirColumn::initAdiosWrite(uInt aNrRows){
        itsStManPtr->logdbg("AdiosStManDirColumn::initAdiosWrite","start");
        if(!itsAdiosWriteIDs){
            itsAdiosWriteIDs = new int64_t[aNrRows];
        }
        for(uInt j=0; j<aNrRows; j++){
            stringstream NrRows, RowID;
            NrRows << aNrRows;
            RowID << j;
            IPosition dimensions_pos;
            for (int k=itsShape.nelements() - 1; k>=0; k--){
                dimensions_pos.append(IPosition(1, itsShape[k]));
            }
            string dimensions_pos_str = dimensions_pos.toString().substr(1, itsShape.toString().length()-2);
            string dimensions = "1," + dimensions_pos_str;
            string global_dimensions = NrRows.str() + "," + dimensions_pos_str;
            string local_offsets = RowID.str();
            for (int k=0; k<itsShape.nelements(); k++){
                local_offsets += ",0";
            }
            itsAdiosWriteIDs[j] = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, dimensions.c_str(), global_dimensions.c_str(), local_offsets.c_str());
        }
    }


    void AdiosStManDirColumn::putArrayMetaV (uint64_t row, const void* data){
        itsStManPtr->adiosWriteOpen();
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[row] , (void*)data);
    }

    void AdiosStManDirColumn::getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* data){
        if(itsStManPtr->getAdiosReadFile()){
            if(nrRows == 0){
                // if getting entire column
                readStart[0] = 0;
                readCount[0] = itsStManPtr->getNrRows();
            }
            else{
                // if getting some rows
                readStart[0] = rowStart;
                readCount[0] = nrRows;
            }
            for (int i=1; i<=itsShape.size(); i++){
                readStart[itsShape.size() - i + 1] = ns.start()(i-1);
                readCount[itsShape.size() - i + 1] = ns.length()(i-1);
            }
            ADIOS_SELECTION *sel = adios_selection_boundingbox (itsShape.size()+1, readStart, readCount);
            adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, data);
            adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
        }
        else{
            cout << "AdiosStManColumn Error: AdiosStMan is not working in read mode!" << endl;
        }
    }

    void AdiosStManDirColumn::putScalarMetaV (uint64_t row, const void* data){
    }

    void AdiosStManDirColumn::getScalarMetaV (uint64_t row, void* data){
    }

    void AdiosStManDirColumn::flush(){
    }
}

