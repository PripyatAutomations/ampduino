//
// Support for antenna rotors
#if	!defined(_rotator_h)
#define	_rotator_h
class ad_Rotator {
    private:
        unsigned int	x_angle_min, x_angle_max;
        unsigned int	y_angle_min, y_angle_max;
        unsigned int	z_angle_min, z_angle_max;
        unsigned int	x_angle, y_angle, z_angle;
};

#endif
