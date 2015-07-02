//    AdiosStManColumnA.cc: StManColumn class for AdiosStMan,
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


#include "AdiosStManColumnA.h"

namespace casa{

    AdiosStManColumnA::AdiosStManColumnA (AdiosStMan* aParent, int aDataType, uInt aColNr)
        :AdiosStManColumn (aParent, aDataType, aColNr){
        }

    AdiosStManColumnA::~AdiosStManColumnA (){
        if (itsAdiosWriteIDs)
            delete [] itsAdiosWriteIDs;
    }

    Bool AdiosStManColumnA::canAccessArrayColumn(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    Bool AdiosStManColumnA::canAccessSlice(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    Bool AdiosStManColumnA::canAccessColumnSlice(Bool &reask) const{
        reask = false;
        if(itsStManPtr->getMode() == 'r')
            return true;
        return false;
    }

    void AdiosStManColumnA::initAdiosWrite(uInt aNrRows){
        for(uInt j=0; j<aNrRows; j++){
            // if not allocated
            if(itsAdiosWriteIDs == 0){
                itsAdiosWriteIDs = new int64_t[aNrRows];
            }
            stringstream NrRows, RowID;
            NrRows << aNrRows;
            RowID << j;
            if (itsShape.nelements() == 0){
                itsAdiosWriteIDs[j] = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, "1", NrRows.str().c_str(), RowID.str().c_str() ); ////
            }
            else{
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
    }

    // get a row from a scalar column
    void AdiosStManColumnA::getScalarMetaV (uint64_t row, void* data){
        itsStManPtr->logdbg("AdiosStManColumnA::getScalarMetaV","");
        if(itsStManPtr->getAdiosReadFile()){
            uint64_t rowid = row;
            ADIOS_SELECTION *sel = adios_selection_points (1, 1, &rowid);
            adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, data);
            adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
        }
        else{
            cout << "AdiosStManColumn Error: AdiosStMan is working in write mode!" << endl;
        }
    }

    // get a slice of a row (all rows if aRowNr < 0) from an array column
    void AdiosStManColumnA::getArrayMetaV (uint64_t rowStart, uint64_t nrRows, const Slicer& ns, void* dataPtr){
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
            adios_schedule_read (itsStManPtr->getAdiosReadFile(), sel, itsColumnName.c_str(), 0, 1, dataPtr);
            adios_perform_reads (itsStManPtr->getAdiosReadFile(), 1);
        }
        else{
            cout << "AdiosStManColumn Error: AdiosStMan is not working in read mode!" << endl;
        }
    }

    void AdiosStManColumnA::putMetaV (uint64_t row, const void* data){
        itsStManPtr->adiosWriteOpen();
        adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[row] , (void*)data);
    }

    void AdiosStManColumnA::flush(){

    }
}

