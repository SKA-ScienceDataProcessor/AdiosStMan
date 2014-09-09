//    mwa_converter.cc: convert MWA measurementsets from TiledStMan to AdiosStMan 
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

	// UVW column
	ROArrayColumn<Double> UVW_col_adios(adios_table, "UVW");
	// FLAG column
//	ROArrayColumn<bool> FLAG_col_adios(adios_table, "FLAG");
	// WEIGHT column
	ROArrayColumn<float> WEIGHT_col_adios(adios_table, "WEIGHT");
	// SIGMA column
	ROArrayColumn<float> SIGMA_col_adios(adios_table, "SIGMA");
	// ANTENNA1 column
	ROScalarColumn<int> ANTENNA1_col_adios(adios_table, "ANTENNA1");
	// ANTENNA2 column
	ROScalarColumn<int> ANTENNA2_col_adios(adios_table, "ANTENNA2");
	// ARRAY_ID column
	ROScalarColumn<int> ARRAY_ID_col_adios(adios_table, "ARRAY_ID");
	// DATA_DESC_ID column
	ROScalarColumn<int> DATA_DESC_ID_col_adios(adios_table, "DATA_DESC_ID");
	// EXPOSURE column
	ROScalarColumn<double> EXPOSURE_col_adios(adios_table, "EXPOSURE");
	// FEED1 column
	ROScalarColumn<int> FEED1_col_adios(adios_table, "FEED1");
	// FEED2 column
	ROScalarColumn<int> FEED2_col_adios(adios_table, "FEED2");
	// FIELD_ID column
	ROScalarColumn<int> FIELD_ID_col_adios(adios_table, "FIELD_ID");
	// FLAG_ROW column
	ROScalarColumn<bool> FLAG_ROW_col_adios(adios_table, "FLAG_ROW");
	// INTERVAL column
	ROScalarColumn<double> INTERVAL_col_adios(adios_table, "INTERVAL");
	// PROCESSOR_ID column
	ROScalarColumn<int> PROCESSOR_ID_col_adios(adios_table, "PROCESSOR_ID");
	// SCAN_NUMBER column
	ROScalarColumn<int> SCAN_NUMBER_col_adios(adios_table, "SCAN_NUMBER");
	// STATE_ID column
	ROScalarColumn<int> STATE_ID_col_adios(adios_table, "STATE_ID");
	// TIME column
	ROScalarColumn<double> TIME_col_adios(adios_table, "TIME");
	// TIME_CENTROID column
	ROScalarColumn<double> TIME_CENTROID_col_adios(adios_table, "TIME_CENTROID");
	// DATA column
	ROArrayColumn<Complex> DATA_col_adios(adios_table, "DATA");
	// WEIGHT_SPECTRUM column
	ROArrayColumn<float> WEIGHT_SPECTRUM_col_adios(adios_table, "WEIGHT_SPECTRUM");
	// CORRECTED_DATA column
	ROArrayColumn<Complex> CORRECTED_DATA_col_adios(adios_table, "CORRECTED_DATA");

	// UVW column
	ROArrayColumn<Double> UVW_col_tsm(tsm_table, "UVW");
	// FLAG column
