local t = require("luatest")
local simdjson = require("simdjson")
local g = t.group("tarantool")
local specs = require("spec.consts")
local tt_json = require("json")
local fio = require("fio")

local function load_file(filepath)
    local file, err = fio.open(filepath, { "O_RDONLY" })
    t.assert_equals(err, nil)
    t.assert_not_equals(file, nil)
    local allLines = file:read()
    file:close()
    return allLines
end

g.test_nulls_are_same = function ()
  local raw_json = '[{"first_null": null, "second_null": null, "nulls_array": [null, {"key": null}]}]'
  t.assert_equals(simdjson.parse(raw_json), tt_json.decode(raw_json))
end

g.test_compat_with_tarantool_json = function()
  for _, path in ipairs(specs.jsonexamples) do
    local lines = load_file(path)
    t.assert_equals(simdjson.parse(lines), tt_json.decode(lines))
  end
end

g.test_serialize_markers = function ()
  local result = simdjson.parse('{"nested": {"emptyMap": {}}, "emptyArray": []}')
  t.assert_equals(getmetatable(result), {__serialize = "map"})
  t.assert_equals(getmetatable(result.emptyArray), {__serialize = "seq"})
  t.assert_equals(getmetatable(result.nested), {__serialize = "map"})
  t.assert_equals(getmetatable(result.nested.emptyMap), {__serialize = "map"})

	local result = simdjson.parse('[{"emptyMap": {}, "emptyArray": []}]')
  t.assert_equals(getmetatable(result), {__serialize = "seq"})
  t.assert_equals(getmetatable(result[1].emptyMap), {__serialize = "map"})
  t.assert_equals(getmetatable(result[1].emptyArray), {__serialize = "seq"})
end
