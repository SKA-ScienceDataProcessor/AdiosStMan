//    rAdiosStManSlice.cc: example code for reading a casa table using AdiosStMan
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



// headers for table creation 
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>

// headers for scalar column
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>

// headers for array column
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>

// headers for casa namespaces
#include <casa/namespace.h>

#include "tictak.h"


String filename;

void table_read(){
	
	Table casa_table(filename);    
	uInt nrrow = casa_table.nrow();

	ROArrayColumn<Complex> data_col(casa_table, "DATA");

	IPosition start(2,0,0);
	IPosition end(2,1,768);
	Slicer sli(start, end);

	for (int j=0; j<nrrow; j++){
		Array<Complex> data_arr = data_col.getSlice(j, sli);
//		Vector<Complex> data_vec = data_arr.reform(IPosition(1,data_arr.nelements()));
//		cout << "Row  " << j << endl;
//		for (int i=0; i<16; i++){
//			cout << data_vec[i] << "  ";
//			if ((i+1) % (data_arr.shape())(0) == 0)	cout << endl;
//		}
	}
}


int main (){

	tictak_add((char*)"AdiosStMan",0);
	filename = "/scratch/jason/1067892840_adiosA.ms";
	table_read();

	tictak_add((char*)"TiledStMan",0);
	filename = "/scratch/jason/1067892840_tsm.ms";
	table_read();

	tictak_add((char*)"End",0);

	tictak_dump(0);

	return 0;
}


