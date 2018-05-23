#Makefile

CC = g++
CXXFLAGS = -std=c++11

tmSimulator : TuringMachine.o TuringMachineTransitions.o
