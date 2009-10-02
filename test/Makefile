INC=../include

all: rpg_test keyword_test signal_test

keyword_test: keyword_test.cpp
	g++ -o keyword_test keyword_test.cpp

tr_keyword_test: $(INC)/Rules/TRKeyword.hpp tr_keyword_test.cpp
	g++ -o tr_keyword_test tr_keyword_test.cpp

signal_test: signal_test.cpp
	g++ -o signal_test signal_test.cpp

rpg_test: rpg_test.cpp $(INC)/IInstrumentDefinition.hpp
	g++ -c ../src/InstrumentRuleFactory.cpp -I ../include
	g++ -c ../src/InstrumentFactory.cpp -I ../include
	g++ -o rpg_test rpg_test.cpp InstrumentRuleFactory.o InstrumentFactory.o

clean:
	rm -rf *~ rpg_test spirit_test signal_test keyword_test \
	InstrumentFactory.o InstrumentRuleFactory.o tr_keyword_test
