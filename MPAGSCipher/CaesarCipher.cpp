#include <string>

#include "CaesarCipher.hpp"

std::string runCaesarCipher ( 
	const std::string& inputText,
	const size_t key,
	const bool encrypt )
{
	// Create the alphabet container and output string
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result{""};

	// Loop over the input text
	for ( const char c : inputText ) {
		// For each character find the corresponding position in the alphabet
		int pos = alphabet.find(c);

		// Apply the shift (+ve or  –ve depending on encrypt/decrypt)
		// to the position, handling correctly potential wrap-around
		if ( encrypt ) {
			pos += key;
		} else {
			pos -= key;
		}
		if ( pos > (int)alphabet.size() )
			pos = pos % alphabet.size();
		else if ( pos < 0 )
			pos = alphabet.size() + pos; // +(-ve) == subtraction

		// Determine the new character and add it to the output string
		result += alphabet[pos];

	}
// Finally (after the loop), return the output string
	return result;
}

