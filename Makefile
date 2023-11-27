_SRC = src/luasimdjson.cpp src/simdjson.cpp $(SRC)
INCLUDE = -I$(LUA_INCDIR)
LIBS_PATH = -L$(LUA_LIBDIR)
LIBS = -lpthread
FLAGS = -std=c++11 -Wall $(LIBFLAG) $(CFLAGS)

all: simdjson.so

simdjson.so:
	$(CXX) $(_SRC) $(FLAGS) $(INCLUDE) $(LIBS_PATH) $(LIBS) -o $@

clean:
	-rm *.so

install: simdjson.so
	cp simdjson.so $(INST_LIBDIR)

build: clean
	tarantoolctl rocks make lua-simdjson-pico.scm-1.rockspec

local-env:
	./dev_deps.sh

test: build
	.rocks/bin/luatest -v tests/
