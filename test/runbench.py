#!/usr/bin/python
#    runBench.py: This file calls bench (tBench.cc) to benchmark
#    storage managers.
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




import matplotlib.pyplot as plt
import commands
import numpy
import os


#  ----------------- testing configuration
#
namesStMan = ['AdiosStMan', 'TiledShapeStMan', 'StandardStMan']
nrRows = range(10, 100, 30)
arrayS = range(100, 600, 400)
iters  = 1 
filepath = '/tmp/'


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
		plt.savefig('row-MBps-{0}.png'.format(int(s)))

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
		plt.savefig('arrsize-MBps-{0}.png'.format(int(r)))


#  ----------------- main flow
#
for i in range(iters):   # loop for iterations
	Ir = -1 
	for r in nrRows:   # loop for testing different numbers of rows in a CASA table
		Ir = Ir + 1
		Is = -1
		for s in arrayS:   # loop for testing different array sizes 
			Is = Is + 1
			for n in namesStMan:   # loop for testing different storage managers
				os.system("rm -rf *.casa")   # delete any existing casa files / directories
				filename = filepath + '{0}_{1}rows_{2}size.casa'.format(n, r, s)
				cmdline = "./bench {0} {1} {2} {3} {4}".format(r, s, s, n, filename)   # generate command line
				status, output = commands.getstatusoutput(cmdline)   # run command line and get output
				print cmdline + ' ---------  time = ' + output + ' seconds'
				output = output.split('\n')[-1]   # to skip the error lines that ADIOS possibly printed out
				if is_number(output):
					eval(n+'_time')[i, Ir, Is] = float(output)
					eval(n+'_size')[i, Ir, Is] = r * s * s * 4 / 1000000
					eval(n+'_MBps')[i, Ir, Is] = r * s * s * 4 / float(output) / 1000000

print_row()
print_arrsize()

os.system("rm -rf *.casa")
