CC=g++
CPPFLAGS=-Wall -ansi -pedantic -O2 -fno-elide-constructors -g -L.

# Main program sources
FILES=util.cc tag.cc tag_byte.cc tag_byte_array.cc tag_compound.cc tag_list.cc \
	  tag_end.cc tag_double.cc tag_long.cc tag_string.cc tag_short.cc \
	  tag_int.cc tag_float.cc nbtfile.cc

SOURCES=$(addprefix src/, $(FILES))
HEADERS=$(addsuffix .h, $(basename $(SOURCES)))
OBJECTS=$(addsuffix .o, $(basename $(SOURCES)))

all: nbttest

libcppnbt: objects
	ar -rcs libcppnbt.a $(OBJECTS)

nbttest: libcppnbt test.cc
	$(CC) $(CPPFLAGS) test.cc -lpng -lcppnbt -lz -o $@

objects: $(OBJECTS)
$(OBJECTS):

clean:
	@find -name '*.o' -print -delete | sed -e 's/^/Delete /'
