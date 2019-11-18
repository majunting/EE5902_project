# EE5902_project
This project makes use of Noxim, a NoC simulation software based on systemC.

The recommanded operating system for this project is linux. The required libraries include C++ compiler, YAML (with Boost Libraries) and SystemC.

To install C++ compiler on linux: 
	run command: sudo apt-get install build-essential

To install YAML: 
	run command: sudo apt-get install libyaml-cpp-dev libboost-dev
	if the packet libyaml-cpp-dev is not available, just build yaml-cpp
	    Prerequisites:
    - CMake
        sudo apt-get install cmake
    - Boost libs
    	sudo apt-get install libboost-dev	
    Then download code from https://github.com/jbeder/yaml-cpp/archive/master.zip
    and execute the following comamnds:
	unzip yaml-cpp-master.zip
	mv yaml-cpp-master yaml-cpp
	cd yaml-cpp
	mkdir lib
	cd lib
	cmake ..
	make
	sudo make install

To install SystemC:
	The required version of SystemC is 2.3.1

Build and run Noxim:
	to build Noxim, just run 'make'
	to execute noxim, use command:
		./noxim -config test_setup/mesh4/xy.yaml
	with xy.yaml being the simulation setup file
