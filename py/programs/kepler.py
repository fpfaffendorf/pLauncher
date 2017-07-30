# -------------------------------------------------------------------------------------------------------------------------------------------------------------
from lib import meeus
import sys
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Main Program
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

if len(sys.argv) == 2 and sys.argv[1] == "--help":

	print "TXT"
	print "Mean Anomaly (degree)"
	print "Eccentricity"
	print "Semi-major axis"

else:

	M = float(sys.argv[1])
	e = float(sys.argv[2])
	a = float(sys.argv[3])

	E = meeus.find_E(M, e)
	E_decimal = meeus.dms_to_decimal(E[0], E[1], E[2])
	v = meeus.find_v(e, E_decimal)
	v_decimal = meeus.dms_to_decimal(v[0], v[1], v[2])
	r = meeus.find_r(a, e, E_decimal)

	print "Eccentric Anomaly"
	print "%dd %dm %ds | %fd" % (E[0], E[1], E[2], E_decimal)
	print "True Anomaly"
	print "%dd %dm %ds | %fd" % (v[0], v[1], v[2], v_decimal)
	print "Radius %f" % (r)
