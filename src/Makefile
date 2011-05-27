CC=g++
CPPFLAGS=-Wall -ansi -pedantic -O2 -fno-elide-constructors -g

# Main program sources
SOURCES=tag.cc tag_byte.cc tag_byte_array.cc tag_compound.cc tag_list.cc \
	    tag_end.cc tag_double.cc tag_long.cc tag_string.cc tag_short.cc \
		tag_int.cc tag_float.cc test.cc util.cc
HEADERS=$(addsuffix .h, $(basename $(SOURCES)))
OBJECTS=$(addsuffix .o, $(basename $(SOURCES)))


nbttest: objects
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@

objects: $(OBJECTS)
$(OBJECTS):

clean:
	@find -name '*.o' -print -delete | sed -e 's/^/Delete /'
