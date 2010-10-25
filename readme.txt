The Bit Pattern Generator v-2.0 code base requires the following dependencies for installation:

Dependencies:

1. Boost Libraries
	a. tuple
	b. bind
	c. spirit
	d. dynamic_bitset
	e. any

2. Boost Tools
	a. boost-book ( optional )
	b. quick-book ( optional )

3. SThreads ( see local repo )
4. CommandLineParser ( see local repo )
5. libusb-0.1 series ( a.k.a the old version )
6. Scons build system. 


Installation Notes:

1. Make sure that /usr/local/include in defined in your PATH variable (e.g. "env | grep PATH")
2. As root, run "scons install-headers".
3. As normal user, run "scons".
4. As root, run "scons install".
5. Add "uucp" group to access the LCD using "gpasswd -a user uucp".

Operation:

1. Use bpg-generate to create a new radar mode. 
2. Use bpg-shell to enter the bpg shell to add and run modes. 
 
