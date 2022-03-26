#if	!defined(__safety_h)
#define	__safety_h

class Safety {
    private:
        bool	tx_ok;
        bool	Transmitting;
        bool	PendingTransmission;
    public:
        bool CanTransmit(void);
        bool PendingTransmit(void);
        bool SWR_Lockout(void);
        bool CheckThermals(void);
        bool CheckVoltages(void);
        bool CheckCurrents(void);
};


#endif
