//
// Created by Yunpeng Xu on 1/12/17.
//

#include "tsp-ga.h"
#include <iostream>

int main() {
	int population = 1000;
	int generations = 100;
	float keep = 0.4;
	float mutate = 1.0;
	
	int n;
	double x, y, z;
	std::vector<Point> points;
	std::cout << "Please enter the number of points [2 ~ ]" << std::endl;
	std::cin >> n;
	std::cout << "Please enter the " << n << " points with x y z" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cin >> x >> y >> z;
		points.push_back(Point(x, y, z));
	}
	
	TSPGenome tspGenome = findAShortPath(points, population, generations,
	                                     (int)(keep * population), (int)(mutate * population));
	std::cout << "size: " << tspGenome.getOrder().size() << std::endl;
	std::cout << "Best order: [ ";
	for (int i = 0; i < tspGenome.getOrder().size(); i++) {
		std::cout << tspGenome.getOrder()[i] << " ";
	}
	std::cout << "]" << std::endl;
	std::cout << "Shortest distance: " << tspGenome.getCircuitLength() << std::endl;
	return 0;
}
