#ifndef _D_ITER_H
#define _D_ITER_H

#include <SFML/Graphics/Image.hpp>
#include "vec.h"

void paint(vec2 sx, vec2 sy, int w, int h, double ang);
sf::Image getimg();
void iter_init();
void set_itrn(int n);

#endif
