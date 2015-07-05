//    AdiosStManIndColumn.cc: StManColumn class for AdiosStMan,
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

#include "AdiosStManIndColumn.h"


namespace casacore {

    AdiosStManIndColumn::AdiosStManIndColumn(AdiosStMan* aParent, int aDataType, uInt aColNr)
        :AdiosStManColumn (aParent, aDataType, aColNr)
    {
    }

    AdiosStManIndColumn::~AdiosStManIndColumn(){
        if (itsAdiosWriteIDs)
            delete [] itsAdiosWriteIDs;
    }

    void AdiosStManIndColumn::initAdiosRead(){
    }

    void AdiosStManIndColumn::initAdiosWrite(uInt aNrRows){
        int mpiRank;
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        for(uInt j=0; j<aNrRows; j++){
            if(itsAdiosWriteIDs == 0){
                itsAdiosWriteIDs = new int64_t[aNrRows];
            }
            stringstream varName;
            varName << itsColumnName << "[" << j << "]";
            if (itsShape.nelements() == 0){
                itsAdiosWriteIDs[j] = adios_define_var(itsStManPtr->getAdiosGroup(), varName.str().c_str(), itsColumnName.c_str(), itsAdiosDataType, "", "", ""); ////
            }
            else{
                IPosition dimensions_pos;
                for (int k=itsShape.nelements() - 1; k>=0; k--){
                    dimensions_pos.append(IPosition(1, itsShape[k]));
                }
                string dimensions_pos_str = dimensions_pos.toString().substr(1, itsShape.toString().length()-2);
                string local_offsets = "0";
                for (int k=1; k<itsShape.nelements(); k++){
                    local_offsets += ",0";
                }
                itsAdiosWriteIDs[j] = adios_define_var(itsStManPtr->getAdiosGroup(), varName.str().c_str(), itsColumnName.c_str(), itsAdiosDataType, dimensions_pos_str.c_str(), dimensions_pos_str.c_str(), local_offsets.c_str());
            }
        }
    }

    Bool AdiosStManIndColumn::canAccessSlice(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    void AdiosStManIndColumn::getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* dataPtr){
        if(itsStManPtr->getAdiosReadFile()){
            stringstream varName;
            varName << itsColumnName << "/" << itsColumnName << "[" << rowStart << "]";
            for (int i=0; i<itsShape.size(); i++){
                readStart[itsShape.size() - i - 1] = ns.start()(i);
                readCount[itsShape.size() - i - 1] = ns.length()(i);
            }
            ADIOS_SELECTION *sel = adios_selection_boundingbox (itsShape.size(), readStart, readCount);
            adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, varName.str().c_str(), 0, 1, dataPtr);
            adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
        }
        else{
            cout << "AdiosStManColumn Error: AdiosStMan is not working in read mode!" << endl;
        }
    }

    void AdiosStManIndColumn::putArrayMetaV (uint64_t row, const void* data){
        itsStManPtr->adiosWriteOpen();
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[row] , (void*)data);
    }

    void AdiosStManIndColumn::flush(){
    }
}

