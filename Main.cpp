#include <iostream>
#include <string>
using namespace std;
#include "DES_Array.h"

int main()
{
	string messageString = "",
		tempMsgString = "";
	int keyBits		= 56,
		messageBits	= 0,
		rounds		= 16,
		msgStrLen	= 0,
		chunks		= 0,
		bitsPerChar	= 4,
		chunkSize	= 64;

	bool validMessage = false;
	int failCount = 0;

	while (!validMessage && failCount < 10) {
		cout << "Enter the plaintext message (must be 16 hexidecimal characters long): ";
		cin >> messageString;

		if (messageString.length() == 16)
		{
			validMessage = true;
			msgStrLen = 16;
		}
		else
		{
			cout << "Invalid message length, try again:\n";
			failCount++;
		}
	}

	messageBits = msgStrLen * bitsPerChar;
	chunks = (msgStrLen * bitsPerChar) / chunkSize;

	cout << "Plaintext:\t" << messageString << "\n";

	if((msgStrLen * 4) > (chunks * chunkSize))
		chunks++;

	// Get initial message chunk
	for(int i = 0; i < (chunkSize / 4); i++)
		tempMsgString += messageString[i];

	DES_Array<char> DES_key(keyBits, keyString.length(), keyString);
	DES_Array<char> DES_message(chunkSize, chunkSize / 4, tempMsgString);
	
	/* KEY PHASE */
	DES_key.PopulateHexArray();	// Pull in key data
	DES_key.PopulateBitArray();	// Convert hex key to bits
	DES_key.PermuteKey();		// Initial key permutation
	DES_key.KeyGeneration();	// Pre-generate keys

	/* ENCRYPTION PHASE */
	cout << "\n. . . Encrypting . . .\n";
	for(int i = 0; i < chunks; i++)
	{
		DES_message.PopulateHexArray();
		DES_message.PopulateBitArray();

		if(i == 0)
			DES_message.PermuteData();

		for(int j = 0; j < rounds; j++)
		{
			string currentKey = "";
			currentKey = DES_key.GetNextKey(j);
			DES_message.DESEncryptionRound(currentKey);
		}

		DES_message.SwapHalves();
		DES_message.FinalPermutation();
	}

	cout << "\nCipher text:\t";
	DES_message.GetCipherText();

	/* DECRYPTION PHASE */
	cout << "\n. . . Decrypting . . .\n";
	for(int i = 0; i < chunks; i++)
	{
		// Initial data permutation
		if(i == 0)
			DES_message.PermuteData();

		for(int j = rounds - 1; j >= 0; j--)
		{
			string currentKey = "";
			currentKey = DES_key.GetNextKey(j);
			DES_message.DESEncryptionRound(currentKey);
		}

		DES_message.SwapHalves();
		DES_message.FinalPermutation();
	}

	cout << "\nPlain text:\t";
	DES_message.GetCipherText();

	cout << "\n. . . Run successful!\n\n";
	system("pause");
	return 0;
}

/*
* Encryption Input:		8 byte hex as the plaintext, one 7-byte hex as the key
* Encryption Output:	8 bytes hex

* Decryption Input:		8 bytes hex as the cipher text, one 7-byte hex as the key
* Decryption Output:	8 byte hex characters
*/