#ifndef DES_ARRAY_HPP
#define DES_ARRAY_HPP
#include "Patterns.h"

//============================================Constructors/Destructor//
template <class D>
DES_Array<D>::DES_Array()
{
	bitArraySize	= 0;
	hexArraySize	= 0;
	bitCount		= 0;
	hexCount		= 0;
	eachKeyLen		= 0;
	cdLength		= 0;
	lrLength		= 0;
	numOfKeys		= 0;
	currentKey		= " ";
	DES_String		= " ";
	cHalf			= NULL;
	dHalf			= NULL;
	K				= NULL;
	bitArray		= NULL;
	L				= NULL;
	R				= NULL;
	Lnext			= NULL;
	Rnext			= NULL;
	hexArray		= NULL;
	tempArray		= NULL;
}


template <class D>
DES_Array<D>::DES_Array(int bs, int hs, string ds)
{
	bitArraySize	= bs;
	hexArraySize	= hs;
	bitCount		= 0;
	hexCount		= 0;
	eachKeyLen		= 48;
	cdLength		= 28;
	lrLength		= 32;
	numOfKeys		= 16;
	currentKey		= " ";
	DES_String		= ds;

	K = new D[numOfKeys * eachKeyLen];
	if(K != NULL)
	{
		for(int i = 0; i < (numOfKeys * eachKeyLen); i++)
			K[i] = ' ';
	}
	else
		ErrorMessage("Invalid memory allocation -- @ K paramaterized constructor");

	cHalf = new D[cdLength];
	dHalf = new D[cdLength];
	if (cHalf != NULL && dHalf != NULL)
	{
		for (int i = 0; i < cdLength; i++)
			cHalf[i] = dHalf[i] = ' ';
	}
	else
		ErrorMessage("Invalid memory allocation -- @ cHalf or dHalf paramaterized constructor");

	hexArray = new D[hexArraySize];
	if(hexArray != NULL)
	{
		for(int i = 0; i < hexArraySize; i++)
			hexArray[i] = ' ';
	}
	else
		ErrorMessage("Invalid memory allocation -- @ hexArray paramaterized constructor");

	bitArray = new D[bitArraySize];
	tempArray = new D[bitArraySize];
	if(bitArray != NULL && tempArray != NULL)
	{
		for(int i = 0; i < bitArraySize; i++)
			bitArray[i] = tempArray[i] = ' ';
	}
	else
		ErrorMessage("Invalid memory allocation -- @ bitArray or tempArray paramaterized constructor");

	L = new D[lrLength];
	R = new D[lrLength];
	Lnext = new D[lrLength];
	Rnext = new D[lrLength];
	if(L != NULL && R != NULL && Lnext != NULL && Rnext != NULL)
	{
		for(int i = 0; i < lrLength; i++)
			L[i] = R[i] = Lnext[i] = Rnext[i] = ' ';
	}
	else
		ErrorMessage("Invalid memory allocation -- @ L or R or Lnext or Rnext paramaterized constructor");
}


template <class D>
DES_Array<D>::~DES_Array()
{
	delete [] cHalf;
	delete [] dHalf;
	delete [] K;
	delete [] tempArray;
	delete [] bitArray;
	delete [] L;
	delete [] R;
	delete [] Lnext;
	delete [] Rnext;
	delete [] hexArray;
}


template <class D>
void DES_Array<D>::ErrorMessage(string s) const
{
	cout << "ERROR -- " << s << "\n\n";
	system("pause");
	exit(EXIT_SUCCESS);
}


//============================================Manipulation functions//
template <class D>
void DES_Array<D>::InsertBit(D x)
{
	if (bitCount < bitArraySize)
		bitArray[bitCount++] = x;
	else
		ErrorMessage("bitCount == " + to_string(bitCount) + ", array full -- [@InsertBit]");
}

template <class D>
void DES_Array<D>::InsertHex(D x)
{
	if (hexCount < hexArraySize)
		hexArray[hexCount++] = x;
	else
		ErrorMessage("hexCount == " + to_string(hexCount) + ", array full -- [@InsertHex]");
}


template <class D>
void DES_Array<D>::SetNextChunk(string s)
{
	DES_String = s;
}


