local simdjson = require("simdjson")
local cjson = require("cjson")
local consts = require("spec.consts")

local function loadFile(textFile)
    local file = io.open(textFile, "r")
    if not file then error("File not found at " .. textFile) end
    local allLines = file:read("*all")
    file:close()
    return allLines
end

describe("Make sure everything compiled correctly", function()
	for _, file in ipairs(consts.jsonexamples) do
		it("should parse the file: " .. file, function()
			local fileContents = loadFile(file)
			assert.are.same(cjson.decode(fileContents), simdjson.parse(fileContents))
		end)
	end
end)
