prog: 	driver.o header.o
	g++ -o prog driver.o header.o

driver.o:	driver.cpp header.h
	g++ -c driver.cpp

header.o:	header.cpp header.h
	g++ -c header.cpp

