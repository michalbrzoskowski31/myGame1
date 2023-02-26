#pragma once

#include <cmath>


class Wektor
{
public:
	double x, y;

	Wektor(double _x, double _y);
	Wektor();
	~Wektor();

	double operator*(Wektor const& w);
	Wektor operator*(double liczba);
	Wektor operator+(Wektor const& w);
	Wektor operator-(Wektor const& w);
	//Wektor operator%(Wektor const& w);


	double length();
	void normalize();
};

Wektor operator*(double s, Wektor const& w);

