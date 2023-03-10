#include "Wektor.h"

Wektor::Wektor(double _x = 0.0, double _y = 0.0) : x(_x), y(_y)
{
}

Wektor::Wektor()
{
	x = 0.0;
	y = 0.0;
}

Wektor::~Wektor()
{
}

double Wektor::operator*(Wektor const& w)
{
	return (x * w.x + y * w.y);
}

Wektor Wektor::operator*(double liczba)
{
	return Wektor(x * liczba, y * liczba);
}

Wektor operator*(double s, Wektor const& w)
{
	return Wektor(s * w.x, s * w.y);
}

Wektor Wektor::operator+(Wektor const& w)
{
	return Wektor(x + w.x, y + w.y);
}

Wektor Wektor::operator-(Wektor const& w)
{
	return Wektor(x - w.x, y - w.y);
}

