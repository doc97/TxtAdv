CXXFLAGS=-O -g -Wall
CXX=g++
OUT=TxtAdv.lib
DIR_BUILD=Build

AROPT=ruv
AR=ar

OBJS=AdvGame.o ConsoleIO.o CtrlContentReader.o Game.o GameState.o \
	LambdaExpression.o LambdaResponseHandler.o

.PHONY: all
all: $(OBJS)
	$(AR) $(AROPT) $(DIR_BUILD)/$(OUT) $(patsubst %, $(DIR_BUILD)/%,$(OBJS))

-include $(OBJS:.o=.d)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $(DIR_BUILD)/$*.o
	$(CXX) -MMD $(CXXFLAGS) $*.cpp > $(DIR_BUILD)/$*.d

.PHONY: clean
clean:
	rm -r $(DIR_BUILD)
