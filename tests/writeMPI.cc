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

#include "../AdiosStMan.h"
#include <casacore/tables/Tables/TableDesc.h>
#include <casacore/tables/Tables/SetupNewTab.h>
#include <casacore/tables/Tables/ScaColDesc.h>
#include <casacore/tables/Tables/ScalarColumn.h>
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/casa/namespace.h>

int main(int argc, char **argv){

    if (argc < 2){
        cout << "./wAdiosStMan /path/to/file" << endl;
        return 0;
    }

    string filename = argv[1];

    AdiosStMan stman("POSIX", "", 10, 20);

    int mpiRank, mpiSize;
//    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    
    int NrRows = 200;
    int rows_per_process = NrRows/mpiSize;

//    AdiosStMan stman("POSIX", "", 10, rows_per_process);

    // generate filenames for slave processes
    // these files are not used later on, so just put them
    // into /tmp and clean them up when job is finished
    if(mpiRank>0){
        stringstream filename_s;
        filename_s << "/tmp/v" << mpiRank << ".casa";
        filename = filename_s.str();
    }

    // define a dimension object for the array column
    IPosition data_pos = IPosition(2,50,60);
    // define data arrays that actually hold the data
    Array<Float> data_arr(data_pos);
    // put some data into the data array
    indgen (data_arr);

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

    // each mpi rank writes a subset of the data
    for (uInt i=0; i<rows_per_process; i++) {
        index_col.put (mpiRank * rows_per_process + i, i);
        data_col.put (mpiRank * rows_per_process + i, data_arr);
    }
  

 //   MPI_Finalize();
  
    return 0;
}


