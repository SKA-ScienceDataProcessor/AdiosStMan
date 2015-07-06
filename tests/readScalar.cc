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

#include <casacore/tables/Tables/ScalarColumn.h>
#include <casacore/casa/namespace.h>

int main(int argc, char **argv){
    if (argc < 2){
        cout << "./rAdiosStMan /path/to/file" << endl;
        return -1;
    }
    string filename = argv[1];
    Table casa_table(filename);

    ROScalarColumn<Bool> col_Bool(casa_table, "index_Bool");
    Vector<Bool> vec_Bool = col_Bool.getColumn();
    cout << "index_Bool column: " << endl;
    for (int i=0; i<vec_Bool.nelements(); i++){
        cout << vec_Bool[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<uChar> col_uChar(casa_table, "index_uChar");
    Vector<uChar> vec_uChar = col_uChar.getColumn();
    cout << "index_uChar column: " << endl;
    for (int i=0; i<vec_uChar.nelements(); i++){
        cout << (uInt)vec_uChar[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<Short> col_Short(casa_table, "index_Short");
    Vector<Short> vec_Short = col_Short.getColumn();
    cout << "index_Short column: " << endl;
    for (int i=0; i<vec_Short.nelements(); i++){
        cout << vec_Short[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<uShort> col_uShort(casa_table, "index_uShort");
    Vector<uShort> vec_uShort = col_uShort.getColumn();
    cout << "index_uShort column: " << endl;
    for (int i=0; i<vec_uShort.nelements(); i++){
        cout << vec_uShort[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<Int> col_Int(casa_table, "index_Int");
    Vector<Int> vec_Int = col_Int.getColumn();
    cout << "index_Int column: " << endl;
    for (int i=0; i<vec_Int.nelements(); i++){
        cout << vec_Int[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<uInt> col_uInt(casa_table, "index_uInt");
    Vector<uInt> vec_uInt = col_uInt.getColumn();
    cout << "index_uInt column: " << endl;
    for (int i=0; i<vec_uInt.nelements(); i++){
        cout << vec_uInt[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<Float> col_Float(casa_table, "index_Float");
    Vector<Float> vec_Float = col_Float.getColumn();
    cout << "index_Float column: " << endl;
    for (int i=0; i<vec_Float.nelements(); i++){
        cout << vec_Float[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<Double> col_Double(casa_table, "index_Double");
    Vector<Double> vec_Double = col_Double.getColumn();
    cout << "index_Double column: " << endl;
    for (int i=0; i<vec_Double.nelements(); i++){
        cout << vec_Double[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<Complex> col_Complex(casa_table, "index_Complex");
    Vector<Complex> vec_Complex = col_Complex.getColumn();
    cout << "index_Complex column: " << endl;
    for (int i=0; i<vec_Complex.nelements(); i++){
        cout << vec_Complex[i] << "  ";
    }
    cout << endl << endl;

    ROScalarColumn<DComplex> col_DComplex(casa_table, "index_DComplex");
    Vector<DComplex> vec_DComplex = col_DComplex.getColumn();
    cout << "index_DComplex column: " << endl;
    for (int i=0; i<vec_DComplex.nelements(); i++){
        cout << vec_DComplex[i] << "  ";
    }
    cout << endl << endl;
    return 0;
}


