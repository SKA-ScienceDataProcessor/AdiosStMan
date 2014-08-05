AdiosStMan
============================================

This project is to implement a CASA storage manager using ADIOS (Adaptive IO System) as the underlying storage library. Currently, the existing CASA storage managers are all based on CASA built-in file formats, which can only be operated in serial. In the meanwhile, modern general purpose IO libraries, for instance, HDF5 and ADIOS, have started evolving towards parallel IO. This project aims at implementing an Adios storage manager, design a parallel IO mechanism for casacore, and then test it to see how this parallel IO mechanism compares with the existing serial ones when dealing with SKA scale data. 


============================================

Version History:
v0.1.4 - Fixed the bug that causes a failure when writing an array larger than 80MB
---------------------
v0.1.3 - Added a simple bench mark code to compare storage managers. Put all testing/benchmarking code into ./test
---------------------
v0.1.2 - Added README.txt with version history. 
---------------------
v0.1.1 - Trivial changes to v0.1. Pushed to SDP github.
---------------------
v0.1 - The first release. This version only supports writing a CASA table with scalar columns and/or direct array columns in numeric data types to ADIOS files. Reading operations, indirect arrays and the string data type are not supported in this version. 


