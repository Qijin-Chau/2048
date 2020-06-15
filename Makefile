# simft Makefile
# by: Qijin Chau
# date: 3/13/19
#

CXX      = clang++
CXXFLAGS = -Wall -Wextra -g -std=c++11
LDFlagS  = -g


2048: 2048.cpp
	$(CXX) -o 2048 2048.cpp