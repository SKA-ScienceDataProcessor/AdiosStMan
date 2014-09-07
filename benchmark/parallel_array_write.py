#!/usr/bin/python
#    parallel_array_write.py: Python script for benchmarking storage managers,
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
import matplotlib.patches as mpatches
import commands
import numpy
import os

row_max = 6000
row_min = 1000
array_size = 16
node_max = 22


def add_point(linedic):


	#######
	plt.figure(1)
	color = (linedic['NrRows']-row_min)/(row_max-row_min)
	plt.scatter(linedic['Nodes'], linedic['Mps'], c=(color, 1 - color , 0), s=10, edgecolors='none') 


	#######
	plt.figure(2)
	color = linedic['Nodes']/node_max
	if color > 1:
		color = 1
	print linedic['Nodes'], linedic['Mps'], color, linedic['NrRows']
	plt.scatter(linedic['NrRows'], linedic['Mps'], c=(color, 1 - color , 0), s=10, edgecolors='none') 


def save_fig():

	#######
	plt.figure(1)
	for i in range(row_min, row_max+1, 1000):
		colour = (float)(i-row_min)/(row_max-row_min)
		plt.scatter([],[], c=(colour, 1 - colour , 0), s=20, edgecolors='none', label=str("{0} Rows".format(i)))
	plt.legend(loc = 4)
	plt.grid()
	plt.xlim([0, 40])
	plt.ylim([0, 5000])
	plt.xlabel('Number of Nodes (12 processes per node)')
	plt.ylabel('Total throughput in MB/s (cache saturated)')
	plt.figtext(.10, .94, "Parallel AdiosStMan (v0.3.6) testing, iVEC Fornax, Lustre Stripe Size = 8, \nSingle column with direct arrays, Array size = {0}MB, Table size = {0}MB * Rows".format(array_size))
	plt.savefig('fig1.png', dpi = 200)


	#######
	plt.figure(2)
	for i in range(1,node_max, 5):
		color = (float)(i)/node_max
		print color
		plt.scatter([],[], c=(color, 1 - color , 0), s=20, edgecolors='none', label=str("{0} Nodes".format(i)))
	plt.legend()
	plt.grid()
	plt.xlim([900, 6100])
	plt.ylim([0, 5000])
	plt.xlabel('Number of Rows')
	plt.ylabel('Total throughput in MB/s (cache saturated)')
	plt.figtext(.10, .94, "Parallel AdiosStMan (v0.3.6) testing, iVEC Fornax, Lustre Stripe Size = 8, \nSingle column with direct arrays, Array size = {0}MB, Table size = {0}MB * Rows".format(array_size))
	plt.savefig('fig2.png', dpi = 200)

#######  main

logfile = open('log','r')

for line in logfile:

	linedic = {}
	linelist = line.strip().split(',')
	for i in range(len(linelist)/2):
		linedic[linelist[i*2]] = float(linelist[i*2+1])
	add_point(linedic)

save_fig()
		

	

	



