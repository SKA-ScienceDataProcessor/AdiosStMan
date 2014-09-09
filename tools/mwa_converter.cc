#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>
#include <tables/Tables/ScaColDesc.h>
#include <tables/Tables/ScalarColumn.h>
#include <casacore/tables/Tables/ArrColDesc.h>
#include <casacore/tables/Tables/ArrayColumn.h>
#include "../AdiosStMan.h"
#include <casa/namespace.h>


int main (int argc, char **argv){

	string file_tsm="/scratch/jason/1067892840_tsm.ms";
	string file_adios="/scratch/jason/1067892840_adios.ms";

	if (argc == 3){
		file_tsm = argv[1];
		file_adios = argv[2];
	}

	cout << "file_tsm = " << file_tsm << endl;
	cout << "file_adios = " << file_adios << endl;

	// ####### read init
	Table read_table(file_tsm);    
	uInt NrRows = read_table.nrow();


	// ####### write init
	TableDesc td("", "1", TableDesc::Scratch);
	

	// ####### column init for read & write
	// UVW column
	ROArrayColumn<Double> UVW_col(read_table, "UVW");
	IPosition UVW_pos = UVW_col.shape(0);
	td.addColumn (ArrayColumnDesc<Double>("UVW", UVW_pos, ColumnDesc::Direct));
	// FLAG column
//	ROArrayColumn<bool> FLAG_col(read_table, "FLAG");
//	IPosition FLAG_pos = FLAG_col.shape(0);
//	td.addColumn (ArrayColumnDesc<bool>("FLAG", FLAG_pos, ColumnDesc::Direct));
	// WEIGHT column
	ROArrayColumn<float> WEIGHT_col(read_table, "WEIGHT");
	IPosition WEIGHT_pos = WEIGHT_col.shape(0);
	td.addColumn (ArrayColumnDesc<float>("WEIGHT", WEIGHT_pos, ColumnDesc::Direct));
	// SIGMA column
	ROArrayColumn<float> SIGMA_col(read_table, "SIGMA");
	IPosition SIGMA_pos = SIGMA_col.shape(0);
	td.addColumn (ArrayColumnDesc<float>("SIGMA", SIGMA_pos, ColumnDesc::Direct));
	// ANTENNA1 column
	ROScalarColumn<int> ANTENNA1_col(read_table, "ANTENNA1");
	td.addColumn (ScalarColumnDesc<int>("ANTENNA1"));
	// ANTENNA2 column
	ROScalarColumn<int> ANTENNA2_col(read_table, "ANTENNA2");
	td.addColumn (ScalarColumnDesc<int>("ANTENNA2"));
	// ARRAY_ID column
	ROScalarColumn<int> ARRAY_ID_col(read_table, "ARRAY_ID");
	td.addColumn (ScalarColumnDesc<int>("ARRAY_ID"));
	// DATA_DESC_ID column
	ROScalarColumn<int> DATA_DESC_ID_col(read_table, "DATA_DESC_ID");
	td.addColumn (ScalarColumnDesc<int>("DATA_DESC_ID"));
	// EXPOSURE column
	ROScalarColumn<double> EXPOSURE_col(read_table, "EXPOSURE");
	td.addColumn (ScalarColumnDesc<double>("EXPOSURE"));
	// FEED1 column
	ROScalarColumn<int> FEED1_col(read_table, "FEED1");
	td.addColumn (ScalarColumnDesc<int>("FEED1"));
	// FEED2 column
	ROScalarColumn<int> FEED2_col(read_table, "FEED2");
	td.addColumn (ScalarColumnDesc<int>("FEED2"));
	// FIELD_ID column
	ROScalarColumn<int> FIELD_ID_col(read_table, "FIELD_ID");
	td.addColumn (ScalarColumnDesc<int>("FIELD_ID"));
	// FLAG_ROW column
	ROScalarColumn<bool> FLAG_ROW_col(read_table, "FLAG_ROW");
	td.addColumn (ScalarColumnDesc<bool>("FLAG_ROW"));
	// INTERVAL column
	ROScalarColumn<double> INTERVAL_col(read_table, "INTERVAL");
	td.addColumn (ScalarColumnDesc<double>("INTERVAL"));
	// PROCESSOR_ID column
	ROScalarColumn<int> PROCESSOR_ID_col(read_table, "PROCESSOR_ID");
	td.addColumn (ScalarColumnDesc<int>("PROCESSOR_ID"));
	// SCAN_NUMBER column
	ROScalarColumn<int> SCAN_NUMBER_col(read_table, "SCAN_NUMBER");
	td.addColumn (ScalarColumnDesc<int>("SCAN_NUMBER"));
	// STATE_ID column
	ROScalarColumn<int> STATE_ID_col(read_table, "STATE_ID");
	td.addColumn (ScalarColumnDesc<int>("STATE_ID"));
	// TIME column
	ROScalarColumn<double> TIME_col(read_table, "TIME");
	td.addColumn (ScalarColumnDesc<double>("TIME"));
	// TIME_CENTROID column
	ROScalarColumn<double> TIME_CENTROID_col(read_table, "TIME_CENTROID");
	td.addColumn (ScalarColumnDesc<double>("TIME_CENTROID"));
	// DATA column
	ROArrayColumn<Complex> DATA_col(read_table, "DATA");
	IPosition DATA_pos = DATA_col.shape(0);
	td.addColumn (ArrayColumnDesc<Complex>("DATA", DATA_pos, ColumnDesc::Direct));
	// WEIGHT_SPECTRUM column
	ROArrayColumn<float> WEIGHT_SPECTRUM_col(read_table, "WEIGHT_SPECTRUM");
	IPosition WEIGHT_SPECTRUM_pos = WEIGHT_SPECTRUM_col.shape(0);
	td.addColumn (ArrayColumnDesc<float>("WEIGHT_SPECTRUM", WEIGHT_SPECTRUM_pos, ColumnDesc::Direct));
	// CORRECTED_DATA column
	ROArrayColumn<Complex> CORRECTED_DATA_col(read_table, "CORRECTED_DATA");
	IPosition CORRECTED_DATA_pos = CORRECTED_DATA_col.shape(0);
	td.addColumn (ArrayColumnDesc<Complex>("CORRECTED_DATA", CORRECTED_DATA_pos, ColumnDesc::Direct));
	
	
	// ####### column init for read & write
	SetupNewTable newtab(file_adios, td, Table::New);
	AdiosStMan stman;
	newtab.bindAll(stman);
	Table write_table(newtab, NrRows);


	// ####### write columns 
	// UVW column
	ArrayColumn<double> UVW_col_new (write_table, "UVW");
	UVW_col_new.putColumn(UVW_col.getColumn());
	cout << "UVW column completed" << endl;
	// FLAG column
//	ArrayColumn<bool> FLAG_col_new (write_table, "FLAG");
//	FLAG_col_new.putColumn(FLAG_col.getColumn());
//	cout << "FLAG column completed" << endl;
	// FLAG_CATEGORY column
	ArrayColumn<float> WEIGHT_col_new (write_table, "WEIGHT");
	WEIGHT_col_new.putColumn(WEIGHT_col.getColumn());
	cout << "WEIGHT column completed" << endl;
	// SIGMA column
	ArrayColumn<float> SIGMA_col_new (write_table, "SIGMA");
	SIGMA_col_new.putColumn(SIGMA_col.getColumn());
	cout << "SIGMA column completed" << endl;
	// ANTENNA1 column
	ScalarColumn<int> ANTENNA1_col_new (write_table, "ANTENNA1");
	ANTENNA1_col_new.putColumn(ANTENNA1_col.getColumn());
	cout << "ANTENNA1 column completed" << endl;
	// ANTENNA2 column
	ScalarColumn<int> ANTENNA2_col_new (write_table, "ANTENNA2");
	ANTENNA2_col_new.putColumn(ANTENNA2_col.getColumn());
	cout << "ANTENNA2 column completed" << endl;
	// ARRAY_ID column
	ScalarColumn<int> ARRAY_ID_col_new (write_table, "ARRAY_ID");
	ARRAY_ID_col_new.putColumn(ARRAY_ID_col.getColumn());
	cout << "ARRAY_ID column completed" << endl;
	// DATA_DESC_ID column
	ScalarColumn<int> DATA_DESC_ID_col_new (write_table, "DATA_DESC_ID");
	DATA_DESC_ID_col_new.putColumn(DATA_DESC_ID_col.getColumn());
	cout << "DATA_DESC_ID column completed" << endl;
	// EXPOSURE column
	ScalarColumn<double> EXPOSURE_col_new (write_table, "EXPOSURE");
	EXPOSURE_col_new.putColumn(EXPOSURE_col.getColumn());
	cout << "EXPOSURE column completed" << endl;
	// FEED1 column
	ScalarColumn<int> FEED1_col_new (write_table, "FEED1");
	FEED1_col_new.putColumn(FEED1_col.getColumn());
	cout << "FEED1 column completed" << endl;
	// FEED2 column
	ScalarColumn<int> FEED2_col_new (write_table, "FEED2");
	FEED2_col_new.putColumn(FEED2_col.getColumn());
	cout << "FEED2 column completed" << endl;
	// FIELD_ID column
	ScalarColumn<int> FIELD_ID_col_new (write_table, "FIELD_ID");
	FIELD_ID_col_new.putColumn(FIELD_ID_col.getColumn());
	cout << "FIELD_ID column completed" << endl;
	// FLAG_ROW column
	ScalarColumn<bool> FLAG_ROW_col_new (write_table, "FLAG_ROW");
	FLAG_ROW_col_new.putColumn(FLAG_ROW_col.getColumn());
	cout << "FLAG_ROW column completed" << endl;
	// INTERVAL column
	ScalarColumn<double> INTERVAL_col_new (write_table, "INTERVAL");
	INTERVAL_col_new.putColumn(INTERVAL_col.getColumn());
	cout << "INTERVAL column completed" << endl;
	// PROCESSOR_ID column
	ScalarColumn<int> PROCESSOR_ID_col_new (write_table, "PROCESSOR_ID");
	PROCESSOR_ID_col_new.putColumn(PROCESSOR_ID_col.getColumn());
	cout << "PROCESSOR_ID column completed" << endl;
	// SCAN_NUMBER column
	ScalarColumn<int> SCAN_NUMBER_col_new (write_table, "SCAN_NUMBER");
	SCAN_NUMBER_col_new.putColumn(SCAN_NUMBER_col.getColumn());
	cout << "SCAN_NUMBER column completed" << endl;
	// STATE_ID column
	ScalarColumn<int> STATE_ID_col_new (write_table, "STATE_ID");
	STATE_ID_col_new.putColumn(STATE_ID_col.getColumn());
	cout << "STATE_ID column completed" << endl;
	// TIME column
	ScalarColumn<double> TIME_col_new (write_table, "TIME");
	TIME_col_new.putColumn(TIME_col.getColumn());
	cout << "TIME column completed" << endl;
	// TIME_CENTROID column
	ScalarColumn<double> TIME_CENTROID_col_new (write_table, "TIME_CENTROID");
	TIME_CENTROID_col_new.putColumn(TIME_CENTROID_col.getColumn());
	cout << "TIME_CENTROID column completed" << endl;
	// DATA column
	ArrayColumn<Complex> DATA_col_new (write_table, "DATA");
	DATA_col_new.putColumn(DATA_col.getColumn());
	cout << "DATA column completed" << endl;
	// WEIGHT_SPECTRUM column
	ArrayColumn<float> WEIGHT_SPECTRUM_col_new (write_table, "WEIGHT_SPECTRUM");
	WEIGHT_SPECTRUM_col_new.putColumn(WEIGHT_SPECTRUM_col.getColumn());
	cout << "WEIGHT_SPECTRUM column completed" << endl;
	// CORRECTED_DATA column
	ArrayColumn<Complex> CORRECTED_DATA_col_new (write_table, "CORRECTED_DATA");
	CORRECTED_DATA_col_new.putColumn(CORRECTED_DATA_col.getColumn());
	cout << "CORRECTED_DATA column completed" << endl;


	return 0;
}


