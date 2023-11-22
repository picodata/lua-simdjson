#include <lua.hpp>
#include <lauxlib.h>

/* Initializes needed consts for future work.
 * Intended to be called on the Lua module init.
 */
void tt_compat_init(lua_State *L);


/* Pushes tarantool's null onto the stack.
 * It requires `tt_lua_init` to be called first.
 */
void tt_lua_pushnull(lua_State *L);

extern char* SER_MARKER_SEQ;
extern char* SER_MARKER_MAP;

/* Push metatable with given `__serialize` marker onto the stack.
 * As empty table in lua can be treated as both empty map and empty table, we need to somehow distinguish them.
 * This adds key `__serialize` to the resulting metatable, which might be one of following markers:
 * 1) `seq`: table was an array in the original json;
 * 2) `map`: table was a table in the original json.
 * `marker` param must be one of defined `SER_MARKER_*` consts.
 */
void tt_lua_push_serialize_mt(lua_State *L, char* marker);
