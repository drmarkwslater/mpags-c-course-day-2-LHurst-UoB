// Standard Library includes
#include <iostream>
#include <string>
#include <vector>

// For std::isalpha and std::isupper
#include <cctype>

std::string transformChar( const char in_char ) {
    // Uppercase alphabetic characters
    if (std::isalpha(in_char)) {
      return std::string(1, std::toupper(in_char));
    }

    // Transliterate digits to English words
    switch (in_char) {
      case '0':
		return "ZERO";
      case '1':
		return "ONE";
      case '2':
		return "TWO";
      case '3':
		return "THREE";
      case '4':
		return "FOUR";
      case '5':
		return "FIVE";
      case '6':
		return "SIX";
      case '7':
		return "SEVEN";
      case '8':
		return "EIGHT";
      case '9':
		return "NINE";
    }

    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
    return "";
}

bool processCommandLine(
	const std::vector<std::string>& args,
	bool& helpRequested,
	bool& versionRequested,
	std::string& inputFileName,
	std::string& outputFileName
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
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
	// failed to parse args 
	return false;
    }
  }
	// Reached the end - success
	return true;
}

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

	if ( ! processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile) )
		return 1; // Error indication

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
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
  std::string inputText {""};

  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  if (!inputFile.empty()) {
    std::cout << "[warning] input from file ('"
              << inputFile
              << "') not implemented yet, using stdin\n";
  }

  // Loop over each character from user input
  // (until Return then CTRL-D (EOF) pressed)
  while(std::cin >> inputChar)
  {
	inputText +=  transformChar(inputChar);
  }

  // Output the transliterated text
  // Warn that output file option not yet implemented
  if (!outputFile.empty()) {
    std::cout << "[warning] output to file ('"
              << outputFile
              << "') not implemented yet, using stdout\n";
  }

  std::cout << inputText << std::endl;

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}
