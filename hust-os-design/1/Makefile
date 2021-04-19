
CXX ?= g++
CXXFLAGS = -std=c++2a -O3

def:
	$(CXX) $(CXXFLAGS) `pkg-config gtkmm-3.0 --cflags --libs` cp.cc -o cp
	$(CXX) $(CXXFLAGS) 3-ball-game.cc -o 3-ball-game

clean:
	rm -f cp 3-ball-game


