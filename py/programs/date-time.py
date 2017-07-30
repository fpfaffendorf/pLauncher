# -------------------------------------------------------------------------------------------------------------------------------------------------------------
from lib import meeus
import sys
import datetime
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Main
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

if len(sys.argv) > 1 and sys.argv[1] == "--help":

	print "TXT"
	quit()

else:

	locnow = datetime.datetime.today()
	utcnow = datetime.datetime.utcnow()

	tdtnow = meeus.tdt (utcnow.year, utcnow.month, utcnow.day, utcnow.hour, utcnow.minute, utcnow.second)

	print "Loc %02d:%02d:%02d %d/%02d/%02d" % (locnow.hour, locnow.minute, locnow.second, locnow.year, locnow.month, locnow.day)
	print "UT  %02d:%02d:%02d %d/%02d/%02d" % (utcnow.hour, utcnow.minute, utcnow.second, utcnow.year, utcnow.month, utcnow.day)
	print "TDT %02d:%02d:%02d %d/%02d/%02d" % (tdtnow[3], tdtnow[4], tdtnow[5], tdtnow[0], tdtnow[1], tdtnow[2])
	print "Loc JD %.2f" % (meeus.jd ("g", locnow.year, locnow.month, locnow.day, locnow.hour, locnow.minute, locnow.second)) 
	print "UT  JD %.2f" % (meeus.jd ("g", utcnow.year, utcnow.month, utcnow.day, utcnow.hour, utcnow.minute, utcnow.second))
	print "Prueba"
