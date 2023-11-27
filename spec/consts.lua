local jsonexamples = {
	"apache_builds.json",
	"canada.json",
	"citm_catalog.json",
	"github_events.json",
	"google_maps_api_compact_response.json",
	"google_maps_api_response.json",
	"gsoc-2018.json",
	"instruments.json",
	"marine_ik.json",
	"mesh.json",
	"mesh.pretty.json",
	"numbers.json",
	"random.json",
	"repeat.json",
	"twitter_timeline.json",
	"update-center.json",
	"small/adversarial.json",
	"small/demo.json",
	"small/flatadversarial.json",
	"small/smalldemo.json",
	"small/truenull.json"
}

local function jsonexample_filepath(filename)
  return "jsonexamples/" .. filename
end

for idx, filename in ipairs(jsonexamples) do
  jsonexamples[idx] = jsonexample_filepath(filename)
end

return {
  jsonexamples = jsonexamples
}
