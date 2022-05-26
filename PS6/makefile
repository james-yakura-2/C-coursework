all: clean ps6 run

clean:
	rm -rf *.o ps6

ps6:
	g++ -c Main.cpp
	g++ Main.o -o ps6 -lboost_regex -lboost_date_time

run:
	./ps6 < device1_intouch.log > device1_intouch.log.rpt
	./ps6 < device2_intouch.log > device2_intouch.log.rpt
	./ps6 < device3_intouch.log > device3_intouch.log.rpt
	./ps6 < device4_intouch.log > device4_intouch.log.rpt
	./ps6 < device5_intouch.log > device5_intouch.log.rpt
	./ps6 < device6_intouch.log > device6_intouch.log.rpt