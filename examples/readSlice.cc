//    rAdiosStManSlice.cc: example code for reading a casa table using AdiosStMan
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


#include "../AdiosStManGlobal.h"

#ifdef CASACORE_VERSION_1
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>
#include <tables/Tables/ArrColDesc.h>
#include <tables/Tables/ArrayColumn.h>
#include <casa/namespace.h>
#endif

#ifdef CASACORE_VERSION_2
#include <casacore/tables/Tables/TableDesc.h>
#include <casacore/tables/Tables/SetupNewTab.h>
#include <casacore/tables/Tables/ScaColDesc.h>
#include <casacore/tables/Tables/ScalarColumn.h>
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/casa/namespace.h>
#endif


int main(int argc, char **argv){

    if (argc < 2){
        cout << "./rAdiosStMan /path/to/file" << endl;
        return -1;
    }
    string filename = argv[1];

    Slicer sli(IPosition(2,1,2), IPosition(2,2,3));

    Table casa_table(filename);

    ROArrayColumn<float> data_col(casa_table, "data");

    Array<float> data_arr = data_col.getColumn(sli);

    Vector<float> data_vec = data_arr.reform(IPosition(1,data_arr.nelements()));

    for (int i=0; i<data_arr.nelements(); i++){
        cout << data_vec[i] << "  ";
        if ((i+1) % (data_arr.shape())(0) == 0)	cout << endl;
    }

    return 0;
}


