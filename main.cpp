#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int WIDTH = 640;
int HEIGHT = 360;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "dynamics");
sf::Image c_img;

// logging
std::string cds[] = {"INF", "ERR"};
void cns_log() {
    std::cout << std::endl;
}

template<typename F, typename ... T>
void cns_log(F frs, const T&... rst) {
    std::cout << frs << " ";
    cns_log(rst...);
}

template<typename ... T>
void clog(int s, const T&... rst){
	std::cout << "[" << cds[s] << "] ";
	cns_log(rst...);
}
// logging end

class pixel{
public:
	int x, y;
	sf::Color col;
	
	pixel(int _x, int _y, sf::Color _col){
		this->x = _x;
		this->y = _y;
		this->col = _col;
	}
};

class vec2{
public:
	double x, y;
	vec2(){
		this->x = 0;
		this->y = 0;	
	}
	
	vec2(double _x, double _y){
		this->x = _x;
		this->y = _y;
	}
	
	vec2(double f){
		this->x = f;
		this->y = f;
	}
	
	vec2 operator+(vec2 const& rhs){
		return vec2(this->x + rhs.x, this->y + rhs.y);
	}
	vec2 operator-(vec2 const& rhs){
		return vec2(this->x - rhs.x, this->y - rhs.y);
	}
	vec2 operator*(vec2 const& rhs){
		return vec2(this->x * rhs.x, this->y * rhs.y);
	}
	vec2 operator/(vec2 const& rhs){
		return vec2(this->x / rhs.x, this->y / rhs.y);
	}
};

class vec3{
public:
	double x, y, z;
	vec3(double _x, double _y, double _z){
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}
	
	vec3(double f){
		this->x = f;
		this->y = f;
		this->z = f;
	}
	
	vec3 operator+(vec3 const& rhs){
		return vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}
};

class cx{
public:
	double re, im;
	
	cx(){
		this->re = 0;
		this->im = 0;
	}
	
	cx(double _re, double _im){
		this->re = _re;
		this->im = _im;
	}
	
	cx(double _re){
		this->re = _re;
		this->im = 0;
	}
	
	double rad(){
		return sqrt(this->re*this->re + this->im*this->im);
	}
	
	cx operator+(cx const& rhs){
		return cx(this->re + rhs.re, this->im + rhs.im);
	}
	
	cx operator-(cx const& rhs){
		return cx(this->re - rhs.re, this->im - rhs.im);
	}
	
	cx operator*(cx const& rhs){
		return cx(this->re*rhs.re - this->im*rhs.im, this->re*rhs.im + this->im*rhs.re);
	}
	
	cx operator/(cx const& rhs){
		double k = rhs.re*rhs.re + rhs.im*rhs.im;
		return cx((this->re*rhs.re + this->im*rhs.im)/k, (this->re*rhs.im - this->im*rhs.re)/k);
	}
	
	cx maxr(cx n){
		if(this->rad() > n.rad()){
			return *this;
		}
		return n;
	}
	
	std::string str(){
		std::stringstream ss;
		ss << this->re;
		
		if(this->im < 0){
			ss << " - " << -this->im;
		} 
		else{
			ss << " + " << this->im;
		}
		
		ss << "i";
		return ss.str();
	}
};

int esc_rds = 2;
cx func(cx cm, cx cns){
	return cm*cm + cns;
}

// cx maxtp;
int iterate(cx cm, int num){
	cx res;
	if(cm.rad() > esc_rds) return 0;
	
	for(int i = 1; i <= num; i++){
		res = func(res, cm);
		if(res.rad() > esc_rds){
			return i;
		}
	}
	
	return num;
}

double smoothsq(double x, double dlt){
	return sin(x) / sqrt(dlt*dlt + sin(x)*sin(x));
}

