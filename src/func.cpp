#include "func.h"
#include <cmath>
#include "log.h"

double cpx_fescape(cx cm, cx cns){
	/*double ang = cns.re;
	cx mp(0.7885 * cos(ang), 0.7885 * sin(ang));
	return (double)(1 + sqrt(1 + mp.rad() * 4))*3;
	*/
	return 4;
}

// z_(n+1) = (z_n)^2 + c
cx cpx_func(cx cm, cx cns){
	//double ang = cns.re;
	//cx mp(0.7885 * cos(ang), 0.7885 * sin(ang));
	cx mp(-0.835, -0.321);
	//clog(cm);
	//clog(mp);
	return cm.square() + mp;
}
