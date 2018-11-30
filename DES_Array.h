#ifndef DES_ARRAY_H
#define DES_ARRAY_H

template <class D>
class DES_Array {
	private:
		int hexArraySize;
		int bitArraySize;
		int bitCount;
		int hexCount;
		int eachKeyLen;
		int cdLength;
		int lrLength;
		int numOfKeys;
		string currentKey;
		string DES_String;
		D *cHalf;
		D *dHalf;
		D *K;
		D *hexArray;
		D *bitArray;
		D *L;
		D *R;
		D *Lnext;
		D *Rnext;
		D *tempArray;

	public:
		DES_Array();
		DES_Array(int, int, string);
		~DES_Array();
		void ErrorMessage(string) const;
		void InsertBit(D);
		void InsertHex(D);
		void SetNextChunk(string);
		void SetCurrentKey(string);
		string GetNextKey(int);
		char BinToHex(string);
		int BinToDec(string);
		string HexToBin(char);
		string DecToBin(int);
		void PopulateBitArray();
		void PopulateHexArray();
		void PermuteData();
		void PermuteKey();
		void KeyGeneration();
		void DESEncryptionRound(string);
		void SwapHalves();
		void FinalPermutation();
		void GetCipherText();
};
#include "DES_Array.hpp"

#endif