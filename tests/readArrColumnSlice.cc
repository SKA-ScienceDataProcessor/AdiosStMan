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

#include <casacore/tables/Tables/ArrayColumn.h>
#include <casacore/casa/namespace.h>

int main(int argc, char **argv){
    if (argc < 2){
        cout << "./rAdiosStMan /path/to/file" << endl;
        return -1;
    }
    string filename = argv[1];
    Slicer sli(IPosition(2,1,2), IPosition(2,2,3));
    Table casa_table(filename);

    ROArrayColumn<Bool> col_Bool(casa_table, "data_Bool");
    Array<Bool> arr_Bool = col_Bool.getColumn(sli);
    Vector<Bool> vec_Bool = arr_Bool.reform(IPosition(1,arr_Bool.nelements()));
    cout << endl << "Column: data_Bool, Shape: " << arr_Bool.shape() << endl;
    for (int i=0; i<arr_Bool.nelements(); i++){
        cout << vec_Bool[i] << "  ";
        if ((i+1) % (arr_Bool.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<uChar> col_uChar(casa_table, "data_uChar");
    Array<uChar> arr_uChar = col_uChar.getColumn(sli);
    Vector<uChar> vec_uChar = arr_uChar.reform(IPosition(1,arr_uChar.nelements()));
    cout << endl << "Column: data_uChar, Shape: " << arr_uChar.shape() << endl;
    for (int i=0; i<arr_uChar.nelements(); i++){
        cout << (uInt)vec_uChar[i] << "  ";
        if ((i+1) % (arr_uChar.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<Short> col_Short(casa_table, "data_Short");
    Array<Short> arr_Short = col_Short.getColumn(sli);
    Vector<Short> vec_Short = arr_Short.reform(IPosition(1,arr_Short.nelements()));
    cout << endl << "Column: data_Short, Shape: " << arr_Short.shape() << endl;
    for (int i=0; i<arr_Short.nelements(); i++){
        cout << vec_Short[i] << "  ";
        if ((i+1) % (arr_Short.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<uShort> col_uShort(casa_table, "data_uShort");
    Array<uShort> arr_uShort = col_uShort.getColumn(sli);
    Vector<uShort> vec_uShort = arr_uShort.reform(IPosition(1,arr_uShort.nelements()));
    cout << endl << "Column: data_uShort, Shape: " << arr_uShort.shape() << endl;
    for (int i=0; i<arr_uShort.nelements(); i++){
        cout << vec_uShort[i] << "  ";
        if ((i+1) % (arr_uShort.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<Int> col_Int(casa_table, "data_Int");
    Array<Int> arr_Int = col_Int.getColumn(sli);
    Vector<Int> vec_Int = arr_Int.reform(IPosition(1,arr_Int.nelements()));
    cout << endl << "Column: data_Int, Shape: " << arr_Int.shape() << endl;
    for (int i=0; i<arr_Int.nelements(); i++){
        cout << vec_Int[i] << "  ";
        if ((i+1) % (arr_Int.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<uInt> col_uInt(casa_table, "data_uInt");
    Array<uInt> arr_uInt = col_uInt.getColumn(sli);
    Vector<uInt> vec_uInt = arr_uInt.reform(IPosition(1,arr_uInt.nelements()));
    cout << endl << "Column: data_uInt, Shape: " << arr_uInt.shape() << endl;
    for (int i=0; i<arr_uInt.nelements(); i++){
        cout << vec_uInt[i] << "  ";
        if ((i+1) % (arr_uInt.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<Float> col_Float(casa_table, "data_Float");
    Array<Float> arr_Float = col_Float.getColumn(sli);
    Vector<Float> vec_Float = arr_Float.reform(IPosition(1,arr_Float.nelements()));
    cout << endl << "Column: data_Float, Shape: " << arr_Float.shape() << endl;
    for (int i=0; i<arr_Float.nelements(); i++){
        cout << vec_Float[i] << "  ";
        if ((i+1) % (arr_Float.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<Double> col_Double(casa_table, "data_Double");
    Array<Double> arr_Double = col_Double.getColumn(sli);
    Vector<Double> vec_Double = arr_Double.reform(IPosition(1,arr_Double.nelements()));
    cout << endl << "Column: data_Double, Shape: " << arr_Double.shape() << endl;
    for (int i=0; i<arr_Double.nelements(); i++){
        cout << vec_Double[i] << "  ";
        if ((i+1) % (arr_Double.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<Complex> col_Complex(casa_table, "data_Complex");
    Array<Complex> arr_Complex = col_Complex.getColumn(sli);
    Vector<Complex> vec_Complex = arr_Complex.reform(IPosition(1,arr_Complex.nelements()));
    cout << endl << "Column: data_Complex, Shape: " << arr_Complex.shape() << endl;
    for (int i=0; i<arr_Complex.nelements(); i++){
        cout << vec_Complex[i] << "  ";
        if ((i+1) % (arr_Complex.shape())(0) == 0)
            cout << endl;
    }

    ROArrayColumn<DComplex> col_DComplex(casa_table, "data_DComplex");
    Array<DComplex> arr_DComplex = col_DComplex.getColumn(sli);
    Vector<DComplex> vec_DComplex = arr_DComplex.reform(IPosition(1,arr_DComplex.nelements()));
    cout << endl << "Column: data_DComplex, Shape: " << arr_DComplex.shape() << endl;
    for (int i=0; i<arr_DComplex.nelements(); i++){
        cout << vec_DComplex[i] << "  ";
        if ((i+1) % (arr_DComplex.shape())(0) == 0)
            cout << endl;
    }

    return 0;
}
