//    wAdiosStManMPI.cc: example code for writing a casa table with AdiosStMan
//    columns from multiple MPI processes in parallel
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



// ################################################################################
// This code creates separate casa table files for each MPI process. 
// In order to fool the casa table system as if different processes are 
// dealing with independent casa tables so that one process won't lock
// the table and/or prevent others from putting data in, only the master MPI process
// creates casa table files in the intended place, while slave processes 
// create table files with exactly the same contents in /tmp, which are supposed
// to be cleaned up once the job is finished.
//
// However, the AdiosStMan objects associated with these casa tables are actually all
// writing data into a single ADIOS container, which is in the same directory where
// the master MPI process writes casa table files. Therefore, after job is finished,
// these table files together with ADIOS files will contain all information that is
// necessary to reproduce the casa table. 



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

#include "../tools/tictak.h"

int NrRows = 10;
IPosition data_pos;
string filename = "v.casa";

int mpiRank, mpiSize;
Array<Float> data_arr;


void write_table(){

	AdiosStMan stman(AdiosStMan::ARRAY);

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
//	td.addColumn (ScalarColumnDesc<uInt>("index"));
	td.addColumn (ArrayColumnDesc<Float>("data", data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab(filename, td, Table::New);
	newtab.bindAll(stman);
	Table casa_table(newtab, NrRows);

	// define column objects and link them to the table
//	ScalarColumn<uInt> index_col(casa_table, "index");
	ArrayColumn<Float> data_col(casa_table, "data");

	// each mpi rank writes a subset of the data
	for (uInt i=mpiRank; i<NrRows; i+=mpiSize) {
//		if (i < NrRows/mpiSize*mpiSize )
//			MPI_Barrier(MPI_COMM_WORLD);
//		index_col.put (i, i);
		data_col.put (i, data_arr);
//		cout << i << " rows finished from Rank " << mpiRank << endl;
	}

}


int main (int argc, char **argv){

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

	if(NrRows<mpiSize){
		exit(-1);
	}
	// generate filenames for slave processes
	// these files are not used later on, so just put them 
	// into /tmp and clean them up when job is finished
	if(mpiRank>0){
		stringstream filename_s;
		filename_s << "/tmp/v" << mpiRank << ".casa";
		filename = filename_s.str();
	}

	// put some data into the data array
	indgen (data_arr);

	MPI_Barrier(MPI_COMM_WORLD);
	tictak_add((char*)filename.c_str(),0);
	write_table();
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