template <class D>
void DES_Array<D>::SetCurrentKey(string s)
{
	currentKey = s;
}


template <class D>
string DES_Array<D>::GetNextKey(int round)
{
	currentKey = "";
	int currentIndex = round * eachKeyLen;

	for(int i = currentIndex; i < (currentIndex + eachKeyLen); i++)
		currentKey += K[i];

	return currentKey;
}


// Convert a 4-bit binary string to hex char
template <class D>
char DES_Array<D>::BinToHex(string s)
{
	char c = ' ';
	char cArr[4] = { s[0], s[1], s[2], s[3] };

	if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '0') { c = '0'; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '1') { c = '1'; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '1' && s[3] == '0') { c = '2'; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '1' && s[3] == '1') { c = '3'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '0' && s[3] == '0') { c = '4'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '0' && s[3] == '1') { c = '5'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '1' && s[3] == '0') { c = '6'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '1' && s[3] == '1') { c = '7'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '0' && s[3] == '0') { c = '8'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '0' && s[3] == '1') { c = '9'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '1' && s[3] == '0') { c = 'A'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '1' && s[3] == '1') { c = 'B'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '0' && s[3] == '0') { c = 'C'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '0' && s[3] == '1') { c = 'D'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '1' && s[3] == '0') { c = 'E'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '1' && s[3] == '1') { c = 'F'; }
	else { ErrorMessage("Incorrect bit sequence -- [@BinToHex]"); }

	return c;
}


// Convert a 4-bit binary string to int
template <class D>
int DES_Array<D>::BinToDec(string s)
{
	int c = 0;
	char cArr[4] = { s[0], s[1], s[2], s[3] };

	if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '0') { c = 0; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '1') { c = 1; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '1' && s[3] == '0') { c = 2; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '1' && s[3] == '1') { c = 3; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '0' && s[3] == '0') { c = 4; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '0' && s[3] == '1') { c = 5; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '1' && s[3] == '0') { c = 6; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '1' && s[3] == '1') { c = 7; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '0' && s[3] == '0') { c = 8; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '0' && s[3] == '1') { c = 9; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '1' && s[3] == '0') { c = 10; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '1' && s[3] == '1') { c = 11; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '0' && s[3] == '0') { c = 12; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '0' && s[3] == '1') { c = 13; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '1' && s[3] == '0') { c = 14; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '1' && s[3] == '1') { c = 15; }
	else { ErrorMessage("Incorrect bit sqeuence -- [@BinToDec]"); }

	return c;
}


// Convert a hex char to a 4-bit binary string
template <class D>
string DES_Array<D>::HexToBin(char c)
{
	string s = " ";
	
	switch(c) {
		case '0': { s = "0000"; break; }
		case '1': { s = "0001"; break; }
		case '2': { s = "0010"; break; }
		case '3': { s = "0011"; break; }
		case '4': { s = "0100"; break; }
		case '5': { s = "0101"; break; }
		case '6': { s = "0110"; break; }
		case '7': { s = "0111"; break; }
		case '8': { s = "1000"; break; }
		case '9': { s = "1001"; break; }
		case 'A': { s = "1010"; break; }
		case 'B': { s = "1011"; break; }
		case 'C': { s = "1100"; break; }
		case 'D': { s = "1101"; break; }
		case 'E': { s = "1110"; break; }
		case 'F': { s = "1111"; break; }
	}

	if (s == " ")
		ErrorMessage("Incorrect hex char -- [@HexToBin]");

	return s;
}


// Convert an int to a 4-bit binary string
template <class D>
string DES_Array<D>::DecToBin(int i)
{
	string s = " ";

	switch(i) {
		case 0: { s = "0000"; break; }
		case 1: { s = "0001"; break; }
		case 2: { s = "0010"; break; }
		case 3: { s = "0011"; break; }
		case 4: { s = "0100"; break; }
		case 5: { s = "0101"; break; }
		case 6: { s = "0110"; break; }
		case 7: { s = "0111"; break; }
		case 8: { s = "1000"; break; }
		case 9: { s = "1001"; break; }
		case 10: { s = "1010"; break; }
		case 11: { s = "1011"; break; }
		case 12: { s = "1100"; break; }
		case 13: { s = "1101"; break; }
		case 14: { s = "1110"; break; }
		case 15: { s = "1111"; break; }
	}

	if (s == " ")
		ErrorMessage("Incorrect int value -- [@DecToBin]");

	return s;
}


