program_name = vtchecker

vtchecker: main.cpp
	g++ main.cpp -I /usr/include/python2.7/ -l python2.7 -l ssl -l crypto -o $(program_name)

clean:
	rm *.o