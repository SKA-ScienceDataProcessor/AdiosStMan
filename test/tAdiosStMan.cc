// headers for table creation 
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>

// headers for storage manager
#include "../AdiosStMan.h"

// headers for scalar column
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>

// headers for array column
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>

// headers for casa namespaces
#include <casa/namespace.h>


int main (){

	// define a storage manager
	AdiosStMan stman;

	// define a dimension object for the array column
	IPosition data_pos = IPosition(2,4,4);

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<int>("index"));
	td.addColumn (ArrayColumnDesc<float>("data", data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab("v.casa", td, Table::New);
	newtab.bindAll(stman);
	Table tab(newtab, 10);

	// define column objects and link them to the table
	ScalarColumn<int> index_col (tab, "index");
	ArrayColumn<float> data_col (tab, "data");

	// define data arrays that actually hold the data
	Array<float> data_arr(data_pos);

	// put some data in
	indgen (data_arr);

	// write data into the column objects
	for (uInt i=0; i<10; i++) {
		index_col.put (i, i);
		data_col.put(i, data_arr);
	}

	return 0;
}


