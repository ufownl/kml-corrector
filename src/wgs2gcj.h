#ifndef __kml_corrector_wgs2gcj_h__
#define __kml_corrector_wgs2gcj_h__

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void wgs2gcj(double lat, double lon, double* m_lat, double* m_lon);
	
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __kml_corrector_wgs2gcj_h__
