
//	  in the table's main AipsIO file, in the same order as the casa table system
//    does when opening an existing table. The purpose of this code is to help
//    verify if a storage manager that is under development is writing correct 
//    metadata to a table. 
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

#include <string.h>
#include <tables/Tables/Table.h>
#include <tables/Tables/TableRecord.h>
#include <casa/IO/AipsIO.h>

using namespace casa;


int main(int argc, char** argv){

	if (argc < 2){
		cout << "./dumpTable tabname" << endl;
		exit(1);
	}

	// open the table
	string tabname = argv[1];
	AipsIO ios (Table::fileName(tabname), ByteIO::Old);


	// called in PlainTable.cc
	cout << "Called in PlainTable.cc  -----------" << endl;
	uInt version = ios.getstart ("Table");

	String tp;
	uInt format;
	uInt nrrow;

	ios >> nrrow;
	ios >> format;
	ios >> tp;

	cout << "version = " << version << endl;
	cout << "number of rows = " << nrrow << endl;
	cout << "format = " << format << endl;
	cout << "table type = " << tp << endl;
	cout << "------------------------------------" << endl << endl;


	// called in TableDesc.cc
	cout << "Called in TableDesc.cc  ------------" << endl;

	uInt tvers = ios.getstart ("TableDesc");
	String name_p, vers_p, comm_p;
	TableRecord* privKey_p = new TableRecord;

	ios >> name_p;
	ios >> vers_p;
	ios >> comm_p;
	if (tvers != 1) {
		ios >> *privKey_p;
	}

	cout << "name_p = " << name_p << endl;
	cout << "vers_p = " << vers_p << endl;
	cout << "comm_p = " << comm_p << endl;
	cout << "privKey_p = " << *privKey_p << endl;
	cout << "------------------------------------" << endl << endl;


	
	// called in ColumnDesc.cc
	cout << "Called in ColumnDesc.cc  -----------" << endl;

	ios >> version;
	ios >> tp;
	cout << "version = " << version << endl;
	cout << "column type = " << tp << endl;
	cout << "------------------------------------" << endl << endl;


	// called in BaseColDesc.cc
	cout << "Called in BaseColDesc.cc  -----------" << endl;

	String         colName_p;            //# column name
	String         comment_p;            //# comment
	String         dataManType_p;        //# default data manager type
	String         dataManGroup_p;       //# data manager group
	DataType       dtype_p;              //# datatype
	Int dtype;

	ios >> version;
	cout << "version = " << version << endl;
	ios >> colName_p;
	cout << "colName_p = " << colName_p << endl;
	ios >> comment_p;
/*	
	ios >> dataManType_p;
	ios >> dataManGroup_p;

	ios >> dtype;

	*/
	cout << "------------------------------------" << endl << endl;

	

	return 0;

}
