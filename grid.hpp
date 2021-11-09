#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "debugmode.hpp"

template<class T>
class Grid {
public:
	Grid(size_t width, size_t height) : arrWidth(width), arrHeight(height) {
		arr.resize(width * height);
	}

	T& at(size_t row, size_t col) {
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
	size_t arrWidth, arrHeight;
	std::vector<T> arr;
};

#endif /* GRID_HPP */