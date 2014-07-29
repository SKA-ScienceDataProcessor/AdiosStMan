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

	// define a table description & add two columns
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<uInt>("index"));
	td.addColumn (ArrayColumnDesc<Complex>("data",IPosition(2,128,64),ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab("tmp.data", td, Table::New);
	newtab.bindAll(stman);
	Table tab(newtab, 10);

	// define column objects and link them to the table
	ScalarColumn<uInt> index (tab, "index");
//	ArrayColumn<Complex> data (tab, "data");

	// define data arrays that actually hold the data
//	Array<Complex> data_origin(IPosition(2,128,64));

	// put some data in
//	indgen (data_origin);

	// write data into the column objects
	for (uInt i=0; i<10; i++) {
		index.put (i, i);
//		data.put(i, data_origin);
	}

	return 0;
}


