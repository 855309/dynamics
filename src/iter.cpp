#include "iter.h"

#include "func.h"
#include "cx.h"
#include "color.h"
#include "log.h"

sf::Image c_img;

int iterations = 100;
void set_itrn(int n){
	iterations = n;
}

int esc_ords = 4; // for z^2 + c
int iterate(cx cm, int num){
	cx res;
	if(cm.orad() > esc_ords) return 0;
	
	for(int i = 1; i <= num; i++){
		res = cpx_func(res, cm);
		if(res.orad() > esc_ords){
			return i;
		}
	}
	
	return num;
}

double delta = 0.0001;
void fillpix(vec2 pos, int et){
	vec3 col = colfunc(iterations - et, iterations, delta);
	sf::Color cl(255 * col.x, 255 * col.y, 255 * col.z);
	c_img.setPixel(pos.x, pos.y, cl);
}

void paint(vec2 sx, vec2 sy, int w, int h){
	ins_lf(0);
	clog("Started iteration:");
	clog(iterations);
	clog("iterations.");
	clnl();
	
	c_img.create(w, h, sf::Color::White);
	double sc_fx = (sx.y - sx.x)/((double)w);
	double sc_fy = (sy.y - sy.x)/((double)h);
	for(int x = 0; x < w; x++){
		double xv = sx.x + x*sc_fx;
		for(int y = 0; y < h; y++){
			double yv = sy.y - y*sc_fy;
			cx cm(xv, yv);
			int et = iterate(cm, iterations);
			fillpix(vec2(x, y), et);
		}
	}
}

sf::Image getimg(){
	return c_img;
}

