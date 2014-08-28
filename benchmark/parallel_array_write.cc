//    parallel_array_write.cc: Benchmark code for comparing storage managers.
//    This is supposed to be used together with parallel_array_write.py, 
//    which is a python code controlling the benchmark flow.
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

// headers for storage manager
#include "../AdiosStMan.h"
#include "../AdiosStManColumn.h"

// headers for scalar column
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>

// headers for array column
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>

// headers for casa namespaces
#include <casa/namespace.h>

// shape of the array column
IPosition data_pos;

// number of rows
int NrRows;

string filename = "v.casa";

int mpiRank, mpiSize;

Array<Float> data_arr(data_pos);




void write_table_master(){

	AdiosStMan stman;

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<uInt>("index"));
	td.addColumn (ArrayColumnDesc<Float>("data", data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab(filename, td, Table::New);
	newtab.bindAll(stman);
	Table casa_table(newtab, NrRows);

	// define column objects and link them to the table
	ScalarColumn<uInt> index_col(casa_table, "index");
	ArrayColumn<Float> data_col(casa_table, "data");

	// write data into the column objects
	for (uInt i=mpiRank; i<NrRows; i+=mpiSize) {
		index_col.put (i, i);
		data_col.put (i, data_arr);
	}

}

void write_table_slave(){

	AdiosStMan stman;

	uInt i;

	AdiosStManColumn *index_col = stman.makeScalarColumnSlave("index", whatType(&i));
	AdiosStManColumn *data_col = stman.makeScalarColumnSlave("data", whatType(&data_arr));

	data_col->setShapeColumn(data_pos);

	stman.create(NrRows);

	const Array<Float> *data_arr_con = &data_arr;

	for (i=mpiRank; i<NrRows; i+=mpiSize) {
		index_col->put (i, i);
		data_col->put (i, data_arr_con);
	}

	delete index_col;
	delete data_col;
}


int main (int argc, char **argv){

	if(argc < 5){
		cout << "./parallel_array_write (int)nrRows (int)arrayX (int)arrayY (string)filename" << endl;
		exit(1);
	}

	MPI_Init(0,0);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);


	// put some data in
	indgen (data_arr);

	if(mpiRank == 0)
		write_table_master();
	else
		write_table_slave();

	MPI_Finalize();

	return 0;
}


