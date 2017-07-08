# -------------------------------------------------------------------------------------------------------------------------------------------------------------
from lib import meeus
import sys
import datetime
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Main Program
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

if len(sys.argv) == 2 and sys.argv[1] == "--help":

	print "RA Hour (Epoch 2000.0)"
	print "RA Min (Epoch 2000.0)"
	print "RA Sec (Epoch 2000.0)"
	print "Dec Deg (Epoch 2000.0)"
	print "Dec Min (Epoch 2000.0)"
	print "Dec Sec (Epoch 2000.0)"

else:

	if len(sys.argv) == 7:

		now = datetime.datetime.utcnow()
		year = now.year
		month = now.month
		day = now.day
		hour = now.hour
		minute = now.minute
		second = now.second

		loc = meeus.location()
		loc[3] *= -1

		r = meeus.az_alt('g', year, month, day, hour, minute, second, loc[0], loc[1], loc[2], loc[3], loc[4], loc[5], float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3]), float(sys.argv[4]), float(sys.argv[5]), float(sys.argv[6]))

		print "UT   %02d:%02d:%02d %d/%02d/%02d" % (hour, minute, second, year, month, day)
		print "Az.  %dd %dm %ds" % (r[0][0], r[0][1], r[0][2])
		print "Alt. %dd %dm %ds" % (r[1][0], r[1][1], r[1][2])
