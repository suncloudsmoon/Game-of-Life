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

#ifndef COORDUTIL_HPP
#define COORDUTIL_HPP

#include <cmath>

namespace gol {
	// Entity Utility Functions
	template<class T, class O, class B>
	static T toBlockyCoordX(T coordX, O xOffset, B blockSize) {
		return static_cast<T>(std::floor((coordX - xOffset) / blockSize));
	}

	template<class T, class O, class B>
	static T toBlockyCoordY(T coordY, O yOffset, B blockSize) {
		return static_cast<T>(std::floor((coordY - yOffset) / blockSize));
	}

	template<class T, class O, class B>
	static B toNormalCoordX(T gridX, O xOffset, B blockSize) {
		return static_cast<B>(gridX * blockSize) + xOffset;
	}

	template<class T, class O, class B>
	static B toNormalCoordY(T gridY, O yOffset, B blockSize) {
		return static_cast<B>(gridY * blockSize) + yOffset;
	}
}

#endif /* COORDUTIL_HPP */