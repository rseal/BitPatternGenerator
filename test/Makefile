INC=../include

all: rpg_test keyword_test signal_test

keyword_test: keyword_test.cpp
	g++ -o keyword_test keyword_test.cpp

tr_keyword_test: $(INC)/Rules/TRKeyword.hpp tr_keyword_test.cpp
	g++ -o tr_keyword_test tr_keyword_test.cpp

signal_test: signal_test.cpp
	g++ -o signal_test signal_test.cpp

rpg_test: rpg_test.cpp $(INC)/Common/IInstrumentDefinition.hpp
	g++ -g -O0 -c ../src/InstrumentRuleFactory.cpp -I ../include
	g++ -g -O0 -c ../src/InstrumentFactory.cpp -I ../include
	g++ -g -O0 -o rpg_test rpg_test.cpp InstrumentRuleFactory.o InstrumentFactory.o

lcd_test: lcd_test.cpp
	g++ -g -o lcd_test lcd_test.cpp -lboost_date_time -lpthread

clean:
	rm -rf *~ rpg_test spirit_test signal_test keyword_test \
	InstrumentFactory.o InstrumentRuleFactory.o tr_keyword_test \
	lcd_test time_test
