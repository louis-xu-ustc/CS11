//
// Created by Yunpeng Xu on 1/12/17.
//

#include <cassert>
#include <cstdlib>
#include <set>
#include <iostream>
#include "tsp-ga.h"

//default constructor
TSPGenome::TSPGenome() {
	circuit_length = 0;
}

//takes the number of points that will be visited, and generates a random order to visit those points.
TSPGenome::TSPGenome(int numPoints) {
	assert(numPoints >= 2);
	for (int i = 0; i < numPoints; i++) {
		order.push_back(i);
	}
	std::random_shuffle(order.begin(), order.end());
}

//initializes the genome from the specified visit order
TSPGenome::TSPGenome(const std::vector<int> &other) {
	assert(other.size() >= 2);
	for (int i = 0; i < other.size(); i++) {
		order.push_back(other[i]);
	}
}

// Destructor - TSPGenome allocates no dynamic resources.
TSPGenome::~TSPGenome() {
	// no-op
}

//computes the circuit length from traversing the points in the order specified in the object, and
// store the value in the object
void TSPGenome::computeCircuitLength(const std::vector<Point> &points) {
	double len = 0.0;
	int N = order.size();
	for (int i = 1; i < N; i++) {
		len += points[order[i-1]].distanceTo(points[order[i]]);
	}
	len += points[order[N - 1]].distanceTo(points[order[0]]);
	circuit_length = len;
}

//returns the genome's current visit order.
std::vector<int> TSPGenome::getOrder() const {
	return order;
}

//returns the circuit length
double TSPGenome::getCircuitLength() const {
	return circuit_length;
}

void TSPGenome::swap(std::vector<int> &order, int i, int j) const {
	int tmp = order[i];
	order[i] = order[j];
	order[j] = tmp;
}

//mutates the genome by swapping two randomly-selected values in the order vector
void TSPGenome::mutate() {
	int rand1 = rand() % order.size();
	int rand2;
	
	do {
		rand2 = rand() % order.size();
	} while (rand1 == rand2);
	swap(order, rand1, rand2);
}

//generate offspring
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
	std::vector<int> new_order;
	std::set<int> s;
	int index = rand() % g1.getOrder().size();
	for (int i = 0; i < index; i++) {
		int tmp = g1.getOrder()[i];
		new_order.push_back(tmp);
		s.insert(tmp);
	}
	for (int i = 0; i < g2.getOrder().size(); i++) {
		int tmp = g2.getOrder()[i];
		if (s.count(tmp) != 0) {
			continue;
		}
		new_order.push_back(tmp);
		s.insert(tmp);
	}
	TSPGenome tspGenome = TSPGenome(new_order);
	return tspGenome;
}

//return true if g1 has a shorter circuit length than g2; false otherwise.
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2) {
	return g1.getCircuitLength() < g2.getCircuitLength();
}

//find a shorter path
TSPGenome findAShortPath(const std::vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations) {
	
	std::vector<TSPGenome> genomes;
	for (int i = 0; i < populationSize; i++) {
		genomes.push_back(TSPGenome(points.size()));
	}
	
	for (int gen = 0; gen < numGenerations; gen++) {
		for (int i = 0; i < populationSize; i++) {
			genomes[i].computeCircuitLength(points);
		}
		std::sort(genomes.begin(), genomes.end(), isShorterPath);
		// prints out the fitness of the best solution
		if (gen % 10 == 0) {
			std::cout << "Generation " << gen << ":  shortest path is "
			     << genomes[0].getCircuitLength() << std::endl;
		}
		
		// keep the top N fittest members of the population,
		// but replace the remaining members with new genomes produced from the fittest ones
		assert(keepPopulation < populationSize);
		for (int i = keepPopulation; i < populationSize; i++) {
			int rand1 = rand() % keepPopulation;
			int rand2;
			do {
				rand2 = rand() % keepPopulation;
			} while (rand1 == rand2);
			genomes[i] = crosslink(genomes[rand1], genomes[rand2]);
		}
		
		for (int i = 0; i < numMutations; i++) {
			int index = 1 + rand() % (populationSize - 1);
			genomes[index].mutate();
		}
	}
	return genomes[0];
}

