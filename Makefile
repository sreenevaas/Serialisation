CXX=g++
RM=rm
Sources=DataAnalysis.cpp \
	Serialisation.cpp \
	DeSerialisation.cpp \
	RecordContainer.cpp \
	Record.cpp

Executable=DataAnalysis

CXXFlags=-c -Wall -g -Iinc -std=c++11
LDFlags=
ObjectDir=obj/
SourceDir=src/
BinDir=bin/

Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: $(CSources) $(CExecutable)

$(CExecutable): $(CObjects)
	$(CXX) $(LDFlags) $(CObjects) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CXX) $(CXXFlags) $< -o $@

clean:
	$(RM) $(CObjects) $(CExecutable) 
	$(RM) ./bin/*.bin
