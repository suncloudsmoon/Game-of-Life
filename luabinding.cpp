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

#include <LUA/lua.hpp>

#include "debugmode.hpp"
#include "luabinding.hpp"
#include "entitymanager.hpp"

namespace gol {
	static std::shared_ptr<EntityManager>* entityManager;
	void luabinding_init(std::shared_ptr<EntityManager>* manager) {
		entityManager = manager;
	}
	void luabinding_close() {
		entityManager = nullptr;
	}

	int luabinding_getrows(lua_State* L) {
		double result = static_cast<double>((*entityManager)->getGrid()->getWidth());
		lua_pushnumber(L, result);
		return 1;
	}

	int luabinding_getcolumns(lua_State* L) {
		double result = static_cast<double>((*entityManager)->getGrid()->getHeight());
		lua_pushnumber(L, result);
		return 1;
	}

	int luabinding_getEntityStateAt(lua_State* L) {
		double arg1 = lua_tonumber(L, 1);
		double arg2 = lua_tonumber(L, 2);

		bool state = (*entityManager)->getGrid()->at(arg1, arg2)->isWhite();
		lua_pushboolean(L, state);
		return 1;
	}

	int luabinding_setEntityStateAt(lua_State* L) {
		double arg1 = lua_tonumber(L, 1);
		double arg2 = lua_tonumber(L, 2);
		bool arg3 = static_cast<bool>(lua_toboolean(L, 3));

		(*entityManager)->getGrid()->at(arg1, arg2)->changeColor(arg3);
		return 0; // pushing zero args
	}
}
