The Bit Pattern Generator v-2.0 code base requires the following dependencies for installation:

Dependencies:

1. Boost Libraries
	a. tuple
	b. bind
	c. spirit
	d. dynamic_bitset
	e. any

2. Boost Tools
	a. boost-build
	b. boost-book
	c. quick-book

Installation Notes:

1. Make sure that /usr/local/include in defined in your PATH variable (e.g. "env | grep PATH")
2. As root, run scripts/install-headers to install headers in /usr/local/include/bpg-v2 directory.
3. Use "bjam-xxx --v2" to build the necassary programs (where xxx is the version number of bjam).

 
