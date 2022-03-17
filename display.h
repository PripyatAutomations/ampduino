#if	!defined(_display_h)
#define	_display_h

#if	defined(CF_DISPLAY)
extern void print_alert(const char *msg);
extern void print_log(const char *msg);

class ad_Display {
    private:
        bool enabled;
    public:
        bool Enable(void);
        bool Disable(void);
};
// defined(CF_DISPLAY)
#endif

// !defined(_display_h)
#endif
