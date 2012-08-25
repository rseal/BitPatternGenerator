The Bit Pattern Generator v-2.0 code base requires the following dependencies for installation:

Dependencies:

1. Boost Libraries
	a. tuple
	b. bind
	c. spirit
	d. dynamic_bitset
	e. any

3. SThreads ( see local repo )
4. CommandLineParser ( see local repo )
5. libusb-0.1 series ( a.k.a the old version )
6. Waf build system.


Installation Notes:

1. Make sure that /usr/local/include in defined in your PATH variable (e.g. "env | grep PATH")
2. As root, run "waf install_headers".
3. As normal user, run "waf configure build" (use -j<ncpu> for multithread build).
4. As root, run "waf install".
5. Add "uucp" group to access the LCD using "gpasswd -a user uucp".

Operation:

1. Use bpg-generate to create a new radar mode. 
2. Use bpg-shell to enter the bpg shell to add and run modes. 
 
