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

Table *casa_table;
String filename = "v.casa";

int main (){

	casa_table = new Table(filename);    
	uInt nrrow = casa_table->nrow();

	ROScalarColumn<uInt> index_col(*casa_table, "index");
	ROArrayColumn<float> data_col(*casa_table, "data");

	Array<uInt> index_arr = index_col.getColumn();
	Array<float> data_arr = data_col.getColumn();

	uInt *index_data = index_arr.data();
	float *data_data = data_arr.data();

	for (int i=0; i<1000; i++){
		cout << data_data[i] << endl;
	}

	return 0;
}


