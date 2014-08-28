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

IPosition data_pos = IPosition(2,6,5);

int NrRows = 10;

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

	for (i=mpiRank; i<NrRows; i+=mpiSize) {
		index_col->put (i, i);
		data_col->put (i, data_arr);
	}

	delete index_col;
	delete data_col;
}


int main (){

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


