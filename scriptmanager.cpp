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

#include <memory>
#include <functional>
#include <vector>
#include <fstream>

#include "debugmode.hpp"
#include "scriptmanager.hpp"
#include "entitymanager.hpp"
#include "luabinding.hpp"

namespace gol {
	ScriptManager::ScriptManager(const std::shared_ptr<EntityManager>& manager) : entityManager(manager) {
		luabinding_init(&entityManager);
	}

	ScriptManager::~ScriptManager() {
		luabinding_close();
	}

	bool ScriptManager::loadScriptList(const std::string& scriptTxtPath) {
		std::ifstream input(scriptTxtPath);
		if (input.is_open()) {
			std::string line;
			while (std::getline(input, line)) {
				if (!line.empty())
					addScript(line);
			}
			return true;
		}
		else {
			return false;
		}
	}

	bool ScriptManager::writeScriptList(const std::string& scriptTxtPath) {
		std::ofstream output(scriptTxtPath);
		if (output.is_open()) {
			output << std::endl;
			return true;
		}
		else {
			return false;
		}
	}

	void ScriptManager::addScript(const std::string& scriptPath) {
		scriptList.push_back(std::make_unique<LuaScript>(scriptPath));
		auto* L = scriptList.back()->getRawState();
		luaL_openlibs(L); // Open all the standard library functions

		// Bind C Functions
		lua_register(L, "GetEntityStateAt", luabinding_getEntityStateAt);
		lua_register(L, "SetEntityStateAt", luabinding_setEntityStateAt);
	}

	int ScriptManager::executeLuaFunction(const std::string& functName, const std::function<int(lua_State*)>& job,
		const std::function<void(lua_State*, int&)>& success) {
		int code = false;
		for (auto& script : scriptList) {
			auto* L = script->getRawState();
			lua_getglobal(L, functName.c_str());
			if (lua_isfunction(L, -1)) {
				if (job(L) != LUA_OK) {
					throw LuaError(script->getPath() + ": P-Call Error - " + std::string(lua_tostring(L, -1)) + "!");
				}
				else {
					success(L, code);
				}
			}
			else {
				throw LuaError(script->getPath() + ": Unable to call lua function for " + functName + "!");
			}
		}
		return code;
	}

	// NOTE: DO NOT USE lua_iscfunction()
	void ScriptManager::executeStartFunction(const std::string& functName) {
		auto job = [&](lua_State* L) {
			return lua_pcall(L, 0, 0, 0);
		};
		auto success = [&](lua_State* L, int &code) {
			return code;
		};
		executeLuaFunction(functName, job, success);
	}

	void ScriptManager::executeButtonPressedFunction(const std::string& functName, bool state) {
		auto job = [=](lua_State* L) {
			lua_pushboolean(L, state);
			return lua_pcall(L, 1, 0, 0);
		};
		auto success = [&](lua_State* L, int& code) {
			return code;
		};
		executeLuaFunction(functName, job, success);
	}

	bool ScriptManager::executeMousePressedFunction(const std::string& functName, double x, double y) {
		auto job = [=](lua_State* L) {
			lua_pushnumber(L, x);
			lua_pushnumber(L, y);
			return lua_pcall(L, 2, 1, 0);
		};
		auto success = [&](lua_State* L, int& code) {
			return code = code || lua_toboolean(L, -1);
		};
		return executeLuaFunction(functName, job, success);
	}
}