template <class D>
void DES_Array<D>::PopulateHexArray()
{
	for(int i = 0; i < hexArraySize; i++)
		hexArray[i] = DES_String[i];
}


template <class D>
void DES_Array<D>::PopulateBitArray()
{
	string tempStr = " ";

	for(int i = 0; i < hexArraySize; i++)
	{
		tempStr = HexToBin(hexArray[i]);

		for(int j = 0; j < 4; j++)
			InsertBit(tempStr[j]);
	}
}


//============================================Permutation functions//
template <class D>
void DES_Array<D>::PermuteData()
{
	for(int i = 0; i < bitArraySize; i++)
		tempArray[i] = bitArray[dataPattern[i]];

	for(int i = 0; i < bitArraySize; i++)
		bitArray[i] = tempArray[i];
}

/*
	Can maybe genericize these into one function, passing in the array to be permuted?
*/

template <class D>
void DES_Array<D>::PermuteKey()
{
	for(int i = 0; i < bitArraySize; i++)
		tempArray[i] = bitArray[keyPattern[i]];

	for(int i = 0; i < bitArraySize; i++)
		bitArray[i] = tempArray[i];
}


template <class D>
void DES_Array<D>::KeyGeneration()
{
	for(int i = 0; i < cdLength; i++)
	{
		cHalf[i] = bitArray[i];
		dHalf[i] = bitArray[i + cdLength];
	}

	for(int i = 0; i < numOfKeys; i++)
	{
		int count = 0;

		/* SHIFTING PHASE */
		if(i == 0 || i == 1 || i == 8 || i == 15)
		{
			// ONE LEFT SHIFT

			char cTemp = cHalf[0], dTemp = dHalf[0];

			for(int j = 0; j < (cdLength - 1); j++)
			{
				cHalf[j] = cHalf[j + 1];
				dHalf[j] = dHalf[j + 1];
			}

			cHalf[cdLength - 1] = cTemp;
			dHalf[cdLength - 1] = dTemp;
		}
		else
		{
			// TWO LEFT SHIFT

			char cTemp0 = cHalf[0], cTemp1 = cHalf[1],
				 dTemp0 = dHalf[0], dTemp1 = dHalf[1];

			for(int j = 0; j < (cdLength - 2); j++)
			{
				cHalf[j] = cHalf[j + 2];
				dHalf[j] = dHalf[j + 2];
			}

			cHalf[cdLength - 2] = cTemp0;
			cHalf[cdLength - 1] = cTemp1;
			dHalf[cdLength - 2] = dTemp0;
			dHalf[cdLength - 1] = dTemp1;
		}

		/* PERMUTATION PHASE */
		for(int k = (i * eachKeyLen); k < ((i + 1) * eachKeyLen - (eachKeyLen / 2)); k++)
		{
			K[k] = cHalf[keyLeft[count]];
			K[k + eachKeyLen/2] = dHalf[keyRight[count]];
			count++;
		}
	}
}


