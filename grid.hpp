#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <stdexcept>

#include "debugmode.hpp"

template<class T>
class Grid {
public:
	Grid(size_t width, size_t height) : arrWidth(width), arrHeight(height) {
		arr.resize(width * height);
	}

	template<class A>
	T& at(A row, A col) {
		// Range checking
		if (static_cast<size_t>(row) >= arrWidth) {
			throw std::out_of_range("Grid row is greather than or equal to array width!");
		}
		else if (static_cast<size_t>(col) >= arrHeight) {
			throw std::out_of_range("Grid column is greater than or equal to array height!");
		}
		return arr[(static_cast<size_t>(row) * arrHeight) + static_cast<size_t>(col)];
	}

	template<class A>
	T& operator()(A row, A col) {
		return at(row, col);
	}

	std::vector<T>& getRawArr() {
		return arr;
	}

	size_t getWidth() {
		return arrWidth;
	}

	size_t getHeight() {
		return arrHeight;
	}
private:
	size_t arrWidth, arrHeight;
	std::vector<T> arr;
};

#endif /* GRID_HPP */