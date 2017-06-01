# -------------------------------------------------------------------------------------------------------------------------------------------------------------
from __future__ import division		# Force floating point division
import sys
import math
import datetime
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# PI constant
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def pi():

	return math.pi

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# INT according to meeus
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def int_meeus (n):

	if (n < 0):
		return int(n) - 1
	else:
		return int(n)

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# RAD to degree
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def rad_to_degree (n):

	return n * 180 / pi()

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Degree to RAD
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def degree_to_rad (n):

	return n * pi() / 180

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# HMS to decimal conversion 
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def hms_to_decimal (h, m, s):

	if (h < 0):
		m = m * -1;
		s = s * -1;
	
	m = m + (s / 60)
	h = h + (m / 60)

	return h

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Decimal to HMS conversion 
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def decimal_to_hms (h):

	a = [0, 0, 0]

	a[0] = h
	a[1] = (h - int(h)) * 60
	a[2] = (a[1] - int(a[1])) * 60

	a[0] = int(a[0])
	a[1] = int(a[1])
	return a

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Degree to decimal conversion 
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def dms_to_decimal (d, m, s):

	if (d < 0):
		m = m * -1;
		s = s * -1;

        m = m + (s / 60)
        d = d + (m / 60)

        return d

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Decimal to HMS conversion 
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def decimal_to_degree (d):

	a = [0, 0, 0]

	a[0] = d
	a[1] = (d - int(d)) * 60
	a[2] = (a[1] - int(a[1])) * 60

	a[0] = int(a[0])
	a[1] = int(a[1])
	return a
	
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Find E
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

def find_E (M, e):

	M = degree_to_rad(M)
	E = M
	new_E = M

	while True:

		E = new_E
		new_E = E + ( M + e * math.sin(E) - E ) / ( 1 - e * math.cos(E) ) 

		if (E == new_E): break;

	return decimal_to_degree (rad_to_degree(new_E))

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Find v
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

def find_v (e, E):

	E = degree_to_rad(E)
	return decimal_to_degree(rad_to_degree(math.atan(math.sqrt((1 + e) / (1 - e)) * math.tan (E / 2)) * 2))

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Find r
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

def find_r (a, e, E):

	E = degree_to_rad(E)
	return a * ( 1 - e * math.cos(E) )

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Main Program
# -------------------------------------------------------------------------------------------------------------------------------------------------------------

if len(sys.argv) == 2 and sys.argv[1] == "--help":

	print "Mean Anomaly (degree)"
	print "Eccentricity"
	print "Semi-major axis"

else:

	M = float(sys.argv[1])
	e = float(sys.argv[2])
	a = float(sys.argv[3])

	E = find_E(M, e)
	E_decimal = dms_to_decimal(E[0], E[1], E[2])
	v = find_v(e, E_decimal)
	v_decimal = dms_to_decimal(v[0], v[1], v[2])
	r = find_r(a, e, E_decimal)

	print "Eccentric Anomaly"
	print "%dd %dm %ds | %fd" % (E[0], E[1], E[2], E_decimal)
	print "True Anomaly"
	print "%dd %dm %ds | %fd" % (v[0], v[1], v[2], v_decimal)
	print "Radius %f" % (r)
