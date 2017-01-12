//
// Created by Yunpeng Xu on 1/12/17.
//

#ifndef CS11_TSP_GA_H
#define CS11_TSP_GA_H

#include <vector>
#include "Point.hh"

class TSPGenome {
private:
	std::vector<int> order; //the points in the problem will be visited
	double circuit_length;  //the total distance covered if the points are visited in a circuit
	void swap(std::vector<int> &order, int i, int j) const;

public:
	// Constructors
	TSPGenome();                //default constructor
	TSPGenome(int numPoints);   //takes the number of points that will be visited, and
								// generates a random order to visit those points.
	TSPGenome(const std::vector<int> &other);    //initializes the genome from the specified visit order.
	
	// Destructor
	~TSPGenome();
	
	// Mutator methods
	//computes the circuit length from traversing the points in the order specified in the object
	void computeCircuitLength(const std::vector<Point> &points);
	//mutates the genome by swapping two randomly-selected values in the order vector
	void mutate();
	
	// Accessor methods
	std::vector<int> getOrder() const;      // returns the genome's current visit order.
	double getCircuitLength() const;          // returns the circuit length
};

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations);


#endif //CS11_TSP_GA_H
