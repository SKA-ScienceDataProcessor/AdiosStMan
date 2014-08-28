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

#include "tictak.h"


int NrRows;

string filename;

int mpiRank, mpiSize;

IPosition data_pos;
Array<Float> data_arr;



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


int main (int argc, char** argv){

	MPI_Init(0,0);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

	if(argc < 5){
		cout << "./parallel_array_write (int)nrRows (int)arrayX (int)arrayY (string)filename" << endl;
		exit(1);
	}

	NrRows = atoi(argv[1]);
	filename = argv[4];

	data_pos = IPosition(2, atoi(argv[2]), atoi(argv[3]));
	data_arr = Array<Float>(data_pos);

	indgen (data_arr);

	MPI_Barrier(MPI_COMM_WORLD);
	tictak_add((char*)filename.c_str(),0);

	if(mpiRank == 0)
		write_table_master();
	else
		write_table_slave();

	MPI_Barrier(MPI_COMM_WORLD);
	tictak_add((char*)"end",0);

	if(mpiRank == 0){

		float Seconds = tictak_total(0);
		uint64_t CellSize = atoi(argv[2])*atoi(argv[3])*sizeof(float);
		uint64_t TableSize = CellSize * NrRows;
		int Mps = TableSize / Seconds / 1000000;

		cout << "Mps," << Mps;
		cout << ",Seconds," << Seconds;
		cout << ",TableSize," << TableSize;
		cout << ",NrRows," << NrRows;
		cout << ",CellSize," << CellSize;
		cout << ",MpiSize," << mpiSize;
		cout << ",Nodes," << mpiSize / 12;
		cout << ",Xlength," << atoi(argv[2]); 
		cout << ",Ylength," << atoi(argv[3]);
		cout << endl;
	}

	MPI_Finalize();

	return 0;
}


