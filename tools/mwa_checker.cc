//    mwa_checker.cc: check if mwa_converter wrote correctly
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

	Table tsm_table(file_tsm);    
	Table adios_table(file_adios);    

	uInt tsm_rows = tsm_table.nrow();
	uInt adios_rows = adios_table.nrow();

	if (tsm_rows != adios_rows){
		cout << "number of rows does not match!\n" ;
		return -1;
	}

//////////////////////////////////////////////////////////////////////////////////////////////
//  TiledShapeStMan
	
	ROScalarColumn<bool>    FLAG_ROW_col_tsm(tsm_table, "FLAG_ROW");
	ROScalarColumn<int>     ANTENNA1_col_tsm(tsm_table, "ANTENNA1");
	ROScalarColumn<int>     ANTENNA2_col_tsm(tsm_table, "ANTENNA2");
	ROScalarColumn<int>     ARRAY_ID_col_tsm(tsm_table, "ARRAY_ID");
	ROScalarColumn<int>     DATA_DESC_ID_col_tsm(tsm_table, "DATA_DESC_ID");
	ROScalarColumn<int>     FEED1_col_tsm(tsm_table, "FEED1");
	ROScalarColumn<int>     FEED2_col_tsm(tsm_table, "FEED2");
	ROScalarColumn<int>     FIELD_ID_col_tsm(tsm_table, "FIELD_ID");
	ROScalarColumn<int>     PROCESSOR_ID_col_tsm(tsm_table, "PROCESSOR_ID");
	ROScalarColumn<int>     SCAN_NUMBER_col_tsm(tsm_table, "SCAN_NUMBER");
	ROScalarColumn<int>     STATE_ID_col_tsm(tsm_table, "STATE_ID");
	ROScalarColumn<double>  EXPOSURE_col_tsm(tsm_table, "EXPOSURE");
	ROScalarColumn<double>  INTERVAL_col_tsm(tsm_table, "INTERVAL");
	ROScalarColumn<double>  TIME_col_tsm(tsm_table, "TIME");
	ROScalarColumn<double>  TIME_CENTROID_col_tsm(tsm_table, "TIME_CENTROID");

	ROArrayColumn<bool>     FLAG_col_tsm(tsm_table, "FLAG");
	ROArrayColumn<float>    SIGMA_col_tsm(tsm_table, "SIGMA");
	ROArrayColumn<float>    WEIGHT_col_tsm(tsm_table, "WEIGHT");
	ROArrayColumn<float>    WEIGHT_SPECTRUM_col_tsm(tsm_table, "WEIGHT_SPECTRUM");
	ROArrayColumn<Complex>  CORRECTED_DATA_col_tsm(tsm_table, "CORRECTED_DATA");
	ROArrayColumn<Complex>  DATA_col_tsm(tsm_table, "DATA");
	ROArrayColumn<Double>   UVW_col_tsm(tsm_table, "UVW");

//////////////////////////////////////////////////////////////////////////////////////////////
//  AdiosStMan

	ROScalarColumn<bool>    FLAG_ROW_col_adios(adios_table, "FLAG_ROW");
	ROScalarColumn<int>     ANTENNA1_col_adios(adios_table, "ANTENNA1");
	ROScalarColumn<int>     ANTENNA2_col_adios(adios_table, "ANTENNA2");
	ROScalarColumn<int>     ARRAY_ID_col_adios(adios_table, "ARRAY_ID");
	ROScalarColumn<int>     DATA_DESC_ID_col_adios(adios_table, "DATA_DESC_ID");
