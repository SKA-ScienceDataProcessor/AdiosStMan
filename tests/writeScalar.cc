//    wAdiosStMan.cc: example code for writing a casa table using AdiosStMan
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


#include "../AdiosStMan.h"
#include <casacore/tables/Tables/SetupNewTab.h>
#include <casacore/tables/Tables/ScaColDesc.h>
#include <casacore/casa/namespace.h>

int main(int argc, char **argv){

    if (argc < 2){
        cout << "./wAdiosStMan /path/to/file" << endl;
        return -1;
    }
    string filename = argv[1];

    int NrRows = 4;

    // define a storage manager
//    AdiosStMan stman("MPI", "", 100);
//    AdiosStMan stman("MPI_AGGREGATE", "num_aggregators=32", 100);
    AdiosStMan stman;

    // define a table description and add a scalar column
    TableDesc td("", "1", TableDesc::Scratch);
    td.addColumn (ScalarColumnDesc<Bool>("index_Bool"));
    td.addColumn (ScalarColumnDesc<uChar>("index_uChar"));
    td.addColumn (ScalarColumnDesc<Short>("index_Short"));
    td.addColumn (ScalarColumnDesc<uShort>("index_uShort"));
    td.addColumn (ScalarColumnDesc<Int>("index_Int"));
    td.addColumn (ScalarColumnDesc<uInt>("index_uInt"));
    td.addColumn (ScalarColumnDesc<Float>("index_Float"));
    td.addColumn (ScalarColumnDesc<Double>("index_Double"));
    td.addColumn (ScalarColumnDesc<Complex>("index_Complex"));
    td.addColumn (ScalarColumnDesc<DComplex>("index_DComplex"));

    // create a table instance, bind it to the storage manager
    SetupNewTable newtab(filename, td, Table::New);
    newtab.bindAll(stman);
    Table tab(newtab, NrRows);

    // define column objects and link them to the table
    ScalarColumn<Bool> col_Bool (tab, "index_Bool");
    ScalarColumn<uChar> col_uChar (tab, "index_uChar");
    ScalarColumn<Short> col_Short (tab, "index_Short");
    ScalarColumn<uShort> col_uShort (tab, "index_uShort");
    ScalarColumn<Int> col_Int (tab, "index_Int");
    ScalarColumn<uInt> col_uInt (tab, "index_uInt");
    ScalarColumn<Float> col_Float (tab, "index_Float");
    ScalarColumn<Double> col_Double (tab, "index_Double");
    ScalarColumn<Complex> col_Complex (tab, "index_Complex");
    ScalarColumn<DComplex> col_DComplex (tab, "index_DComplex");

    // write data into the column objects
    for (uInt i=0; i<NrRows; i++) {
        col_Bool.put (i, i);
        col_uChar.put (i, i);
        col_Short.put (i, i);
        col_uShort.put (i, i);
        col_Int.put (i, i);
        col_uInt.put (i, i);
        col_Float.put (i, i);
        col_Double.put (i, i);
        col_Complex.put (i, i);
        col_DComplex.put (i, i);
    }

    return 0;
}


