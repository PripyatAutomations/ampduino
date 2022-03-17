#if	!defined(__safety_h)
#define	__safety_h

extern bool tx_ok;
extern bool Transmitting;
extern bool PendingTransmission;

extern bool CanTransmit(void);
extern bool PendingTransmit(void);
extern bool SWR_Lockout(void);
extern bool CheckThermals(void);
extern bool CheckVoltages(void);
extern bool CheckCurrents(void);

#endif
