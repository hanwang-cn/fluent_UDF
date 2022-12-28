#include "udf.h"
#include "math.h"

#include "macro_defines.h"

DEFINE_DELTAT(def_deltat, d)
{
	real deltat;
	real rtime = RP_Get_Real("flow-time");
	real time_per_layer = (END - START) / WELDING_VELOCITY;
	/*using sin to control the time, and its derivate*/
	real ST = sin(2 * M_PI * FREQUENCY * rtime);
	real dSTdrtime = cos(2 * M_PI * FREQUENCY * rtime);
	if (ST >= 0 && ST <= 0.7 && dSTdrtime > 0. && rtime <= time_per_layer)
	{
		deltat = 0.00002;
	}
	else if (ST > 0.7 && rtime <= time_per_layer)
	{
		deltat = 0.00001;
	}
	else if (ST >= -0.5 && ST <= 0.7 && dSTdrtime < 0. && rtime <= time_per_layer)
	{
		deltat = 0.00002;
	}
	else if (ST < 0 && rtime <= time_per_layer)
	{
		deltat = 0.00004;
	}
	else
	{
		deltat = 0.0005;
	}
	return deltat;
}
