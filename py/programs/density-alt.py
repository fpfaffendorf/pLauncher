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
	print "Elevation (Ft)"
	print "Air Temp (C)"
	print "Altimeter (hPa)"
	print "Rel Humidity %"

else:

	elevation = float(sys.argv[1])
	air_temp = float(sys.argv[2])
	altimeter = float(sys.argv[3])
	rel_humidity = float(sys.argv[4])

	altimeter_inch = altimeter * 29.92 / 1013.25

	dew_point = 237.3/(1/(math.log(rel_humidity / 100)/17.27+air_temp/(air_temp+237.3))-1);
	pressure_alt = ((1013 - altimeter) * 30) + elevation
	isa_temp = 15 - (elevation * 2 / 1000)
	density_alt = pressure_alt + (120 * (air_temp - isa_temp))

	print "Dew Point     | %.2fC" % (dew_point)
	print "Pressure Alt  | %dft" % (pressure_alt)
	print "Density Alt   | %dft" % (density_alt)
	print "Pressure \"Hg  | %.2f" % (altimeter_inch)
