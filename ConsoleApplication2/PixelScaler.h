#pragma once
#ifndef PIXELSCALER_H
#define PIXELSCALER_H

#include <SFML\Graphics.hpp>
#include <math.h>

template <int T>
class PixelScaler: public sf::Drawable{
	//square 'pixel' side length, there will then be a table of 4^m_size that are mapped to transformations.
	int m_size = T;
	int m_scale;
	std::array<int, pow(4.f, (float)T)> pixelArray = { 0 };
	sf::RectangleShape m_blackSquare, m_graySquare, m_whiteSquare;

public:
	PixelScaler(int, int);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // !PIXELSCALER_H