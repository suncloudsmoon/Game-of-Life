/*
 * Copyright (c) 2021, suncloudsmoon and the Game-of-Life contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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