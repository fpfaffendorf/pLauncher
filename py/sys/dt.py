import sys
import os

if len(sys.argv) > 1:
	if sys.argv[1] == "--help":
		quit()

print os.popen("date").read()
