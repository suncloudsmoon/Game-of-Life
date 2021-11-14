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

#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <functional>

#include <LUA/lua.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"

namespace gol {
	class LuaError : public std::runtime_error {
	public:
		LuaError(const std::string& errMessage) : std::runtime_error(errMessage) {}
	};

	class LuaScript {
	public:
		LuaScript(const std::string& scriptPath) : path(scriptPath) {
			state = luaL_newstate();
			if (state == nullptr) {
				throw std::bad_alloc();
			}
			if (luaL_dofile(state, scriptPath.c_str()) != LUA_OK) {
				throw LuaError("Unable to load file: " + scriptPath + "!");
			}
		}
		~LuaScript() {
			lua_close(state);
			state = nullptr;
		}
		LuaScript(const LuaScript& script) = delete;

		lua_State* getRawState() {
			return state;
		}
		const std::string& getPath() const {
			return path;
		}
	private:
		std::string path;
		lua_State* state;
	};

	class ScriptManager {
	public:
		ScriptManager(const std::shared_ptr<EntityManager>& manager);
		~ScriptManager();

		bool loadScriptList(const std::string &scriptTxtPath);
		bool writeScriptList(const std::string& scriptTxtPath);

		void addScript(const std::string& scriptPath);

		int executeLuaFunction(const std::string& functName, const std::function<int(lua_State*)>& job,
			const std::function<void(lua_State*, int&)>& success);
		void executeStartFunction(const std::string& functName);
		void executeButtonPressedFunction(const std::string& functName, bool state);

		bool executeMousePressedFunction(const std::string& functName, double x, double y);
	private:
		std::shared_ptr<EntityManager> entityManager;
		std::vector<std::unique_ptr<LuaScript>> scriptList;
	};
}

#endif /* SCRIPTMANAGER_HPP */