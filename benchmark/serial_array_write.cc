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
#include <casacore/tables/DataMan/TiledShapeStMan.h>
#include <casacore/tables/DataMan/StandardStMan.h>
#include <casacore/casa/namespace.h>

#include "../AdiosStMan.h"
#include "tictak.h"

// shape of the array column
IPosition *data_pos;

// number of rows
int nrRows;


void writetable(DataManager *stman, Array<float> *data_arr, string filename){

	// define a table description & add a scalar column and an array column
	TableDesc td("", "1", TableDesc::Scratch);
//	td.addColumn (ScalarColumnDesc<int>("index"));
	td.addColumn (ArrayColumnDesc<float>("data", *data_pos, ColumnDesc::Direct));

	// create a table instance, bind it to the storage manager & allocate rows
	SetupNewTable newtab(filename, td, Table::New);
	newtab.bindAll(*stman);
	Table tab(newtab, nrRows);

	// define column objects and link them to the table
//	ScalarColumn<int> index_col (tab, "index");
	ArrayColumn<float> data_col (tab, "data");

	// write data into the column objects
	for (uInt i=0; i<nrRows; i++) {
//		index_col.put (i, i);
		data_col.put(i, *data_arr);
	}
}

void bench(DataManager *stman, Array<float> *data_arr, string filename){

	tictak_add((char*)filename.c_str(),0);
	writetable(stman, data_arr, filename);
	delete stman;
	stman = 0;
	tictak_add((char*)"end",0);
	cout << tictak_total(0) << endl;

}

int main(int argc, char** argv){

	if(argc < 6){
		cout << "./bench (int)nrRows (int)arrayX (int)arrayY (string)nameStMan (string)filename" << endl;
		exit(1);
	}

	nrRows = atoi(argv[1]);
	data_pos = new IPosition(2, atoi(argv[2]), atoi(argv[3]));

	Array<float> data_arr(*data_pos);
	indgen (data_arr);

	string nameStMan = argv[4];
	string filename = argv[5];
	DataManager *stman = 0;

	if(nameStMan == "AdiosStMan")  stman = new AdiosStMan;
	if(nameStMan == "StandardStMan")  stman = new StandardStMan;
	if(nameStMan == "TiledShapeStMan")  stman = new TiledShapeStMan("data", IPosition(2, (*data_pos)[0] / 10, (*data_pos)[1] / 10));

	if(stman)  bench(stman, &data_arr, filename);
	else cout << "invalid nameStMan" << endl;

	if(data_pos) delete data_pos;
	return 0;
}


