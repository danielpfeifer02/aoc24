CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++20 -ftemplate-depth=16384 -fconstexpr-depth=16384 -Wno-trigraphs -Wno-unused-parameter -I /usr/local/include/eigen3

.PHONY: all clean day_%

all: 
	@if [ -z "$(day)" ]; then \
		echo "Please provide a day number. Usage: make day=X"; \
		exit 1; \
	fi
	@echo "Compiling day $(day)..."
	@if [ ! -f day_$(day)/sol.cpp ]; then \
		echo "Error: Source file day_$(day)/sol.cpp does not exist!"; \
		exit 1; \
	fi
	$(CXX) $(CXXFLAGS) common.h day_$(day)/sol.cpp -o day_$(day)/sol

clean:
	rm -f day_*/sol
