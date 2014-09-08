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

String filename = "/scratch/tmp/v.casa";


int main (){

	Slicer sli(IPosition(2,0,0), IPosition(2,6,5));

	Table casa_table(filename);    

	ROScalarColumn<uInt> index_col(casa_table, "index");
	ROArrayColumn<float> data_col(casa_table, "data");

	Array<uInt> index_arr = index_col.getColumn();
	Array<float> data_arr = data_col.getColumn(sli);

	Vector<float> data_vec = data_arr.reform(IPosition(1,data_arr.nelements()));

	for (int i=0; i<data_arr.nelements(); i++){
		cout << data_vec[i] << "  ";
		if ((i+1) % (data_arr.shape())(0) == 0)	cout << endl;
	}

	return 0;
}


