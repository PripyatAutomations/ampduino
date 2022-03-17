#if	!defined(_serial_h)
#define	_serial_h

#if	defined(CF_SERIAL)
//
// Define the generic serial interface
//
class ad_Serial {
    private:
        bool	active;
    public:
        bool	Write(const char *pkt);
};

// defined(CF_SERIAL)
#endif

// !defined(_serial_h)
#endif
