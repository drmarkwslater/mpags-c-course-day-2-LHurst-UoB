#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPPP
#include <string>
#include <vector>


bool processCommandLine(
	const std::vector<std::string>& args,
	bool& helpRequested,
	bool& versionRequested,
	std::string& inputFileName,
	std::string& outputFileName
);
#endif
