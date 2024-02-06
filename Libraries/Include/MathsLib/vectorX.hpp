#pragma once

#include <iostream>
#include <vector>

class VectorX
{
public:
	VectorX();
	~VectorX();
	VectorX(int fsize);


	//variables 
	int size;		// size of the vector (mathematical vector)

	std::vector<float> float_X;

	// functions
	void print() const;
	void print(std::string name) const;

	// vector related functions
	static VectorX normalize(VectorX a);
	static float length(VectorX a);
	static float lengthSq(VectorX a);	// only used to compare for optimization
	static float dist(VectorX a, VectorX b);
	static float dot(VectorX a, VectorX b);
	static VectorX cross(VectorX a, VectorX b);
};

VectorX operator+(VectorX a, float n);
VectorX operator-(VectorX a, float n);
VectorX operator*(VectorX a, float s);
VectorX operator/(VectorX a, float s);
VectorX operator+(VectorX a, VectorX b);
VectorX operator-(VectorX a, VectorX b);

std::ostream& operator<<(std::ostream& os, const VectorX& VectorX);

#include "vectorX.inl"