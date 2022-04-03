//
// Temperature conversion macros for thermal stuff
#if	!defined(_thermal_h)
#define	_thermal_h

#define	DegCtoDegF(x)	((x * 1.8) + 32)
#define	DegFtoDegC(x)	((x - 32) / 1.8)

#endif
