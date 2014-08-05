// headers for table creation 
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>

// headers for storage manager
#include "../AdiosStMan.h"
#include <tables/Tables/StandardStMan.h>

// headers for scalar column
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>

// headers for array column
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>

// headers for casa namespaces
#include <casa/namespace.h>

#include "tictak.h"

// shape of the array column
IPosition data_pos(2,2000,2000);

// number of rows
int nrRows = 50;

void bench(DataManager *stman, Array<float> *data_arr, string filename){

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<int>("index"));
	td.addColumn (ArrayColumnDesc<float>("data", data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab(filename, td, Table::New);
	newtab.bindAll(*stman);
	Table tab(newtab, nrRows);

	// define column objects and link them to the table
	ScalarColumn<int> index_col (tab, "index");
	ArrayColumn<float> data_col (tab, "data");

	// write data into the column objects
	for (uInt i=0; i<nrRows; i++) {
		index_col.put (i, i);
		data_col.put(i, *data_arr);
	}
}

int main (){

	Array<float> data_arr(data_pos);
	indgen (data_arr);
	
	AdiosStMan *stman1 = new AdiosStMan;
	tictak_add((char*)"adios",0);
	bench(stman1, &data_arr, "adios.casa");
	delete stman1;
	tictak_add((char*)"end",0);
	tictak_dump(0);

	StandardStMan *stman2 = new StandardStMan;
	tictak_add((char*)"stand",1);
	bench(stman2, &data_arr, "stand.casa");
	delete stman2;
	tictak_add((char*)"end",1);
	tictak_dump(1);
	

	return 0;
}


