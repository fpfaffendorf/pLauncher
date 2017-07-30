import sys
import os

if len(sys.argv) > 1:
        if sys.argv[1] == "--help":
		print "TXT"
		print "Enabled(1) Disabled(0)"
                quit()

	else:
		wifi = ""

		if sys.argv[1] == "1":
			wifi = os.popen("wifi up").read()
			print "wifi up"
		else:
			wifi = os.popen("wifi down").read()
			print "wifi down"

