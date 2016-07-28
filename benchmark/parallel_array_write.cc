//    (c) University of Western Australia
//    International Centre of Radio Astronomy Research
//    M468, 35 Stirling Hwy
//    Crawley, Perth WA 6009
//    Australia
//
//    Shanghai Astronomical Observatory, Chinese Academy of Sciences
//    80 Nandan Road, Shanghai 200030, China
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
//    lbq@shao.ac.cn, jason.wang@icrar.org



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



#include <casacore/tables/Tables/SetupNewTab.h>
#include <casacore/tables/Tables/ScaColDesc.h>
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/casa/namespace.h>
#include "../AdiosStMan.h"
#include "tictak.h"


int NrRows;
IPosition data_pos;
string filename;

int mpiRank, mpiSize;
Array<Float> data_arr;

int writeBufRows;

int rows_per_process;

void write_table(){
     
     rows_per_process = NrRows/mpiRank;

//    AdiosStMan stman("MPI_AGGREGATE", "num_aggregators=24, num_ost=24", 30000, 2000);
     AdiosStMan stman("POSIX", "", writeBufRows, rows_per_process);

    // define a table description & add a scalar column and an array column
    TableDesc td("", "1", TableDesc::Scratch);
    td.addColumn (ArrayColumnDesc<Float>("data", data_pos, ColumnDesc::Direct));

    // create a table instance, bind it to the storage manager & allocate rows
    SetupNewTable newtab(filename, td, Table::New);
    newtab.bindAll(stman);
    Table casa_table(newtab, NrRows);

    // define column objects and link them to the table
    ArrayColumn<Float> data_col(casa_table, "data");

    // each mpi rank writes a subset of the data
    for (uInt i=0; i<rows_per_process; i++) {
        data_col.put (mpiRank * rows_per_process + i, data_arr);
    }
}


int main (int argc, char **argv){

    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

    if(argc < 6){
        cout << "./parallel_array_write (int)nrRows (int)arrayX (int)arrayY (string)filename (int)writeBufNrRows" << endl;
        exit(1);
    }

    NrRows = atoi(argv[1]);
    filename = argv[4];
    writeBufRows = atoi(argv[5]);

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
        filename_s << "/scratch/pawsey0129/AdiosStMan/tmp1/rank" << mpiRank << ".casa";
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

        float Seconds = tictak_total(0,0);
        uint64_t CellSize = atoi(argv[2])*atoi(argv[3])*sizeof(float);
        uint64_t TableSize = CellSize * NrRows;
        int Mps = TableSize / Seconds / 1000000;

        cout << "MB/s," << Mps;
        cout << ",Seconds," << Seconds;
        cout << ",TableSize(Byte)," << TableSize;
        cout << ",NrRows," << NrRows;
        cout << ",CellSize(Byte)," << CellSize;
        cout << ",MpiSize," << mpiSize;
        cout << ",Xlength," << atoi(argv[2]);
        cout << ",Ylength," << atoi(argv[3]);
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}


