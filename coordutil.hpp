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