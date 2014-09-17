//    AdiosStManColumnV.cc: StManColumn class for AdiosStMan, 
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

#include "AdiosStManColumnV.h"
#include <casa/Arrays/Array.h>
#include <casa/Utilities/DataType.h>

namespace casa{

	AdiosStManColumnV::AdiosStManColumnV (AdiosStMan* aParent, int aDataType, uInt aColNr)
		:AdiosStManColumn (aParent, aDataType, aColNr){
	}


	void AdiosStManColumnV::initAdiosWrite(uInt aNrRows){

		int mpiRank;
		MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);  

		for(int j=0; j<aNrRows; j++){

			if(itsAdiosWriteIDs == 0){
				itsAdiosWriteIDs = (int64_t*) malloc(sizeof(int64_t) * aNrRows);
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

	Bool AdiosStManColumnV::canAccessSlice(Bool &reask) const{
		reask = false;
		return true;
	}

	void AdiosStManColumnV::putArrayGeneralV (uInt rownr, const void* dataPtr){
//		if(isZero(dataPtr) && rownr > 0) return;
		itsStManPtr->adiosWriteOpen();
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}

	void AdiosStManColumnV::putGeneralV (uInt rownr, const void* dataPtr){
//		if(isZero(dataPtr) && rownr > 0) return;
		itsStManPtr->adiosWriteOpen();
		adios_write_byid(itsStManPtr->getAdiosFile(), itsAdiosWriteIDs[rownr] , (void*)dataPtr);
	}



}

