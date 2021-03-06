// Standard Library includes
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "CaesarCipher.hpp"
#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
	// Convert the command-line arguments into a more easily usable form
	const std::vector<std::string> cmdLineArgs {argv, argv+argc};

	// Options that might be set by the command-line arguments
	bool helpRequested {false};
	bool versionRequested {false};
	std::string inputFile {""};
	std::string outputFile {""};
	bool decrypt {false};
	unsigned int key {0};

	if ( ! processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, decrypt, key) )
		return 1; // Error indication

	// Handle help, if requested
	if (helpRequested) {
		// Line splitting for readability
		std::cout
			<< "Usage: mpags-cipher [-i <file>] [-o <file>] [-m <encrypt/decrypt>] -k <keylength>\n\n"
			<< "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
			<< "Available options:\n\n"
			<< "  -h|--help          Print this help message and exit\n\n"
			<< "  --version          Print version information\n\n"
			<< "  -i FILE            Read text to be processed from FILE\n"
			<< "                     Stdin will be used if not supplied\n\n"
			<< "  -o FILE            Write processed text to FILE\n"
			<< "                     Stdout will be used if not supplied\n\n"
			<< "  -m encrypt/decrypt Mode - encrypt or decrypt/n"
			<< "                     encrypt if not supplied\n\n"
			<< "  -k keylength       Length of the key to use\n\n"
	;
		// Help requires no further action, so return from main
		// with 0 used to indicate success
		return 0;
	}

	// Handle version, if requested
	// Like help, requires no further action,
	// so return from main with zero to indicate success
	if (versionRequested) {
		std::cout << "0.1.0" << std::endl;
		return 0;
	}

	// Initialise variables for processing input text
	char inputChar {'x'};
	std::string inputText {""}; // This will only be used if the input and output are both connected to stdin/stdout - otherwise we will write as we read

	// Read in user input from stdin/file

	// we'll cover better ways of doing this later than raw pointers (or tempates if you're feeling brave!) :)
	std::istream *input;
	std::ifstream infile;

	if ( inputFile.empty() )
	input = &std::cin;
	else {
		infile.open(inputFile);
	input = &infile;
	}

	std::ostream *output;
	std::ofstream outfile;
	if ( outputFile.empty() )
	output = &std::cout;
	else {
	outfile.open(outputFile);
	output = &outfile;
	}

	if ( ! input->good() || ! output->good() ) {
	std::cerr << "Problem with input or output file" << std::endl;
	return 1;
	}
	// Loop over each character from user input
	// (until Return then CTRL-D (EOF) pressed)
	while(*input >> inputChar)
	{
		std::string encrypted_char = runCaesarCipher(transformChar(inputChar), key, !decrypt);
		if ( inputFile.empty() && outputFile.empty() )
			inputText += encrypted_char;
		else
			*output << encrypted_char; // Stream output if not reading/writing from stdin/out
	}

	// Output the transliterated text to stdout if buffered in memory because we were reading from stdin
	if (inputFile.empty() && outputFile.empty())
	*output << inputText;

	*output << std::endl; // Finish with a newline

	// No requirement to return from main, but we do so for clarity
	// and for consistency with other functions
	return 0;
}
