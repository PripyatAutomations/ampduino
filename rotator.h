//
// Support for antenna rotors
#if	!defined(_rotator_h)
#define	_rotator_h
struct Coordinate {
    unsigned int x, y, z;
};
typedef struct Coordinate Coordinate;

class ad_Rotator {
    private:
        Coordinate min, max, current;
    public:
        Coordinate *GetPosition(void);
        bool SetPosition(Coordinate *c);
        bool SetPosition(unsigned int x, unsigned int y, unsigned int z);
};

#endif
