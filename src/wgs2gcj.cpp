#include "wgs2gcj.h"
#include <stdio.h>
#ifndef _WIN32
#include <stdbool.h>
#endif  // _WIN32
#include <math.h>

static const double pi = 3.14159265358979324;
static const double a = 6378245.0;
static const double ee = 0.00669342162296594323;

static bool out_of_china(double lat, double lon)
{
	if (lon < 72.004 || lon > 137.8347)
	{
		return true;
	}
	
	if (lat < 0.8293 || lat > 55.8271)
	{
		return true;
	}

	return false;
}

static double transform_lat(double x, double y)
{
	double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(fabs(x));
	ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
	ret += (20.0 * sin(y * pi) + 40.0 * sin(y / 3.0 * pi)) * 2.0 / 3.0;
	ret += (160.0 * sin(y / 12.0 * pi) + 320 * sin(y * pi / 30.0)) * 2.0 / 3.0;
	return ret;
}

static double transform_lon(double x, double y)
{
	double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(fabs(x));
	ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
	ret += (20.0 * sin(x * pi) + 40.0 * sin(x / 3.0 * pi)) * 2.0 / 3.0;
	ret += (150.0 * sin(x / 12.0 * pi) + 300.0 * sin(x / 30.0 * pi)) * 2.0 / 3.0;
	return ret;
}

void wgs2gcj(double lat, double lon, double* m_lat, double* m_lon)
{
	if (out_of_china(lat, lon))
	{
		if (m_lat)
		{
			*m_lat = lat;
		}

		if (m_lon)
		{
			*m_lon = lon;
		}

		return;
	}

	double d_lat = transform_lat(lon - 105.0, lat - 35.0);
	double d_lon = transform_lon(lon - 105.0, lat - 35.0);
	double rad_lat = lat / 180.0 * pi;
	double magic = sin(rad_lat);
	magic = 1 - ee * magic * magic;
	double sqrt_magic = sqrt(magic);
	d_lat = (d_lat * 180.0) / ((a * (1 - ee)) / (magic * sqrt_magic) * pi);
	d_lon = (d_lon * 180.0) / (a / sqrt_magic * cos(rad_lat) * pi);

	if (m_lat)
	{
		*m_lat = lat + d_lat;
	}

	if (m_lon)
	{
		*m_lon = lon + d_lon;
	}
}