//	ROArrayColumn<bool> FLAG_col_tsm(tsm_table, "FLAG");
	// WEIGHT column
	ROArrayColumn<float> WEIGHT_col_tsm(tsm_table, "WEIGHT");
	// SIGMA column
	ROArrayColumn<float> SIGMA_col_tsm(tsm_table, "SIGMA");
	// ANTENNA1 column
	ROScalarColumn<int> ANTENNA1_col_tsm(tsm_table, "ANTENNA1");
	// ANTENNA2 column
	ROScalarColumn<int> ANTENNA2_col_tsm(tsm_table, "ANTENNA2");
	// ARRAY_ID column
	ROScalarColumn<int> ARRAY_ID_col_tsm(tsm_table, "ARRAY_ID");
	// DATA_DESC_ID column
	ROScalarColumn<int> DATA_DESC_ID_col_tsm(tsm_table, "DATA_DESC_ID");
	// EXPOSURE column
	ROScalarColumn<double> EXPOSURE_col_tsm(tsm_table, "EXPOSURE");
	// FEED1 column
	ROScalarColumn<int> FEED1_col_tsm(tsm_table, "FEED1");
	// FEED2 column
	ROScalarColumn<int> FEED2_col_tsm(tsm_table, "FEED2");
	// FIELD_ID column
	ROScalarColumn<int> FIELD_ID_col_tsm(tsm_table, "FIELD_ID");
	// FLAG_ROW column
	ROScalarColumn<bool> FLAG_ROW_col_tsm(tsm_table, "FLAG_ROW");
	// INTERVAL column
	ROScalarColumn<double> INTERVAL_col_tsm(tsm_table, "INTERVAL");
	// PROCESSOR_ID column
	ROScalarColumn<int> PROCESSOR_ID_col_tsm(tsm_table, "PROCESSOR_ID");
	// SCAN_NUMBER column
	ROScalarColumn<int> SCAN_NUMBER_col_tsm(tsm_table, "SCAN_NUMBER");
	// STATE_ID column
	ROScalarColumn<int> STATE_ID_col_tsm(tsm_table, "STATE_ID");
	// TIME column
	ROScalarColumn<double> TIME_col_tsm(tsm_table, "TIME");
	// TIME_CENTROID column
	ROScalarColumn<double> TIME_CENTROID_col_tsm(tsm_table, "TIME_CENTROID");
	// DATA column
	ROArrayColumn<Complex> DATA_col_tsm(tsm_table, "DATA");
	// WEIGHT_SPECTRUM column
	ROArrayColumn<float> WEIGHT_SPECTRUM_col_tsm(tsm_table, "WEIGHT_SPECTRUM");
	// CORRECTED_DATA column
	ROArrayColumn<Complex> CORRECTED_DATA_col_tsm(tsm_table, "CORRECTED_DATA");
	

	for(int i=0; i<tsm_rows; i++){

		// UVW column
		Array<Double> UVW_tsm = UVW_col_tsm.get(i);
		Vector<Double> UVW_tsm_rf = UVW_tsm.reform(IPosition(1, UVW_tsm.nelements()));

		Array<Double> UVW_adios = UVW_col_adios.get(i);
		Vector<Double> UVW_adios_rf = UVW_adios.reform(IPosition(1, UVW_adios.nelements()));
		for(int j=0; j<UVW_tsm.nelements(); j++){
			Double t = UVW_tsm_rf[j];
			Double a = UVW_adios_rf[j];
			if(UVW_tsm_rf[j] != UVW_adios_rf[j]){
				cout << "row = " << i << ", column = UVW, element = " << j << endl;
				cout << UVW_tsm_rf[j] << endl;
				cout << UVW_adios_rf[j] << endl;
				exit(-1);
			}

		}
		// FLAG column
//		ROArrayColumn<bool> FLAG_col_tsm(tsm_table, "FLAG");
//		// WEIGHT column
//		ROArrayColumn<float> WEIGHT_col_tsm(tsm_table, "WEIGHT");
//		// SIGMA column
//		ROArrayColumn<float> SIGMA_col_tsm(tsm_table, "SIGMA");
//		// ANTENNA1 column
//		ROScalarColumn<int> ANTENNA1_col_tsm(tsm_table, "ANTENNA1");
//		// ANTENNA2 column
//		ROScalarColumn<int> ANTENNA2_col_tsm(tsm_table, "ANTENNA2");
//		// ARRAY_ID column
//		ROScalarColumn<int> ARRAY_ID_col_tsm(tsm_table, "ARRAY_ID");
//		// DATA_DESC_ID column
//		ROScalarColumn<int> DATA_DESC_ID_col_tsm(tsm_table, "DATA_DESC_ID");
//		// EXPOSURE column
//		ROScalarColumn<double> EXPOSURE_col_tsm(tsm_table, "EXPOSURE");
//		// FEED1 column
//		ROScalarColumn<int> FEED1_col_tsm(tsm_table, "FEED1");
//		// FEED2 column
//		ROScalarColumn<int> FEED2_col_tsm(tsm_table, "FEED2");
//		// FIELD_ID column
//		ROScalarColumn<int> FIELD_ID_col_tsm(tsm_table, "FIELD_ID");
//		// FLAG_ROW column
//		ROScalarColumn<bool> FLAG_ROW_col_tsm(tsm_table, "FLAG_ROW");
//		// INTERVAL column
//		ROScalarColumn<double> INTERVAL_col_tsm(tsm_table, "INTERVAL");
//		// PROCESSOR_ID column
//		ROScalarColumn<int> PROCESSOR_ID_col_tsm(tsm_table, "PROCESSOR_ID");
//		// SCAN_NUMBER column
//		ROScalarColumn<int> SCAN_NUMBER_col_tsm(tsm_table, "SCAN_NUMBER");
//		// STATE_ID column
//		ROScalarColumn<int> STATE_ID_col_tsm(tsm_table, "STATE_ID");
//		// TIME column
//		ROScalarColumn<double> TIME_col_tsm(tsm_table, "TIME");
//		// TIME_CENTROID column
//		ROScalarColumn<double> TIME_CENTROID_col_tsm(tsm_table, "TIME_CENTROID");
//		// DATA column
//		ROArrayColumn<Complex> DATA_col_tsm(tsm_table, "DATA");
//		// WEIGHT_SPECTRUM column
//		ROArrayColumn<float> WEIGHT_SPECTRUM_col_tsm(tsm_table, "WEIGHT_SPECTRUM");
//		// CORRECTED_DATA column
//		ROArrayColumn<Complex> CORRECTED_DATA_col_tsm(tsm_table, "CORRECTED_DATA");


		cout << "Row " << i << " is OK" << endl;
	}


	return 0;
}


