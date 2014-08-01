#include <mpi.h>
// headers for table creation 
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>

// headers for storage manager
#include "AdiosStMan.h"

// headers for scalar column
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>

// headers for array column
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>

// headers for casa namespaces
#include <casa/namespace.h>

int main (int argc, char* argv[]){

	// define a storage manager
	AdiosStMan stman;

	IPosition data_pos = IPosition(2,18,4);
	IPosition do_pos = IPosition(3,3,6,2);

	// define a table description & add two columns
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<Int>("index"));
	td.addColumn (ArrayColumnDesc<Complex>("data", data_pos, ColumnDesc::Direct));
	td.addColumn (ArrayColumnDesc<Int>("do", do_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab("v.casa", td, Table::New);
	newtab.bindAll(stman);
	Table tab(newtab, 10);

	// define column objects and link them to the table
	ScalarColumn<int> index_col (tab, "index");
	ArrayColumn<Complex> data_col (tab, "data");
	ArrayColumn<Int> do_col (tab, "do");

	// define data arrays that actually hold the data
	Array<Complex> data_arr(data_pos);
	Array<Int> do_arr(do_pos);



	// put some data in
	indgen (data_arr);
	indgen (do_arr);


	// write data into the column objects
	for (uInt i=0; i<10; i++) {
		index_col.put (i, i);
		data_col.put(i, data_arr);
		do_col.put(i, do_arr);
	}
	return 0;
}


