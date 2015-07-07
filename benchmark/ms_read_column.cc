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



#include <casacore/tables/Tables/TableDesc.h>
#include <casacore/tables/Tables/SetupNewTab.h>
#include <casacore/tables/Tables/ScaColDesc.h>
#include <casacore/tables/Tables/ScalarColumn.h>
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/casa/namespace.h>
#include "tictak.h"



void table_read(string filename){

    Table casa_table(filename);
    ROArrayColumn<Complex> data_col(casa_table, "DATA");
    Array<Complex> data_arr = data_col.getColumn();

    /*
    // this block is for printing
    Vector<Complex> data_vec = data_arr.reform(IPosition(1,data_arr.nelements()));
    for (int i=0; i<32; i++){
        cout << data_vec[i] << "  ";
        if ((i+1) % (data_arr.shape())(0) == 0)	cout << endl;
    }
    */

}


int main(int argc, char **argv){

    for(int i=1; i<argc; i++){
        tictak_add(argv[i],0);
        table_read(argv[i]);
    }

    tictak_add((char*)"End",0);
    tictak_dump(0);

    return 0;
}


