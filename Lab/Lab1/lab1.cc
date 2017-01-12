//
// Created by Yunpeng Xu on 1/11/17.
//
#include "Point.hh"
#include <cmath>
#include <iostream>


double computeArea(Point &a, Point &b, Point &c) {
	double dist_ab = a.distanceTo(b);
	double dist_ac = a.distanceTo(c);
	double dist_bc = b.distanceTo(c);
	
	double s = (dist_ab + dist_ac + dist_bc) / 2;
	return sqrt(s * (s - dist_ab) * (s - dist_ac) * (s - dist_bc));
}

int main() {
	double x, y, z;
	std::cout << "Please enter three points with format <x y z>" << std::endl;
	std::cin >> x >> y >> z;
	Point a = Point(x, y, z);
	std::cin >> x >> y >> z;
	Point b = Point(x, y, z);
	std::cin >> x >> y >> z;
	Point c = Point(x, y, z);
	std::cout << "Point 1: <" << a.getX() << " " << a.getY() << " " << a.getZ() << ">" << std::endl
	          << "Point 2: <" << b.getX() << " " << b.getY() << " " << b.getZ() << ">" << std::endl
	          << "Point 3: <" << c.getX() << " " << c.getY() << " " << c.getZ() << ">" << std::endl
	          << "Area is: <" << computeArea(a, b, c) << ">" << std::endl;
	return 0;
}