double fr_ml = 1;
vec3 colfunc(double t, double maxt, double dlt){
	// y: (1/2) * (1 + smoothsq((3*M_PI/maxt) * (t - M_PI/4)))
	// z: (1/2) * (1 - smoothsq(M_PI/2 - (3*M_PI/maxt) * (t - M_PI/4)))
	return vec3((double)t/(double)maxt, 0.5 * (1 + smoothsq((2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)), 0.5 * (1 - smoothsq(M_PI/2 - (2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)));
}

int iterations = 100;
double delta = 0.00001;
void fillpix(vec2 pos, int et){
	vec3 col = colfunc(iterations - et, iterations, delta);
	sf::Color cl(255 * col.x, 255 * col.y, 255 * col.z);
	c_img.setPixel(pos.x, pos.y, cl);
}

vec2 sx(-2, 2);
vec2 sy = (sx / WIDTH) * HEIGHT;
void paint(){
	clog(0, "Started iteration:", iterations, "iterations.");
	c_img.create(WIDTH, HEIGHT, sf::Color::White);
	double sc_fx = (sx.y - sx.x)/((double)WIDTH);
	double sc_fy = (sy.y - sy.x)/((double)HEIGHT);
	for(int x = 0; x < WIDTH; x++){
		double xv = sx.x + x*sc_fx;
		for(int y = 0; y < HEIGHT; y++){
			double yv = sy.y - y*sc_fy;
			cx cm(xv, yv);
			int et = iterate(cm, iterations);
			fillpix(vec2(x, y), et);
		}
	}
	
	// clog(0, maxtp.str());
}

double arrw_drft_x = 10;
double arrw_drft_y = (10/((double)WIDTH))*(double)HEIGHT;
double zoom_f = 1.05;
int main(int argc, char** argv){
	/*vec3 rn = colfunc(0, iterations, delta);
	clog(0, rn.x, rn.y, rn.z);
	return 0;*/
	c_img.create(WIDTH, HEIGHT, sf::Color::Black);
	bool rp, lp, up, dp = false;
	vec2 s_chg;
	double s_scl = 1;
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::I){
					s_chg = 0;
					s_scl = 1;
					paint();
				}
				if(event.key.code == sf::Keyboard::Right){
					double sc_fx = (sx.y - sx.x)/((double)WIDTH);
					double dx = arrw_drft_x;
					sx = sx + dx*sc_fx;
					s_chg.x -= dx;
				}
				if(event.key.code == sf::Keyboard::Left){
					double sc_fx = (sx.y - sx.x)/((double)WIDTH);
					double dx = arrw_drft_x;
					sx = sx - dx*sc_fx;
					s_chg.x += dx;
				}
				if(event.key.code == sf::Keyboard::Up){
					double sc_fy = (sy.y - sy.x)/((double)HEIGHT);
					double dy = arrw_drft_y;
					sy = sy + dy*sc_fy;
					s_chg.y += dy;
				}
				if(event.key.code == sf::Keyboard::Down){
					double sc_fy = (sy.y - sy.x)/((double)HEIGHT);
					double dy = arrw_drft_y;
					sy = sy - dy*sc_fy;
					s_chg.y -= dy;
				}
				if(event.key.code == sf::Keyboard::Z){
					sx = sx/zoom_f;
					sy = sy/zoom_f;
					
					s_scl *= zoom_f;
					
					/*double dx = ((double)WIDTH)*(zoom_f - 1)/2;
					s_chg.x -= dx;
					
					double dy = ((double)HEIGHT)*(zoom_f - 1)/2;
					s_chg.y -= dy;*/
				}
				if(event.key.code == sf::Keyboard::X){
					sx = sx*zoom_f;
					sy = sy*zoom_f;
					
					s_scl /= zoom_f;
					
					/*double dx = ((double)WIDTH)*(zoom_f - 1)/2;
					s_chg.x += dx;
					
					double dy = ((double)HEIGHT)*(zoom_f - 1)/2;
					s_chg.y += dy;*/
				}
			}
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}
		
		window.clear(sf::Color::Black);
		
		sf::Texture txt;
		txt.loadFromImage(c_img);
		
		sf::Sprite bgs;
		bgs.setTexture(txt, true);
		bgs.setOrigin((double)WIDTH/2, (double)HEIGHT/2);
		bgs.setPosition((double)WIDTH/2, (double)HEIGHT/2);
		bgs.move(s_chg.x, s_chg.y);
		bgs.setScale(s_scl, s_scl);
		
		window.draw(bgs);
		
		window.display();
	}
	
	return 0;
}
