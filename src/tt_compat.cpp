#include <cstdint>
#include <lua.hpp>
#include <lauxlib.h>
#include <module.h>
#include "tt_compat.h"

static constexpr int64_t TT_INT64_THRESHOLD = INT64_C(100000000000000);

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

void tt_lua_pushinteger64(lua_State *L, int64_t val) {
  if (val >= TT_INT64_THRESHOLD || val <= -TT_INT64_THRESHOLD) {
    luaL_pushint64(L, val);
  } else {
    lua_pushnumber(L, static_cast<lua_Number>(val));
  }
}

void tt_lua_pushuint64(lua_State *L, uint64_t val) {
  if (val > static_cast<uint64_t>(INT64_MAX) || val >= static_cast<uint64_t>(TT_INT64_THRESHOLD)) {
    luaL_pushuint64(L, val);
  } else {
    lua_pushnumber(L, static_cast<lua_Number>(val));
  }
}

