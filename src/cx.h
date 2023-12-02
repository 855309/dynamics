#ifndef _D_CX_H
#define _D_CX_H

#include <string>

class cx {
public:
	double re, im;
	
	cx();
	cx(double _re, double _im);
	cx(double _re);
	
	double orad();
	double rad();
	
	cx operator+(cx const& rhs);
	cx operator-(cx const& rhs);
	cx operator*(cx const& rhs);
	cx operator/(cx const& rhs);
	
	cx maxr(cx n);
	cx square();
	
	std::string str();
};

#endif
