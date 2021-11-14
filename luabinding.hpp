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

#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <memory>

#include <LUA/lua.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"

namespace gol {
	void luabinding_init(std::shared_ptr<EntityManager>* manager);
	void luabinding_close();

	// Getters
	int luabinding_getrows(lua_State* L);
	int luabinding_getcolumns(lua_State* L);
	int luabinding_getGenerationCount(lua_State* L);
	int luabinding_getPopulationCount(lua_State* L);
	int luabinding_getEntityStateAt(lua_State* L);

	// Setters
	int luabinding_setEntityStateAt(lua_State* L);
}

#endif /* LUABINDING_HPP */