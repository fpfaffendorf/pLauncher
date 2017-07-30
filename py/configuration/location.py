import sys

if (sys.argv[1] == "--help"):

	print "TXT"
	print "Lat Degrees"
	print "Lat Minutes"
	print "Lat Seconds"
	print "Long Degrees"
	print "Long Minutes"
	print "Long Seconds"
	print "Alt Meters"

else:

	file = open("/root/configuration/location.data", "w")
	for i in range(1, 8):
		file.writelines(sys.argv[i] + "\n")
	file.close()
	
	print "Lat: %s %s %s" % (sys.argv[1], sys.argv[2], sys.argv[3])
	print "Long: %s %s %s" % (sys.argv[4], sys.argv[5], sys.argv[6])
	print "Alt: %s meters" % (sys.argv[7]) 
	print "Saved !"
