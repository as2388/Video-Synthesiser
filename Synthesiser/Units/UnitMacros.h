#define IN(index)  (unit->mFloatInBuf[index])
#define OUT(index) (unit->mFloatOutBuf[index])
#define ZOFF (0)
#define ZIN(i) (IN(i) - ZOFF)	// get buffer pointer offset for iteration
#define ZIN0(i) (IN(i)[0])		// get first sample
#define ZOUT(i) (OUT(i) - ZOFF)		// get buffer pointer offset for iteration
#define ZOUT0(i) (OUT(i)[0])		// get first sample
#define LOOP(length, stmt) for (int xxi=0; xxi<(length); ++xxi) { stmt; }
#define ZXP(z) (*(z)++)
#define SETCALC(func) (unit->mCalcFunc = (UnitCalcFunc)&func)
#define sc_max(a,b) (((a) > (b)) ? (a) : (b))
#define sc_min(a,b) (((a) < (b)) ? (a) : (b))
