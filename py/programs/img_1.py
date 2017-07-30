# -------------------------------------------------------------------------------------------------------------------------------------------------------------
from __future__ import print_function
from lib import meeus
import sys
import math
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Main Program
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

if len(sys.argv) == 2 and sys.argv[1] == "--help":

	print ("IMG")
        print ("Negative (1-Yes 0-No)")

else:

	img = [
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 
	  0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x80, 0x7F, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 
	  0x00, 0xF8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x3F, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x00, 0x80, 0x0F, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3B, 0xED, 
	  0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0xE0, 0xF3, 0xF4, 0x03, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x4F, 0x1F, 0x03, 0x00, 0x78, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFD, 0x8F, 
	  0x01, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0xFC, 0xFD, 0x30, 0x00, 0x00, 0xFC, 0x01, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0x70, 0x01, 0x00, 0xBC, 0x03, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF0, 
	  0x01, 0xC0, 0xB0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x80, 0xFF, 0xE7, 0xF9, 0x03, 0xE0, 0xF1, 0x07, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x03, 0xA0, 0xFD, 0x0F, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x9F, 0x3F, 
	  0x03, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0xC0, 0xFF, 0x1F, 0x0F, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x5F, 0x06, 0x00, 0x60, 0x97, 0x1F, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x7F, 0x03, 
	  0x00, 0xE0, 0xA1, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0xF0, 0xFF, 0xFF, 0x01, 0x00, 0xE0, 0x20, 0x3D, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x0E, 0x70, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xFF, 0x7F, 0x00, 
	  0x00, 0xE0, 0x0F, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x38, 0xFD, 0x3F, 0x00, 0x00, 0xF0, 0xBF, 0x63, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x38, 0xFD, 0x20, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7A, 0x00, 0x00, 
	  0x00, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x18, 0x7A, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x70, 0x02, 0x00, 
	  0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x1C, 0xE0, 0x07, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x0F, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x8C, 0x01, 
	  0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x1C, 0x00, 0xF8, 0x1F, 0x00, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0xC0, 0x3F, 0x00, 0xF8, 0xFE, 0xFF, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0xC0, 0xFF, 
	  0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x18, 0x00, 0xE0, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xF0, 0xFF, 0x01, 0x00, 0xF0, 0xFF, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xF0, 0xFF, 
	  0x1F, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x38, 0x00, 0xF0, 0xFF, 0x3F, 0x00, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xE0, 0xFF, 0x3F, 0x00, 0xE0, 0x7F, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xC0, 0xFF, 
	  0x3F, 0x00, 0xE0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x70, 0x00, 0xC0, 0xFF, 0x1F, 0x00, 0xE0, 0x7F, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x80, 0xFF, 0x1F, 0x00, 0xE0, 0x7F, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0xFE, 
	  0x1F, 0x00, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0xE0, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xFE, 0x03, 0x00, 0xE0, 0x1F, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0xFE, 
	  0x01, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x80, 0x03, 0x00, 0xFE, 0x03, 0x00, 0xC0, 0x0F, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0xFE, 0x03, 0x00, 0x80, 0x0F, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xFE, 
	  0x01, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x0F, 0x00, 0xFE, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x7E, 0x00, 0x00, 0xC0, 0x01, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x1C, 
	  0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x78, 0x00, 0x1C, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x1C, 0x00, 0x00, 0x78, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x3C, 
	  0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0xC0, 0x07, 0x38, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x30, 0x00, 0xC0, 0x07, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x20, 
	  0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0xF8, 0x03, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0xF8, 0x3F, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 
	  0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00
	]

	if (sys.argv[1] == '1'):
		for e in img:
			print(chr(0xFF - e), end='')
	else:
		for e in img:
			print(chr(e), end='')	