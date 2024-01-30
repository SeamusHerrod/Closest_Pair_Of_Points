all:
	g++ -std=c++11 MainTest.cpp -o Lab04 
	chmod +x runScript.sh
	./runScript.sh



clean:
	rm test outTest* Lab04 result_*.txt time_log*.txt test_result 
