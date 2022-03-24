#if	!defined(_serial_h)
#define	_serial_h

#if	defined(CF_SERIAL)
//
// Define the generic serial interface
//
class ad_Serial {
    private:
        bool	active;
        int	pin_tx;
        int	pin_rx;
        int	baud_rate;
    public:
        bool	Write(const char *pkt);
        bool	Read(char *buf, int size);
};

// defined(CF_SERIAL)
#endif

// !defined(_serial_h)
#endif