//	ROScalarColumn<int>     FEED1_col_adios(adios_table, "FEED1");
//	ROScalarColumn<int>     FEED2_col_adios(adios_table, "FEED2");
//	ROScalarColumn<int>     FIELD_ID_col_adios(adios_table, "FIELD_ID");
//	ROScalarColumn<int>     PROCESSOR_ID_col_adios(adios_table, "PROCESSOR_ID");
//	ROScalarColumn<int>     SCAN_NUMBER_col_adios(adios_table, "SCAN_NUMBER");
//	ROScalarColumn<int>     STATE_ID_col_adios(adios_table, "STATE_ID");
//	ROScalarColumn<double>  EXPOSURE_col_adios(adios_table, "EXPOSURE");
//	ROScalarColumn<double>  INTERVAL_col_adios(adios_table, "INTERVAL");
//	ROScalarColumn<double>  TIME_col_adios(adios_table, "TIME");
//	ROScalarColumn<double>  TIME_CENTROID_col_adios(adios_table, "TIME_CENTROID");

//	ROArrayColumn<bool>     FLAG_col_adios(adios_table, "FLAG");
//	ROArrayColumn<float>    SIGMA_col_adios(adios_table, "SIGMA");
//	ROArrayColumn<float>    WEIGHT_col_adios(adios_table, "WEIGHT");
//	ROArrayColumn<float>    WEIGHT_SPECTRUM_col_adios(adios_table, "WEIGHT_SPECTRUM");
//	ROArrayColumn<Complex>  CORRECTED_DATA_col_adios(adios_table, "CORRECTED_DATA");
//	ROArrayColumn<Complex>  DATA_col_adios(adios_table, "DATA");
//	ROArrayColumn<double>   UVW_col_adios(adios_table, "UVW");

	///////////////////////////////////////////
	

	for(int i=0; i<tsm_rows; i++){


	// FLAG_ROW column
		bool FLAG_ROW_adios = FLAG_ROW_col_adios.get(i);
		bool FLAG_ROW_tsm   = FLAG_ROW_col_tsm.get(i);
		if (FLAG_ROW_adios != FLAG_ROW_tsm){
			cout << "row = " << i << ", column = FLAG_ROW" << endl;
			cout << "adios value = " << FLAG_ROW_adios << ", tsm value = " << FLAG_ROW_tsm << endl;
			exit(-1);
		}
	// ANTENNA1 column
		int ANTENNA1_adios = ANTENNA1_col_adios.get(i);
		int ANTENNA1_tsm   = ANTENNA1_col_tsm.get(i);
		if (ANTENNA1_adios != ANTENNA1_tsm){
			cout << "row = " << i << ", column = ANTENNA1" << endl;
			cout << "adios value = " << ANTENNA1_adios << ", tsm value = " << ANTENNA1_tsm << endl;
			exit(-1);
		}
	// ANTENNA2 column
		int ANTENNA2_adios = ANTENNA2_col_adios.get(i);
		int ANTENNA2_tsm   = ANTENNA2_col_tsm.get(i);
		if (ANTENNA2_adios != ANTENNA2_tsm){
			cout << "row = " << i << ", column = ANTENNA2" << endl;
			cout << "adios value = " << ANTENNA2_adios << ", tsm value = " << ANTENNA2_tsm << endl;
			exit(-1);
		}
	// ARRAY_ID column
		int ARRAY_ID_adios = ARRAY_ID_col_adios.get(i);
		int ARRAY_ID_tsm   = ARRAY_ID_col_tsm.get(i);
		if (ARRAY_ID_adios != ARRAY_ID_tsm){
			cout << "row = " << i << ", column = ARRAY_ID" << endl;
			cout << "adios value = " << ARRAY_ID_adios << ", tsm value = " << ARRAY_ID_tsm << endl;
			exit(-1);
		}
	// DATA_DESC_ID column
		int DATA_DESC_ID_adios = DATA_DESC_ID_col_adios.get(i);
		int DATA_DESC_ID_tsm   = DATA_DESC_ID_col_tsm.get(i);
		if (DATA_DESC_ID_adios != DATA_DESC_ID_tsm){
			cout << "row = " << i << ", column = DATA_DESC_ID" << endl;
			cout << "adios value = " << DATA_DESC_ID_adios << ", tsm value = " << DATA_DESC_ID_tsm << endl;
			exit(-1);
		}
//	// FEED1 column
//		int FEED1_adios = FEED1_col_adios.get(i);
//		int FEED1_tsm   = FEED1_col_tsm.get(i);
//		if (FEED1_adios != FEED1_tsm){
//			cout << "row = " << i << ", column = FEED1" << endl;
//			cout << "adios value = " << FEED1_adios << ", tsm value = " << FEED1_tsm << endl;
//			exit(-1);
//		}
//	// FEED2 column
//		int FEED2_adios = FEED2_col_adios.get(i);
//		int FEED2_tsm   = FEED2_col_tsm.get(i);
//		if (FEED2_adios != FEED2_tsm){
//			cout << "row = " << i << ", column = FEED2" << endl;
//			cout << "adios value = " << FEED2_adios << ", tsm value = " << FEED2_tsm << endl;
//			exit(-1);
//		}
//	// FIELD_ID column
//		int FIELD_ID_adios = FIELD_ID_col_adios.get(i);
//		int FIELD_ID_tsm   = FIELD_ID_col_tsm.get(i);
//		if (FIELD_ID_adios != FIELD_ID_tsm){
//			cout << "row = " << i << ", column = FIELD_ID" << endl;
//			cout << "adios value = " << FIELD_ID_adios << ", tsm value = " << FIELD_ID_tsm << endl;
//			exit(-1);
//		}
//	// PROCESSOR_ID column
//	// SCAN_NUMBER column
//	// STATE_ID column
//	// EXPOSURE column
//	// INTERVAL column
//	// TIME column
//	// TIME_CENTROID column


//	// FLAG column
//	// SIGMA column
//	// WEIGHT column
//	// WEIGHT_SPECTRUM column
//		Array<float> WEIGHT_SPECTRUM_tsm = WEIGHT_SPECTRUM_col_tsm.get(i);
//		Vector<float> WEIGHT_SPECTRUM_tsm_rf = WEIGHT_SPECTRUM_tsm.reform(IPosition(1, WEIGHT_SPECTRUM_tsm.nelements()));
//		Array<float> WEIGHT_SPECTRUM_adios = WEIGHT_SPECTRUM_col_adios.get(i);
//		Vector<float> WEIGHT_SPECTRUM_adios_rf = WEIGHT_SPECTRUM_adios.reform(IPosition(1, WEIGHT_SPECTRUM_adios.nelements()));
//		for(int j=0; j<WEIGHT_SPECTRUM_tsm.nelements(); j++){
//			if(WEIGHT_SPECTRUM_tsm_rf[j] != WEIGHT_SPECTRUM_adios_rf[j]){
//				cout << "row = " << i << ", column = WEIGHT_SPECTRUM, element = " << j << endl;
//				cout << WEIGHT_SPECTRUM_tsm_rf[j] << endl;
//				cout << WEIGHT_SPECTRUM_adios_rf[j] << endl;
//				exit(-1);
//			}
//		}
//	// DATA column
//	// CORRECTED_DATA column
//	// UVW column
//		Array<Double> UVW_tsm = UVW_col_tsm.get(i);
//		Vector<Double> UVW_tsm_rf = UVW_tsm.reform(IPosition(1, UVW_tsm.nelements()));
//		Array<Double> UVW_adios = UVW_col_adios.get(i);
//		Vector<Double> UVW_adios_rf = UVW_adios.reform(IPosition(1, UVW_adios.nelements()));
//		for(int j=0; j<UVW_tsm.nelements(); j++){
//			if(UVW_tsm_rf[j] != UVW_adios_rf[j]){
//				cout << "row = " << i << ", column = UVW, element = " << j << endl;
//				cout << UVW_tsm_rf[j] << endl;
//				cout << UVW_adios_rf[j] << endl;
//				exit(-1);
//			}
//		}


		if (i%1000 == 0 && i > 0)
			cout << i << " rows checked, " << (float)i/tsm_rows*100 << "\% finished" << endl;
	}


	return 0;
}


