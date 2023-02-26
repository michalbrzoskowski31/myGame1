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

//Wektor Wektor::operator%(Wektor const& w)
//{
//	return Wektor(y * w.z - z * w.y, z * w.x - x * w.z, x * w.y - y * w.x);
//}

double Wektor::length()
{
	return sqrt((*this) * (*this));
}

void Wektor::normalize()
{
	double d = this->length();
	if (d)
		(*this) = (*this) * (1 / d);
}


