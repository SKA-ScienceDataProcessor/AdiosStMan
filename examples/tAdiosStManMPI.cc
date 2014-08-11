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

IPosition data_pos = IPosition(3,120,120,10);
int NrRows = 10;

string filename = "v.casa";

Table *casa_table;

int mpiRank, mpiSize;




void create_table(){

	// define a storage manager
//	AdiosStMan stman;
	AdiosStMan stman(mpiRank, mpiSize);

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
	td.addColumn (ScalarColumnDesc<int>("index"));
	td.addColumn (ArrayColumnDesc<float>("data", data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab(filename, td, Table::New);
	newtab.bindAll(stman);
	casa_table = new Table(newtab, NrRows);

}

void join_table(){

	casa_table = new Table(filename);    
	uInt nrrow = casa_table->nrow();

	ScalarColumn<int> index_col(*casa_table, "index");
	ArrayColumn<float> data_col(*casa_table, "data");

}

void put_data(){

	// define column objects and link them to the table
	ScalarColumn<int> index_col(*casa_table, "index");
	ArrayColumn<float> data_col(*casa_table, "data");

	// define data arrays that actually hold the data
	Array<float> data_arr(data_pos);

	// put some data in
	indgen (data_arr);

	// write data into the column objects
	for (uInt i=0; i<NrRows; i++) {
		index_col.put (i, i);
		data_col.put(i, data_arr);
	}

}

void close_table(){
	delete casa_table;
}

int main (){

	MPI_Init(0,0);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

	
	if(mpiRank == 0){
		cout << "from master rank = " << mpiRank << endl;
		create_table();
		put_data();
		close_table();
	}

//	MPI_Barrier(MPI_COMM_WORLD);

	
	if(mpiRank == 0){
		cout << "from slave rank = " << mpiRank << endl;
		join_table();
	}
	


	MPI_Finalize();

	return 0;
}


