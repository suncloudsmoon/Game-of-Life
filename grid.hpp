#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "debugmode.hpp"

template<class T>
class Grid {
public:
	Grid(unsigned int width, unsigned int height) : arrWidth(width), arrHeight(height) {
		arr.resize(width * height);
	}

	T& at(unsigned int row, unsigned int col) {
		// Range checking
		if (row >= arrWidth) {
			throw std::runtime_error("Grid row is greather than or equal to array width!");
		}
		else if (col >= arrHeight) {
			throw std::runtime_error("Grid column is greater than or equal to array height!");
		}
		return arr[(row * arrHeight) + col];
	}

	T& operator()(unsigned int row, unsigned int col) {
		return at(row, col);
	}

	std::vector<T>& getRawArr() {
		return arr;
	}
private:
	unsigned int arrWidth, arrHeight;
	std::vector<T> arr;
};

#endif /* GRID_HPP */