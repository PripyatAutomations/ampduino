#if	!defined(_antenna_h)
#define	_antenna_h
class ad_Antenna {
    private:
        char *description;		// Short (<120 char) description
        unsigned int height;		// Height AMSL in meters
        bool	tunable;		// Does it have adjustable tuning?
};
#endif
