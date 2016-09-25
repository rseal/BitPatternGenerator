The Bit Pattern Generator v-2.0 code base requires the following dependencies for installation:

Dependencies:

1. Boost Libraries
3. SThreads ( see local repo )
4. CommandLineParser ( see local repo )
5. libusb-0.1 series ( a.k.a the old version )
6. Waf build system.


Installation Notes:

1. To build, type "waf clean configure build" from the top-level directory. 
2. To install, type "sudo waf install" -- output files are placed in /usr/local folders.
3. Add "uucp" group to access the LCD using "gpasswd -a user uucp".

Operation:

1. Use bpg-generate to create a new radar mode. 
2. Use bpg-shell to enter the bpg shell to add and run modes. 
 
