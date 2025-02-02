#include <lua.hpp>
#include <lauxlib.h>
#include "tt_compat.h"

char* SER_MARKER_MAP = (char*)"map";
char* SER_MARKER_SEQ = (char*)"seq";

const char TT_NULL_ADDR = 'T';

/* Mimics tarantool's cjson NULL, catches and sets it as global variable for future usage.
 * Internally it loads json library, then extracts the "null" value from it and stores it in a registry.
*/
static void tt_lua_createnull(lua_State *L) {
    luaL_register(L, "json", 0);
    lua_pushlightuserdata(L, (void *)&TT_NULL_ADDR);
    lua_getfield(L, -2, "null");
    lua_settable(L, LUA_REGISTRYINDEX);
}

void tt_compat_init(lua_State *L) {
  tt_lua_createnull(L);
}

