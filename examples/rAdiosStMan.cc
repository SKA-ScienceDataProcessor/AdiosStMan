// headers for table creation 
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>

// headers for scalar column
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>

// headers for array column
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>

// headers for casa namespaces
#include <casa/namespace.h>

Table *casa_table;
String filename = "/tmp/v.casa";

int main (){

	casa_table = new Table(filename);    
	uInt nrrow = casa_table->nrow();

	ROScalarColumn<uInt> index_col(*casa_table, "index");
	ROArrayColumn<float> data_col(*casa_table, "data");

	Array<uInt> index_arr = index_col.getColumn();
	Array<float> data_arr = data_col.getColumn();

	Vector<float> data_vec = data_arr.reform(IPosition(1,data_arr.nelements()));

	for (int i=0; i<data_arr.nelements(); i++){
		cout << data_vec[i] << "  ";
		if ((i+1) % (data_arr.shape())(0) == 0)	cout << endl;
	}

	return 0;
}