template <class D>
void DES_Array<D>::DESEncryptionRound(string key)
{
	const int chunks = 8, bits = 6;
	D expansion[chunks][bits];
	D Rchunks[chunks][bits - 2];
	D Kchunks[chunks][bits];
	D Soutput[chunks][bits - 2];
	D tempNext[32];

	for(int i = 0; i < lrLength; i++)
	{
		L[i] = bitArray[i];
		Lnext[i] = bitArray[i + lrLength];
		R[i] = bitArray[i + lrLength];
	}

	for(int i = 0; i < chunks; i++)
	{
		for(int j = 0; j < (bits - 2); j++)
			Rchunks[i][j] = R[i * (bits - 2) + j];
	}

	for(int i = 0; i < chunks; i++)
	{
		for(int j = 0; j < bits; j++)
			Kchunks[i][j] = key[i * bits + j];
	}

	/*----- MANGLER BEGIN -----*/
	/* BIT EXPANSION */
	for(int i = 0; i < chunks; i++)
	{
		for(int j = 0; j < bits; j++)
		{
			if(i == 0)
			{
				if(j == 0)
					expansion[i][j] = Rchunks[chunks - 1][bits - 3];
				else if(j == bits - 1)
					expansion[i][j] = Rchunks[i + 1][0];
				else
					expansion[i][j] = Rchunks[i][j - 1];
			}
			else if(i == chunks - 1)
			{
				if(j == 0)
					expansion[i][j] = Rchunks[i - 1][bits - 3];
				else if(j == bits - 1)
					expansion[i][j] = Rchunks[0][0];
				else
					expansion[i][j] = Rchunks[i][j - 1];
			}
			else
			{
				if(j == 0)
					expansion[i][j] = Rchunks[i - 1][bits - 3];
				else if(j == bits - 1)
					expansion[i][j] = Rchunks[i + 1][0];
				else
					expansion[i][j] = Rchunks[i][j - 1];
			}
		}
	}

	/* MANGLER XOR */
	for(int i = 0; i < chunks; i++)
	{
		for(int j = 0; j < bits; j++)
			expansion[i][j] = (expansion[i][j] ^ Kchunks[i][j]) ? '1' : '0';
	}
	
	/* S-BOXES */
	for(int i = 0; i < chunks; i++)
	{
		int rowIndex = 0, colIndex = 0;
		string tempStr = "";

		if(expansion[i][0] == '0')
			rowIndex = (expansion[i][5] == '0') ? 0 : 1;
		else
			rowIndex = (expansion[i][5] == '0') ? 2 : 3;

		for(int j = 0; j < 4; j++)
			tempStr += expansion[i][j + 1];

		colIndex = BinToDec(tempStr);

		switch(i)
		{
			case 0: { tempStr = DecToBin(S1[rowIndex][colIndex]); break;}
			case 1: { tempStr = DecToBin(S2[rowIndex][colIndex]); break;}
			case 2: { tempStr = DecToBin(S3[rowIndex][colIndex]); break;}
			case 3: { tempStr = DecToBin(S4[rowIndex][colIndex]); break;}
			case 4: { tempStr = DecToBin(S5[rowIndex][colIndex]); break;}
			case 5: { tempStr = DecToBin(S6[rowIndex][colIndex]); break;}
			case 6: { tempStr = DecToBin(S7[rowIndex][colIndex]); break;}
			case 7: { tempStr = DecToBin(S8[rowIndex][colIndex]); break;}
		}

		for(int j = 0; j < 4; j++)
			Soutput[i][j] = tempStr[j];
		
		int bitcount = 0;
		for(int j = 0; j < chunks; j++)
		{
			for(int k = 0; k < bits - 2; k++)
			{
				tempNext[bitcount] = Soutput[j][k];
				bitcount++;
			}
		}

		// S-box permute
		for(int j = 0; j < 32; j++)
			Rnext[j] = tempNext[sBoxPerm[j]];
	}
	/*----- MANGLER END -----*/

	/* POST-MANGLER XOR */
	for(int i = 0; i < 32; i++)
		Rnext[i] = (Rnext[i] + L[i] == 97) ? '1' : '0';

	/* REPOPULATE BITARRAY */
	for(int i = 0; i < 32; i++)
	{
		bitArray[i] = Lnext[i];
		bitArray[i + 32] = Rnext[i];
	}
}


template <class D>
void DES_Array<D>::SwapHalves()
{
	char temp;

	for(int i = 0; i < 32; i++)
	{
		temp = bitArray[i];
		bitArray[i] = bitArray[i + 32];
		bitArray[i + 32] = temp;
	}
}


template <class D>
void DES_Array<D>::FinalPermutation()
{
	for(int i = 0; i < bitArraySize; i++)
		tempArray[i] = bitArray[finalPerm[i]];

	for(int i = 0; i < bitArraySize; i++)
		bitArray[i] = tempArray[i];
}


template <class D>
void DES_Array<D>::GetCipherText()
{
	int count = 0;
	string tempStr = "";

	for(int i = 0; i < 64; i++)
	{
		tempStr += bitArray[i];

		if((i + 1) % 4 == 0)
		{
			hexArray[count] = BinToHex(tempStr);
			count++;
			tempStr = "";
		}
	}

	for(int i = 0; i < hexArraySize; i++)
		cout << hexArray[i];
	cout << "\n";
}

#endif