# -------------------------------------------------------------------------------------------------------------------------------------------------------------
from lib import meeus
import sys
import math
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Main Program
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

if len(sys.argv) == 2 and sys.argv[1] == "--help":

	print "TXT"
	print "Wind Direction"
	print "Wind Speed"
	print "True Course"
	print "Indicated Air Speed"
	print "Altitude"

else:

	w = meeus.degree_to_rad(float(sys.argv[1]))
	Vw = float(sys.argv[2])
	d = meeus.degree_to_rad(float(sys.argv[3]))
	Va = float(sys.argv[4]) * (1 + (float(sys.argv[5]) / 1000 * 0.02 ))

	swc = (Vw / Va) * math.sin(w - d)
	heading = meeus.rad_to_degree(d + math.asin(swc))
	if (heading > 360):
		heading -= 360
	gs = Va * math.sqrt(1 - math.pow(swc, 2)) - (Vw * math.cos(w - d))

	wca = (meeus.rad_to_degree(d) - heading)
	dir = "L"
	if (wca <= 0): 
		dir = "R"
		wca *= -1

	print "Heading | %dd" % (heading)
        print "WCA     | %dd %s" % (wca, dir)
	print "IAS     | %s" % (sys.argv[4])
	print "GS      | %d" % (gs)
	print "TAS     | %d" % (Va)
