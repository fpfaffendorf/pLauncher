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
def degree_to_decimal (d, m, s):

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
# Calendar to Julian Date
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def jd (calendar, year, month, day):

	if (month <= 2):
		year = year - 1
		month = month + 12
	
	a = int_meeus(year / 100)

	if (calendar == "g"):
		b = 2 - a + int_meeus(a / 4)
	elif (calendar == "j"):
		b = 0

	return int_meeus(365.25 * (year + 4716)) + int_meeus(30.6001 * (month + 1)) + day + b - 1524.5

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Centuries from the Epoch J2000.0
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def time_t(calendar, year, month, day):

	return (jd(calendar, year, month, day) - 2451545.0) / 36525

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Less precise implementation (delta psi +/- 0.5 seconds; delta epsilon +/- 0.1 seconds)
# Return seconds of degree
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def nutation_longitude(calendar, year, month, day):

	t = time_t(calendar, year, month, day)
	omega = 125.04452 - 1934.136261 * t 

	l = 280.4665 + 36000.7698 * t
	lp = 218.3165 + 481267.8813 * t

	delta_psi = -17.20 * (math.sin(degree_to_rad(omega))) 
	delta_psi = delta_psi - (1.32 * (math.sin(degree_to_rad(2*l)))) 
        delta_psi = delta_psi - (0.23 * (math.sin(degree_to_rad(2*lp)))) 
        delta_psi = delta_psi + (0.21 * (math.sin(degree_to_rad(2*omega))))

	return delta_psi

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# True obliquity of the ecliptic 
# Expressed in degree
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def true_obliquity_ecliptic(calendar, year, month, day):

        t = time_t(calendar, year, month, day)
        omega = 125.04452 - 1934.136261 * t

        l = 280.4665 + 36000.7698 * t
        lp = 218.3165 + 481267.8813 * t

	delta_epsilon = 9.20 * math.cos(degree_to_rad(omega))
	delta_epsilon = delta_epsilon + 0.57 * math.cos(degree_to_rad(2*l))
	delta_epsilon = delta_epsilon + 0.10 * math.cos(degree_to_rad(2*lp))
	delta_epsilon = delta_epsilon + 0.09 * math.cos(degree_to_rad(2*omega))

	s = -46.8150 * t - 0.00059 * t * t + 0.001813 * t * t * t

	epsilon_zero = ((degree_to_decimal(23, 26, 21.448) * 3600) + s) / 3600

	return ((epsilon_zero * 3600) + delta_epsilon) / 3600

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Mean sidereal time
# Expressed in hours
# Hour, min, sec expressed in UT
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def mean_sidereal_time_greenwich(calendar, year, month, day, hour, min, sec):

	t = time_t(calendar, year, month, day)
	s = 8640184.812866 * t + 0.093104 * t * t - 0.0000062 * t * t * t

	c = 1.00273790935 * (hms_to_decimal(hour, min, sec) * 3600) 

	while (s < 0):
		s = s + 86400

	st = ((hms_to_decimal(6, 41, 50.54841) * 3600) + s + c) / 3600

	while (st >= 24):
		st = st - 24

	return st

# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Aparent sidereal time (with nutation in RA)
# Expressed in hours
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def aparent_sidereal_time_greenwich(calendar, year, month, day, hour, min, sec):

	nutation_ra = (nutation_longitude(calendar, year, month, day) * math.cos(degree_to_rad(true_obliquity_ecliptic(calendar, year, month, day)))) / 15
	
	st = mean_sidereal_time_greenwich(calendar, year, month, day, hour, min, sec)
	st = ((st * 3600) + nutation_ra) / 3600

	while (st >= 24):
		st = st - 24

	return st
	
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
# Azimuth and Altitude 
# -------------------------------------------------------------------------------------------------------------------------------------------------------------
def az_alt(calendar, year, month, day, hour, min, sec, lat_deg, lat_min, lat_sec, lon_deg, lon_min, lon_sec, ra_hour, ra_min, ra_sec, dec_deg, dec_min, dec_sec):

	ast = aparent_sidereal_time_greenwich(calendar, year, month, day, hour, min, sec);
	l = degree_to_decimal(lon_deg, lon_min, lon_sec) * 24 / 360
	alpha = hms_to_decimal(ra_hour, ra_min, ra_sec)	

	h = (ast - l - alpha) * 360 / 24

	while (h < 0):
		h = h + 360

	aux_1 = math.sin(degree_to_rad(h)) 
	aux_2 = math.cos(degree_to_rad(h)) * math.sin(degree_to_rad(degree_to_decimal(lat_deg, lat_min, lat_sec)))
	aux_3 = math.tan(degree_to_rad(degree_to_decimal(dec_deg, dec_min, dec_sec))) * math.cos(degree_to_rad(degree_to_decimal(lat_deg, lat_min, lat_sec)))
	tan_a = aux_1 / (aux_2 - aux_3)

	az = rad_to_degree(math.atan(tan_a))

	if (aux_1 < 0):
		if (tan_a < 0):
			az = az + 180
		else:
			az = az
	else:
		if (tan_a < 0):
			az = az + 360
		else:
			az = az + 180


	sin_h = math.sin(degree_to_rad(degree_to_decimal(lat_deg, lat_min, lat_sec))) *  math.sin(degree_to_rad(degree_to_decimal(dec_deg, dec_min, dec_sec)))
	sin_h = sin_h + math.cos(degree_to_rad(degree_to_decimal(lat_deg, lat_min, lat_sec))) *  math.cos(degree_to_rad(degree_to_decimal(dec_deg, dec_min, dec_sec))) * math.cos(degree_to_rad(h))

	coord = [decimal_to_degree(az), decimal_to_degree(rad_to_degree(math.asin(sin_h)))]
	return coord

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

	now = datetime.datetime.utcnow()
	year = now.year
	month = now.month
	day = now.day
	hour = now.hour
	minute = now.minute
	second = now.second
	r = az_alt('g', year, month, day, hour, minute, second, -34, 42, 05.5, 58, 19, 05.8, float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3]), float(sys.argv[4]), float(sys.argv[5]), float(sys.argv[6]))

	print "Date UTC %dy %dm %dd" % (year, month, day)
	print "Time UTC %dh %dm %ds" % (hour, minute, second)
	print "Az. %dd %dm %ds" % (r[0][0], r[0][1], r[0][2])
	print "Alt. %dd %dm %ds" % (r[1][0], math.fabs(r[1][1]), math.fabs(r[1][2]))
