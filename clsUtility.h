#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "clsDate.h"
using namespace std;
class clsUtility
{

private:
	struct CharTypes {
		enum Type {
			CapitalLetters,
			SmallLetters,
			Digits,
			SpecialChars
		};
	};
	struct StringTypes {
		enum Type {
			CapitalLetters,
			SmallLetters,
			Digits,
			SpecialChars,
			MixChars
		};
	};

public:
	static void Srand() {
		srand(time(0));
	}
	static int RandomNumber(int From, int To) {
		if (From > To) {
			return -1;
		}
		return rand() % (To - From + 1) + From;
	}
	static char GetRandomCharacter(CharTypes::Type type) {
		switch (type) {
			case CharTypes::CapitalLetters:
				return char(RandomNumber('A', 'Z'));
			case CharTypes::SmallLetters:
				return char(RandomNumber('a', 'z'));
			case  CharTypes::Digits:
				return char(RandomNumber('0', '9'));
			case CharTypes::SpecialChars:
				return char(RandomNumber('!', '/'));
			default:
				return char(0);
		}
	}
	static string GenerateWord(StringTypes::Type type , int length) {
		string word = "";
		if (length < 1) {
			return word;
		}	
		if (type == StringTypes::MixChars) {
			for (int i = 0; i < length; i++) {
				word += GetRandomCharacter(static_cast<CharTypes::Type> (RandomNumber(CharTypes::CapitalLetters, CharTypes::SpecialChars)));
			}
		}
		else {
			for (int i = 0; i < length; i++) {
				word += GetRandomCharacter(static_cast<CharTypes::Type>(type));
			}
		}
		return word;
	}
	static string GenerateKey(StringTypes::Type type , int length = 25) {
		return GenerateWord(type, length);
	}
	static void GenerateKeys(int NumberOfKeys, StringTypes::Type type) {
		for (int i = 0; i < NumberOfKeys; i++) {
			cout << GenerateKey(type) << endl;
		}
	}
	template <typename T>
	static void Swap(T& x , T& y) {
		T temp = x;
		x = y;	
		y = temp;
	}
	template <typename T>
	static void ShuffleArray(T arr[], int size) {
		for (int i = size - 1; i >= 0; i--) {
			int j = RandomNumber(0, i);
			Swap(arr[i], arr[j]);
		}
	}
	static void FillArrayWithRandomNumbers(int arr[], int size, int From, int To) {
		if (From > To || size < 1) {
			return;
		}
		for (int i = 0; i < size; i++) {
			arr[i] = RandomNumber(From, To);
		}
	}
	static void FillArrayWithRandomWords (string arr[], int size, StringTypes::Type type, int WordLength) {
		if (size < 1 || WordLength < 1) {
			return;
		}
		for (int i = 0; i < size; i++) {
			arr[i] = GenerateWord(type, WordLength);
		}
	}
	static void FillArrayWithRandomKeys(string arr[], int size, StringTypes::Type type, int KeyLength = 25) {
		if (size < 1 || KeyLength < 1) {
			return;
		}
		for (int i = 0; i < size; i++) {
			arr[i] = GenerateKey(type, KeyLength);
		}
	}
	static string EncryptText(string text, int key) {
		string encryptedText = "";
		for (char c : text) {
			if (isalpha(c)) {
				char base = isupper(c) ? 'A' : 'a';
				encryptedText += char((c - base + key) % 26 + base);
			}
			else {
				encryptedText += c;
			}
		}
		return encryptedText;
	}
	static string DecryptText(string text, int key) {
		return EncryptText(text, 26 - (key % 26));
	}
};

