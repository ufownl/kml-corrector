#ifndef __kml_corrector_gcj2wgs_h__
#define __kml_corrector_gcj2wgs_h__

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void gcj2wgs(double lat, double lon, double* m_lat, double* m_lon);
	
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __kml_corrector_gcj2wgs_h__
