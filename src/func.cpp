#include "func.h"

// z_(n+1) = (z_n)^2 + c
cx cpx_func(cx cm, cx cns){
	return cm*cm + cns;
}
