#include <iostream>
#include <string>
#include <vector>

#include "ProcessCommandLine.hpp"

bool processCommandLine(
	const std::vector<std::string>& args,
	bool& helpRequested,
	bool& versionRequested,
	std::string& inputFileName,
	std::string& outputFileName,
	bool& decrypt,
	unsigned int& keysize
) {
	// Add a typedef that assigns another name for the given type for clarity
	typedef std::vector<std::string>::size_type size_type;
	const size_type nArgs {args.size()};

	// Process command line arguments - ignore zeroth element, as we know this to
	// be the program name and don't need to worry about it
	for (size_type i {1}; i < nArgs; ++i) {

		if (args[i] == "-h" || args[i] == "--help") {
			helpRequested = true;
		}
		else if (args[i] == "--version") {
			versionRequested = true;
		}
		else if (args[i] == "-i") {
			// Handle input file option
			// Next element is filename unless -i is the last argument
			if (i == nArgs-1) {
	std::cerr << "[error] -i requires a filename argument" << std::endl;
	// failed to parse args 
	return false;
			}
			else {
	// Got filename, so assign value and advance past it
	inputFileName = args[i+1];
	++i;
			}
		}
		else if (args[i] == "-o") {
			// Handle output file option
			// Next element is filename unless -o is the last argument
			if (i == nArgs-1) {
	std::cerr << "[error] -o requires a filename argument" << std::endl;
	// failed to parse args 
	return false;
			}
			else {
	// Got filename, so assign value and advance past it
	outputFileName = args[i+1];
	++i;
			}
		}
		else if (args[i] == "-m") {
			if (i == nArgs - 1) {
				std::cerr << "[error] -m requires a mode argument" << std::endl;
				return false;
			}
			std::string mode = args[++i];
			if ( mode == "encrypt" )
				decrypt = false;
			else if ( mode == "decrypt" )
				decrypt = true;
			else {
				std::cerr << "[error] unknown mode: " << mode << std::endl;
				return false;
			}
		} else if (args[i] == "-k") {
			if ( i == nArgs - 1 ) {
				std::cerr << "[error] -k requires an argument" << std::endl;
				return false;
			}
			int _keysize = std::stoi(args[++i]);
			if ( _keysize < 0 || _keysize > 25 ) {
				std::cerr << "[error] Invalid key size " << _keysize << " - must be in range 0 <= keysize <= 25";
				return false;
			} else
				keysize = _keysize; // Only modify target variable is valid keysize
		}
		else {
			// Have an unknown flag to output error message and return non-zero
			//
			// exit status to indicate failure
			std::cerr << "[error] unknown argument '" << args[i] << "'\n";
	// failed to parse args 
	return false;
		}
	}
	// Reached the end - success
	return true;
}

