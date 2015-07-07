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

ppn = 24
array_size = 16

node_max = 0
node_min = 100

row_max = 1
row_min = 10000

mbps_max = 1
mbps_min = 10000

def check_boundaries(linedic):

	global row_max, row_min, mbps_max, mbps_min, node_max, node_min


	if linedic['NrRows'] > row_max:
		row_max = int(linedic['NrRows'])

	if linedic['NrRows'] < row_min:
		row_min = int(linedic['NrRows'])

	if linedic['Mps'] > mbps_max:
		mbps_max = linedic['Mps']

	if linedic['Mps'] < mbps_min:
		mbps_min = linedic['Mps']

	if linedic['MpiSize']/ppn > node_max:
		node_max = int(linedic['MpiSize'])/ppn

	if linedic['MpiSize']/ppn < node_max:
		node_min = int(linedic['MpiSize'])/ppn


def add_point(linedic):


	#######
	plt.figure(1)
	color = (linedic['NrRows']-row_min)/(row_max-row_min)
	plt.scatter(linedic['MpiSize']/ppn, linedic['Mps'], c=(color, 1 - color , 0), s=5, edgecolors='none')

	#######
	plt.figure(2)
	color = (linedic['MpiSize']/ppn - node_min) / (node_max - node_min)
	if color > 1:
		color = 1
	plt.scatter(linedic['NrRows'], linedic['Mps'], c=(color, 1 - color , 0), s=5, edgecolors='none')


def save_fig():
	print node_max
	print node_min

	#######
	plt.figure(1)
	for i in range(row_min, row_max+1, 1000):
		colour = (float)(i-row_min)/(row_max-row_min)
		plt.scatter([],[], c=(colour, 1 - colour , 0), s=20, edgecolors='none', label=str("{0} Rows".format(i)))
	plt.legend(loc = 4)
	plt.grid()
	plt.xlim([node_min - 1, node_max + 10])
	plt.ylim([mbps_min - 100, mbps_max + 100])
	plt.xlabel('Number of Nodes ({0} processes per node)'.format(ppn))
	plt.ylabel('Total throughput in MB/s (cache saturated)')
	plt.figtext(.10, .94, "Parallel AdiosStMan (v0.3.6) testing, iVEC Fornax, Lustre Stripe Size = 8, \nSingle column with direct arrays, Array size = {0}MB, Table size = {0}MB * Rows".format(array_size))
	plt.savefig('fig1.eps')

	#######
	plt.figure(2)
	for i in range(10, node_max, 10):
		color = (float)(i)/node_max
		plt.scatter([],[], c=(color, 1 - color , 0), s=20, edgecolors='none', label=str("{0} Nodes".format(i)))
	plt.legend()
	plt.grid()
	plt.xlim([row_min - 100, row_max + 100])
	plt.ylim([mbps_min - 100, mbps_max + 100])
	plt.xlabel('Number of Rows')
	plt.ylabel('Total throughput in MB/s (cache saturated)')
	plt.figtext(.10, .94, "Parallel AdiosStMan (v0.3.6) testing, iVEC Fornax, Lustre Stripe Size = 8, \nSingle column with direct arrays, Array size = {0}MB, Table size = {0}MB * Rows".format(array_size))
	plt.savefig('fig2.eps')

#######  main

logfile = open('log','r')

for line in logfile:

	linedic = {}

	try:
		linelist = line.strip().split(',')
		for i in range(len(linelist)/2):
			linedic[linelist[i*2]] = float(linelist[i*2+1])
		check_boundaries(linedic)
	except:
		continue


logfile = open('log','r')

for line in logfile:

	linedic = {}

	try:
		linelist = line.strip().split(',')
		for i in range(len(linelist)/2):
			linedic[linelist[i*2]] = float(linelist[i*2+1])
		add_point(linedic)
	except:
		continue

save_fig()








