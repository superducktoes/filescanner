program_name = vtchecker

vtchecker: 
	g++ main.cpp -I /usr/include/python2.7/ -l python2.7 -o $(program_name)
