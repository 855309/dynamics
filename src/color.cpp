#include "color.h"

#include <cmath>

double smoothsq(double x, double dlt){
	return sin(x) / sqrt(dlt*dlt + sin(x)*sin(x));
}

double fr_ml = 1.25;
vec3 colfunc(double t, double maxt, double dlt){
	// y: (1/2) * (1 + smoothsq((3*M_PI/maxt) * (t - M_PI/4)))
	// z: (1/2) * (1 - smoothsq(M_PI/2 - (3*M_PI/maxt) * (t - M_PI/4)))
	return vec3((double)t/(double)maxt, 0.5 * (1 + smoothsq((2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)), 0.5 * (1 - smoothsq(M_PI/2 - (2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)));
}
