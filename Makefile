MODULE_big  = eigen
EXTENSION   = eigen
EXTVERSION  = $(shell grep default_version $(EXTENSION).control | sed -e "s/default_version[[:space:]]*=[[:space:]]*'\([^']*\)'/\1/")
DATA        = sql/$(EXTENSION)--$(EXTVERSION).sql
OBJS        = $(patsubst %.c, %.o, $(wildcard src/*.c)) $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

CPLUSPLUSFLAGS = -W -Wall -O3 -msse4.2 -march=native -DNDEBUG
CPLUSPLUSFLAGS += $(PG_CPPFLAGS)

OCC := $(CC)
CC = $(CXX)
%.o : %.c
	$(OCC) $(CPPFLAGS) -fPIC -O3 -msse4.2 -march=native -c -o $@ $<

%.o : %.cpp
	$(CXX) $(CPLUSPLUSFLAGS) $(CPPFLAGS) -fpic -c -o $@ $<
