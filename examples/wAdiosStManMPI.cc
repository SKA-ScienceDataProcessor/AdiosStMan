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

IPosition data_pos = IPosition(3,120,120,10);

int NrRows = 10;

string filename = "v.casa";

int mpiRank, mpiSize;



void write_table_master(){

	AdiosStMan stman;

	ScalarColumn<uInt> *index_col;

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<uInt>("index"));
//	td.addColumn (ArrayColumnDesc<float>("data", data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab(filename, td, Table::New);
	newtab.bindAll(stman);
	Table casa_table(newtab, NrRows);

	// define column objects and link them to the table
	index_col = new ScalarColumn<uInt>(casa_table, "index");
//	ArrayColumn<float> data_col(casa_table, "data");


	// define data arrays that actually hold the data
	Array<float> data_arr(data_pos);

	// put some data in
	indgen (data_arr);

	// write data into the column objects
	if(mpiRank == 0){
		for (uInt i=mpiRank; i<NrRows; i+=mpiSize) {
			index_col->put (i, i);
//			data_col.put(i, data_arr);
		}
	}

	delete index_col;

}

void write_table_slave(){

	AdiosStMan stman;

	DataManagerColumn *index_col;

	uInt *a;
//	index_col_slave = new AdiosStManColumn(&stman, whatType(a), 0);
	index_col = stman.makeScalarColumn("index", whatType(a), "");

	stman.create(NrRows);

	for (uInt i=mpiRank; i<NrRows; i+=mpiSize*2) {
		index_col->put (i, &i);
//		data_col.put(i, data_arr);
	}

	delete index_col;
}

int main (){

	MPI_Init(0,0);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

	if(mpiRank == 0)
		write_table_master();
	else
		write_table_slave();

	MPI_Finalize();

	return 0;
}


