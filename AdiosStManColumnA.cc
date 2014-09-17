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

#include "AdiosStManColumnA.h"
#include <casa/Arrays/Array.h>
#include <casa/Utilities/DataType.h>

namespace casa{

	AdiosStManColumnA::AdiosStManColumnA (AdiosStMan* aParent, int aDataType, uInt aColNr)
		:AdiosStManColumn (aParent, aDataType, aColNr){
	}


	void AdiosStManColumnA::initAdiosWrite(uInt aNrRows){

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
				itsAdiosWriteIDs[itsNrIDs] = adios_define_var(itsStManPtr->getAdiosGroup(), itsColumnName.c_str(), "", itsAdiosDataType, dimensions.c_str(), global_dimensions.c_str(), local_offsets.c_str());
			}
			itsNrIDs++;
		}
	}

	Bool AdiosStManColumnA::canAccessArrayColumn(Bool &reask) const{
		reask = false;
		// only can access array column when reading
		if(itsStManPtr->getMode() == 'r') 
			return true;
		return false;
	}

	Bool AdiosStManColumnA::canAccessSlice(Bool &reask) const{
		reask = false;
		return true;
	}

	Bool AdiosStManColumnA::canAccessColumnSlice(Bool &reask) const{
		reask = false;
		return true;
	}

	void AdiosStManColumnA::putArrayGeneralV (uInt rownr, const void* dataPtr){
//		if(isZero(dataPtr) && rownr > 0) return;
		itsStManPtr->adiosWriteOpen();
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumnA::putGeneralV (uInt rownr, const void* dataPtr){
//		if(isZero(dataPtr) && rownr > 0) return;
		itsStManPtr->adiosWriteOpen();
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}


}

