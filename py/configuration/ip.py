import sys
import os

if len(sys.argv) > 1:
	if sys.argv[1] == "--help":
		print "TXT"
		quit()

ifconfig = os.popen("ifconfig").read()

interface = False
for line in ifconfig.splitlines():
	if line.startswith("wlan0"):
		interface = True
	else:
		if interface:
			if "inet addr:" in line:
				ip = line.strip()
				ip = ip.split(' ')
				print ip[1]

