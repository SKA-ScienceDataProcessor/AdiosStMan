from pyrap.tables import *

oldtable='/Volumes/RAID/Data/casa/image_1104_1128/image_1104_1128.cube'
newtable='/Volumes/RAID/Data/casa/image_1104_1128/image_1104_1128_new.cube'



t = table(oldtable)

dmdef = t.getdminfo()

print 'Original Table: **************************'
for i in dmdef:
	print i
	print dmdef[i]



dmdef['*17']['TYPE'] = 'AdiosStMan'
print 'New Table: ***********************'
for i in dmdef:
	print i
	print dmdef[i]

#t.copy (newtable, True, True, dminfo=dmdef)
