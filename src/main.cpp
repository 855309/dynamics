#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "log.h"
#include "vec.h"
#include "cx.h"
#include "color.h"
#include "iter.h"

int WIDTH = 640;
int HEIGHT = 360;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "dynamics");

vec2 sx(-2, 2);
vec2 sy = (sx / WIDTH) * HEIGHT;

double arrw_drft_x = 10;
double arrw_drft_y = (10/((double)WIDTH))*(double)HEIGHT;
double zoom_f = 1.05;
bool guide_v = true;
double guide_wd = 1;
double ang = 0;
int main(int argc, char** argv){
	if(argc > 1){
		std::stringstream sts;
		sts << argv[1];
		int tn = 1;
		sts >> tn;
		set_itrn(tn);
	}

	vec2 s_chg;
	double s_scl = 1;
	
	// guide lines
	sf::RectangleShape gv, gh;
	gv.setSize(sf::Vector2f(WIDTH, guide_wd));
	gv.setPosition(0, HEIGHT/2 - guide_wd/2);
	gh.setSize(sf::Vector2f(guide_wd, HEIGHT));
	gh.setPosition(WIDTH/2 - guide_wd/2, 0);
	sf::Color gdc = sf::Color(255, 255, 255, 50);
	gv.setFillColor(gdc);
	gh.setFillColor(gdc);
	// --
	
	paint(sx, sy, WIDTH, HEIGHT, ang);
	
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::I){
					s_chg = 0;
					s_scl = 1;
					paint(sx, sy, WIDTH, HEIGHT, ang);
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
					vec2 cnt((sx.y + sx.x)/2, (sy.y + sy.x)/2);
					sx = (sx - cnt.x)/zoom_f + cnt.x;
					sy = (sy - cnt.y)/zoom_f + cnt.y;
					
					s_scl *= zoom_f;
					
					/*double dx = ((double)WIDTH)*(zoom_f - 1)/2;
					s_chg.x -= dx;
					
					double dy = ((double)HEIGHT)*(zoom_f - 1)/2;
					s_chg.y -= dy;*/
				}
				if(event.key.code == sf::Keyboard::X){
					vec2 cnt((sx.y + sx.x)/2, (sy.y + sy.x)/2);
					sx = (sx - cnt.x)*zoom_f + cnt.x;
					sy = (sy - cnt.y)*zoom_f + cnt.y;
					
					s_scl /= zoom_f;
					
					/*double dx = ((double)WIDTH)*(zoom_f - 1)/2;
					s_chg.x += dx;
					
					double dy = ((double)HEIGHT)*(zoom_f - 1)/2;
					s_chg.y += dy;*/
				}
				if(event.key.code == sf::Keyboard::G){
					guide_v = !guide_v;
				}
				
				if(event.key.code == sf::Keyboard::S){
					//guide_v = !guide_v;
					ang += M_PI/(double)12;
					ins_lf(0);
					clog("Ang:");
					clog(ang/M_PI, false);
					clog("pi rad.");
					clnl();
				}
				
				if(guide_v){
					cx centerp((sx.y + sx.x)/2, (sy.y + sy.x)/2);
					ins_lf(0);
					clog("Center:");
					clog(centerp);
					clnl();
				}
			}
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}
		
		window.clear(sf::Color::Black);
		
		sf::Texture txt;
		txt.loadFromImage(getimg());
		
		sf::Sprite bgs;
		bgs.setTexture(txt, true);
		bgs.setOrigin((double)WIDTH/2, (double)HEIGHT/2);
		bgs.setPosition((double)WIDTH/2, (double)HEIGHT/2);
		bgs.move(s_chg.x, s_chg.y);
		bgs.setScale(s_scl, s_scl);
		
		window.draw(bgs);

		if(guide_v){
			window.draw(gv);
			window.draw(gh);
		}
		
		
		window.display();
	}
	
	return 0;
}
