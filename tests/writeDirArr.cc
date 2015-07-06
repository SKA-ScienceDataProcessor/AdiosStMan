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
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/tables/DataMan/TiledShapeStMan.h>
#include <casacore/casa/namespace.h>

int main(int argc, char **argv){

    if (argc < 2){
        cout << "./wAdiosStMan /path/to/file" << endl;
        return -1;
    }
    string filename = argv[1];

    // define a storage manager
//    AdiosStMan stman("MPI", "", 100);
//    AdiosStMan stman("MPI_AGGREGATE", "num_aggregators=32", 100);
    AdiosStMan stman;
//    TiledShapeStMan stman("Ti", data_pos);

    IPosition data_pos = IPosition(2,6,5);
    int NrRows = 4;


    Array<Bool> arr_Bool(data_pos);
    Array<uChar> arr_uChar(data_pos);
    Array<Short> arr_Short(data_pos);
    Array<uShort> arr_uShort(data_pos);
    Array<Int> arr_Int(data_pos);
    Array<uInt> arr_uInt(data_pos);
    Array<Float> arr_Float(data_pos);
    Array<Double> arr_Double(data_pos);
    Array<Complex> arr_Complex(data_pos);
    Array<DComplex> arr_DComplex(data_pos);

    // define a table description & add a scalar column and an array column
    TableDesc td("", "1", TableDesc::Scratch);
    td.addColumn (ArrayColumnDesc<Bool>("data_Bool", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<uChar>("data_uChar", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<Short>("data_Short", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<uShort>("data_uShort", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<Int>("data_Int", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<uInt>("data_uInt", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<Float>("data_Float", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<Double>("data_Double", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<Complex>("data_Complex", data_pos, ColumnDesc::Direct));
    td.addColumn (ArrayColumnDesc<DComplex>("data_DComplex", data_pos, ColumnDesc::Direct));

    // create a table instance, bind it to the storage manager & allocate rows
    SetupNewTable newtab(filename, td, Table::New);
    newtab.bindAll(stman);
    Table tab(newtab, NrRows);

    // define column objects and link them to the table
    ArrayColumn<Bool> col_Bool (tab, "data_Bool");
    ArrayColumn<uChar> col_uChar (tab, "data_uChar");
    ArrayColumn<Short> col_Short (tab, "data_Short");
    ArrayColumn<uShort> col_uShort (tab, "data_uShort");
    ArrayColumn<Int> col_Int (tab, "data_Int");
    ArrayColumn<uInt> col_uInt (tab, "data_uInt");
    ArrayColumn<Float> col_Float (tab, "data_Float");
    ArrayColumn<Double> col_Double (tab, "data_Double");
    ArrayColumn<Complex> col_Complex (tab, "data_Complex");
    ArrayColumn<DComplex> col_DComplex (tab, "data_DComplex");

    // write data into the column objects
    for (uInt i=0; i<NrRows; i++) {
        arr_Bool = 1; col_Bool.put(i, arr_Bool);
        arr_uChar = 2; col_uChar.put(i, arr_uChar);
        arr_Short = -3; col_Short.put(i, arr_Short);
        arr_uShort = 4; col_uShort.put(i, arr_uShort);
        indgen(arr_Int, (Int)i*100); col_Int.put(i, arr_Int);
        indgen(arr_uInt, (uInt)i*100); col_uInt.put(i, arr_uInt);
        indgen(arr_Float, (Float)i*100); col_Float.put(i, arr_Float);
        indgen(arr_Double, (Double)i*100); col_Double.put(i, arr_Double);
        indgen(arr_Complex, (Complex)i*100); col_Complex.put(i, arr_Complex);
        arr_DComplex = 5; col_DComplex.put(i, arr_DComplex);
    }

    return 0;
}


