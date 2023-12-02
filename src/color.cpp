#include "color.h"

#include <cmath>
#include "log.h"

double cfc(double n, double c, double r){
	return sqrt(r*r - (n-c)*(n-c));
}

int pathln = 9;
double pdiff = (double)1/(double)(pathln - 1);
vec3 path[] = {
	vec3(0, 0, 127),
	vec3(0, 0, 255),
	vec3(0, 127, 255),
	vec3(0, 255, 255),
	vec3(127, 255, 127),
	vec3(255, 255, 0),
	vec3(255, 127, 0),
	vec3(255, 0, 0),
	vec3(127, 0, 0)
};

vec3 jet(double x){
	int p = floor(x / pdiff);
	if(p == pathln - 1){
		return vec3(0,0,0);
	}
	
	vec3 c1 = path[p];
	vec3 c2 = path[p + 1];
	
	double s = (x / pdiff) - p;
	
	return (c1 + (c2 - c1) * s);
}

vec3 colfunc(double t, double maxt){
	// y: (1/2) * (1 + smoothsq((3*M_PI/maxt) * (t - M_PI/4)))
	// z: (1/2) * (1 - smoothsq(M_PI/2 - (3*M_PI/maxt) * (t - M_PI/4)))
	//return vec3((double)t/(double)maxt, 0.5 * (1 + smoothsq((2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)), 0.5 * (1 - smoothsq(M_PI/2 - (2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)));
	if(t == 0){
		return vec3(0,0,0);
	}
	
	vec3 l = jet(1 - t/maxt);
	return l;
}
