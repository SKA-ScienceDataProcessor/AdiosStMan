AdiosStMan
============================================

This project is to implement a CASA storage manager using ADIOS (Adaptive IO System) as the underlying storage library. Currently, the existing CASA storage managers are all based on CASA built-in file formats, which can only be operated in serial. In the meanwhile, modern general purpose IO libraries, for instance, HDF5 and ADIOS, have started evolving towards parallel IO. This project aims at implementing an Adios storage manager, design a parallel IO mechanism for casacore, and then test it to see how this parallel IO mechanism compares with the existing serial ones when dealing with SKA scale data. 
This version uses a method of opening a CTDS column in ADIOS file for multiple times to write data, which reduces the buffer size from the entire table to an arbitrary number. This removes the limitation on the table size that AdiosStMan is able to handle.


============================================
============================================


