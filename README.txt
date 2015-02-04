AdiosStMan
============================================

This project is to implement a CASA storage manager using ADIOS (Adaptive IO System) as the underlying storage library. Currently, the existing CASA storage managers are all based on CASA built-in file formats, which can only be operated in serial. In the meanwhile, modern general purpose IO libraries, for instance, HDF5 and ADIOS, have started evolving towards parallel IO. This project aims at implementing an Adios storage manager, design a parallel IO mechanism for casacore, and then test it to see how this parallel IO mechanism compares with the existing serial ones when dealing with SKA scale data. 


============================================
============================================

Version History:
v0.4.15 - Adjusted parameters for testing on Fornax
---------------------
v0.4.14 - PBS scripts slightly twisted for Fornax 2015 configuration
---------------------
v0.4.13 - Added Slurm job scripts to benchmark ms_converter
---------------------
v0.4.12 - Minors changes to the python script for plotting
---------------------
v0.4.11 - Slight changes to enable large scale testing on Cray machines
---------------------
v0.4.10 - Added user manual
---------------------
v0.4.9 - Added makefile configuration for Cray machines
---------------------
v0.4.8 - Added parallel support to tools/ms_converter
---------------------
v0.4.7 - Added functions to write each cell in individual ADIOS VARs
---------------------
v0.4.6 - Some minor changes for massive MPI testing
---------------------
v0.4.5 - Mesurement set conversion all verified
---------------------
v0.4.4 - Fixed a bug for reversing a dimension string
---------------------
v0.4.3 - Added mwa_checker
---------------------
v0.4.2 - Separated canAccessArrayColumn for reading and writing
---------------------
v0.4.1 - Added functions to check if data to be written is all zero
---------------------
v0.4 - Restructured AdiosStManColumn in a way that it derives child classes to access ADIOS files differently
=====================
=====================
v0.3.12 - Added getColumnSlice
---------------------
v0.3.11 - Fixed a bug for reading slices
---------------------
v0.3.10 - Added getColumn functions for array columns
---------------------
v0.3.9 - Added getSlice functions for array columns
---------------------
v0.3.8 - Added tools for converting MWA measurement sets using AdiosStMan
---------------------
v0.3.7 - Added python script for analysing parallel testing results
---------------------
v0.3.6 - Replaced the parallel benchmark code based on the new example code
---------------------
v0.3.5 - Added another example code for MPI parallel write
---------------------
v0.3.4 - Added PBS script for extensive testing of parallel table write
---------------------
v0.3.3 - Added benchmarking code for parallel write
---------------------
v0.3.2 - Minor changes to makefiles
---------------------
v0.3.1 - Fixed a problem of writing arrays in parallel
---------------------
v0.3 - AdiosStMan is now able to write a single table from multiple MPI processes in parallel
=====================
=====================
v0.2.3 - Added addRow function
---------------------
v0.2.2 - Modified filename of dynamic library for automatic registration on case sensitive systems
---------------------
v0.2.1 - Slightly changed makefiles to work with a variety of Linux systems
---------------------
v0.2 - Read functions added. AdiosStMan now supports writing and reading a CASA table with scalar and / or direct array columns
=====================
=====================
v0.1.11 - Tuned the IO profiling tool to work with MPI and the python benchmarking script on various machines
---------------------
v0.1.10 - Separated benchmark and example codes. Added tools for dumping table metadata and IO profiling
---------------------
v0.1.9 - The python benchmark script now automatically cleans up all CASA files when disk is full
---------------------
v0.1.8 - Twisted for HPC machines at ICRAR & iVEC, ready for extensive testing
---------------------
v0.1.7 - Changed an ADIOS dimension string to avoid a strlen_sse() seg fault for some libc versions
---------------------
v0.1.6 - Minor changes for the Python benckmark running on Ubuntu Linux
---------------------
v0.1.5 - Added an automated benchmark routine in Python 
---------------------
v0.1.4 - Fixed the bug that causes a failure when writing an array larger than 80MB
---------------------
v0.1.3 - Added a simple bench mark code to compare storage managers. Put all testing/benchmarking code into ./test
---------------------
v0.1.2 - Added README.txt with version history. 
---------------------
v0.1.1 - Trivial changes to v0.1. Pushed to SDP github.
---------------------
v0.1 - The first release. This version only supports writing a CASA table with scalar columns and/or direct array columns in numeric data types to ADIOS files. Reading operations, indirect arrays and the string data type are not supported in this version. 
============================================
============================================


