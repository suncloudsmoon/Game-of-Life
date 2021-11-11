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

#include <string>
#include <cstdlib>
#include <stdexcept>

#include "debugmode.hpp"
#include "errorbox.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

static void convert_char_wchar_ptr(wchar_t* dest, const char* str, size_t len);

namespace util {
#ifdef _WIN32
	void displayErrorBox(const std::string& title, const std::string& message) {
		wchar_t* wideTitlePtr = (wchar_t*)std::calloc(title.size() + 1, sizeof(wchar_t));
		wchar_t* wideMessagePtr = (wchar_t*)std::calloc(message.size() + 1, sizeof(wchar_t));

		convert_char_wchar_ptr(wideTitlePtr, title.c_str(), title.size() + 1);
		convert_char_wchar_ptr(wideMessagePtr, message.c_str(), message.size() + 1);

		MessageBox(nullptr, (LPCWSTR)wideMessagePtr, (LPCWSTR)wideTitlePtr, MB_ICONERROR);

		std::free(wideTitlePtr);
		std::free(wideMessagePtr);
	}
#else
	void displayErrorBox(const std::string& title, const std::string& message) {
		// Do nothing...
	}
#endif
}

static void convert_char_wchar_ptr(wchar_t* dest, const char* str, size_t len) {
	if (std::mbstowcs(dest, str, len) == static_cast<size_t>(-1)) {
		throw std::runtime_error("Unable to convert const char pointer to wide char pointer!");
	}
}
