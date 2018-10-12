#!/bin/bash

# Always have a test ;)

echo "Enter key size: "
read key

echo "Input test test: "
read inp

echo
echo "Getting transliterated text (keysize of 0):"
tlt=$( echo $inp | ./mpags-cipher -k 0 )
echo $tlt

echo
echo "Encrypting (keysize: $key):"
enc=$( echo $tlt | ./mpags-cipher -k $key )
echo $enc

echo
echo "Decrypting:"
dec=$( echo $enc | ./mpags-cipher -k $key -m decrypt )
echo $dec

echo
if [ "$dec" == "$tlt" ]
then
	echo "Test ok."
else
	echo "Test FAILED."
fi




