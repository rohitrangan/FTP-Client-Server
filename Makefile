# Makefile for the C++ code.
CXX=c++
CXXFLAGS= -Wall -Wextra
CXXSRCS1=client.cpp
#util.cpp http_util.cpp content_type.cpp
CXXSRCS2=server.cpp
#util.cpp http_util.cpp content_type.cpp
CXXOBJS1=$(CXXSRCS1:.cpp=.o)
CXXOBJS2=$(CXXSRCS2:.cpp=.o)
LIBS=
INCLUDES=-I.
TARGET1=client
TARGET2=server
#DEBUGFLAGS=-g -ggdb -O0 -fno-inline

# Required for the target clean.
RM=rm -rf

CXXFLAGS+=$(DEBUGFLAGS) $(INCLUDES) $(LIBS)

all : $(CXXSRCS1) $(CXXOBJS1) $(TARGET1) $(CXXSRCS2) $(CXXOBJS2) $(TARGET2)

$(TARGET1) : $(CXXOBJS1)
	$(CXX) $(CXXOBJS1) -o $(TARGET1)

$(TARGET2) : $(CXXOBJS2)
	$(CXX) $(CXXOBJS2) -o $(TARGET2)

.cpp.o :
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) *.o *.dSYM $(TARGET1) $(TARGET2)

depend : .depend

.depend : $(CXXSRCS1) $(CXXSRCS2)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ -MF ./.depend

.PHONY : clean

include .depend