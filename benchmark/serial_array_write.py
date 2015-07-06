#!/usr/bin/python
#    serial_array_write.py: Python script for benchmarking storage managers,
#	 collecting & plotting results
#
#    (c) University of Western Australia
#    International Centre of Radio Astronomy Research
#    M468, 35 Stirling Hwy
#    Crawley, Perth WA 6009
#    Australia
#
#    This library is free software: you can redistribute it and/or
#    modify it under the terms of the GNU General Public License as published
#    by the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this library. If not, see <http://www.gnu.org/licenses/>.
#
#    Any bugs, questions, concerns and/or suggestions please email to
#    jason.wang@icrar.org



import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import commands
import numpy
import os


#  ----------------- testing configuration
#
namesStMan = ['AdiosStMan', 'TiledShapeStMan', 'StandardStMan']
nrRows = range(10, 100, 20)
arrayS = range(100, 1000, 200)
iters  = 1
filepath = '/scratch/tmp'
cleaning_threshould = 90  # in GB / if there is less disk space than this number, all casa files will be deleted upon writing requests


#  ----------------- initialisation
#

nr = len(nrRows)
ns = len(arrayS)
nn = len(namesStMan)

for n in namesStMan:   # define numpy arrays for storage managers for putting in testing results
    exec('{0}_time = numpy.zeros(({1},{2},{3}))'.format(n,iters,nr,ns))
    exec('{0}_MBps = numpy.zeros(({1},{2},{3}))'.format(n,iters,nr,ns))
    exec('{0}_size = numpy.zeros(({1},{2},{3}))'.format(n,iters,nr,ns))



#  ----------------- functions
#
def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False


def print_row():
    Is = -1
    for s in arrayS:   # loop for plotting different array sizes
        Is = Is + 1
        In = -1
        pltptr = []
        plt.figure()
        for n in namesStMan:   # loop for testing different storage managers
            In = In + 1
            ptr, = plt.plot(nrRows, sum(eval(n + '_MBps')) [:,Is] / iters)
            pltptr.append(ptr)
        plt.legend (pltptr, namesStMan, loc = 2)
        plt.grid()
        plt.xlabel('number of rows')
        plt.ylabel('throughput in MB/s')
        plt.figtext(.40, .92, "side length of array = {0}\narray size = {1} MB".format(s, float(s * s * 4 / 1000000) ))
        plt.savefig('row-MBps-{0}.png'.format(s))

def print_arrsize():
    Ir = -1
    for r in nrRows:   # loop for plotting different numbers of rows in a CASA table
        Ir = Ir + 1
        In = -1
        pltptr = []
        plt.figure()
        for n in namesStMan:   # loop for testing different storage managers
            In = In + 1
            ptr, = plt.plot(arrayS, sum(eval(n + '_MBps')) [Ir,:] / iters)
            pltptr.append(ptr)
        plt.legend (pltptr, namesStMan, loc = 2)
        plt.grid()
        plt.xlabel('side length of the square array for each cell')
        plt.ylabel('throughput in MB/s')
        plt.figtext(.40, .92, "number of rows = {0}".format(r))
        plt.savefig('arrsize-MBps-{0}.png'.format(r))


#  ----------------- main flow
#

os.system("rm -rf {0}*.casa".format(filepath))

for i in range(iters):   # loop for iterations
    Ir = -1
    for r in nrRows:   # loop for testing different numbers of rows in a CASA table
        Ir = Ir + 1
        Is = -1
        for s in arrayS:   # loop for testing different array sizes
            Is = Is + 1
            for n in namesStMan:   # loop for testing different storage managers
                disk = os.statvfs(filepath)
                freespace = disk.f_frsize * disk.f_bfree / 1024 / 1024 / 1024
                print "Available disk space is {0} GB. Will clean up all casa files when there is less than {1} GB.".format(freespace, cleaning_threshould)
                if freespace < cleaning_threshould:   # if the free disk space is less than a given number of GB
                    print "Reached the cleaning threshold. All casa files deleted!"
                    os.system("rm -rf {0}*.casa".format(filepath))   # delete any existing casa files / directories
                filename = '{0}_rows{1}_size{2}_iter{3}.casa'.format(n, r, s, i)
                filepathname = filepath + filename
                cmdline = "mpirun --quiet -np 1 ./serial_array_write {0} {1} {2} {3} {4}".format(r, s, s, n, filepathname)   # generate command line
                status, output = commands.getstatusoutput(cmdline)   # run command line and get output
                outputlist = output.split('\n')   # to skip the error lines that ADIOS possibly printed out
                output1 = outputlist[-1]
                print cmdline + ' ---------  time = ' + output1 + ' seconds'
                if len(outputlist) > 1:
                    print output
                if is_number(output1):
                    eval(n+'_time')[i, Ir, Is] = float(output1)
                    eval(n+'_size')[i, Ir, Is] = r * s * s * 4 / 1000000
                    eval(n+'_MBps')[i, Ir, Is] = r * s * s * 4 / float(output1) / 1000000

print_row()
print_arrsize()

os.system("rm -rf {0}*.casa".format(filepath))
