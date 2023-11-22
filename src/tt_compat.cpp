#include <lua.hpp>
#include <lauxlib.h>
#include <string>
#include "tt_compat.h"

char* SER_MARKER_MAP = (char*)"map";
char* SER_MARKER_SEQ = (char*)"seq";

// Variable is needed to avoid collisions in LUA_REGISTRY.
static const char TT_NULL_ADDR = 't';

/* Mimics tarantool's cjson NULL, catches and sets it as global variable for future usage.
 * Internally it loads json library, then extracts the "null" value from it and stores it in a registry.
*/
static void tt_lua_createnull(lua_State *L) {
    luaL_register(L, "json", 0);
    lua_pushlightuserdata(L, (void *)&TT_NULL_ADDR);
    lua_getfield(L, -2, "null");
    lua_settable(L, LUA_REGISTRYINDEX);
}

void tt_lua_pushnull(lua_State *L) {
  lua_pushlightuserdata(L, (void *)&TT_NULL_ADDR);
  lua_gettable(L, LUA_REGISTRYINDEX);
}

void tt_compat_init(lua_State *L) {
  tt_lua_createnull(L);
}

void tt_lua_push_serialize_mt(lua_State *L, char* marker) {
  lua_createtable(L, 0, 1);
  lua_pushstring(L, "__serialize");
  lua_pushstring(L, marker);
  lua_settable(L, -3);
}
