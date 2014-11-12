#include "gcj2wgs.h"
#include "wgs2gcj.h"

void gcj2wgs(double lat, double lon, double* m_lat, double* m_lon)
{
	double t_lat, t_lon;

	wgs2gcj(lat, lon, &t_lat, &t_lon);

	double d_lat = t_lat - lat;
	double d_lon = t_lon - lon;

	if (m_lat)
	{
		*m_lat = lat - d_lat;
	}

	if (m_lon)
	{
		*m_lon = lon - d_lon;
	}
}
