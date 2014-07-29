#!/opt/local/bin/python
"""
Author: Alberto Uriarte
Program: unitTiming.py
Date: 7/28/2014
Description: Calculates at what frame the player construct the
required units in the global unitsToSearch {'unit name', number of units}
"""

import os, fnmatch

# -----------------------------------------------------------------
#  CONFIG
# -----------------------------------------------------------------

unitsToSearch = {'Protoss Zealot': 20, 'Protoss Dragoon': 5}

# -----------------------------------------------------------------
#  STARTING EXECUTION
# -----------------------------------------------------------------

# setting counter
unitsCounter = unitsToSearch.copy()
for k in unitsCounter:
	unitsCounter[k] = 0

results = {}

for root, dirs, files in os.walk("Protoss"):
	
	filePaths = []
	if root != 'Protoss':
		for filename in fnmatch.filter(files, "*.short*"):
			filePaths.append(os.path.join(root, filename))

		print 'Processing {} ({} files)'.format(root, len(filePaths))

		for filePath in filePaths:
			fileBuffer = open(filePath, 'r')

			for fileLine in fileBuffer:
				line = fileLine.rstrip('\r\n')
				if line != '' and not("@" in line):
					orders = line.split(',')
					# look for all the keys
					if orders[4] in unitsToSearch:
						if unitsCounter[orders[4]] < unitsToSearch[orders[4]]:
							unitsCounter[orders[4]] += 1
							# print orders[0], unitsCounter
						# check counters
						if unitsCounter == unitsToSearch:
							frames = int(orders[0])
							if frames in results:
								results[frames] += 1
							else:
								results[frames] = 1
							break

results = sorted(results.items())

print 'Times: {}'.format(results)