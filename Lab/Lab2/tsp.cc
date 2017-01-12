//
// Created by Yunpeng Xu on 1/11/17.
//

using namespace std;
#include <iostream>
#include <vector>
#include <cfloat>
#include "Point.hh"

double circuitLength(const vector<Point> &points, const vector<int> &order) {
	double len = 0.0;
	if (order.size() < 2) return len;
	for (int i = 1; i < order.size(); i++) {
		len += points[order[i-1]].distanceTo(points[order[i]]);
	}
	len += points[order[order.size() - 1]].distanceTo(points[order[0]]);
	return len;
}

vector<int> findShortestPath(const vector<Point> &points) {
	int N = points.size();
	vector<int> vec;
	vector<int> res;
	for (int i = 0; i < N; i++) {
		vec.push_back(i);
	}
	
	double shortest = DBL_MAX;
	do {
		double tmp = circuitLength(points, vec);
		if (tmp < shortest) {
			shortest = tmp;
			res = vector<int>(vec.begin(), vec.end());
		}
	} while (next_permutation(vec.begin(), vec.end()));
	return res;
}



int main() {
	int n;
	double x, y, z;
	vector<Point> points;
	cout << "Please enter the number of points [2 ~ ]" << endl;
	cin >> n;
	cout << "Please enter the " << n << " points with x y z" << endl;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> z;
		points.push_back(Point(x, y, z));
	}
	
	vector<int> res = findShortestPath(points);
	cout << "Best order: [ ";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << "]" << endl;
	cout << "Shortest distance: " << circuitLength(points, res) << endl;
	return 0;
}