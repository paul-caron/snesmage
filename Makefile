

all: snesmage


snesmage: snesmage.cpp
	c++ -o snesmage snesmage.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs`
