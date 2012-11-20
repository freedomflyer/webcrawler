#ifndef WORDLIST_H_
#define WORDLIST_H_

#include <string>
#include "Word.h"
#include "URL.h"
#include "BST.h"


using namespace std;

class WordList
{
	public:
		//Constructor
		WordList();

		//Destructor
		~WordList();

		//Add a word to the word list w/ URL
		void addWord(string _theWord, URL _theURL);

		//Get the BST of words wrapped inside
		BST<Word> * getWords();

		//Get size of WordList
		int getSize();

		//Testing function
		static bool Test(ostream & os);

	private:
		BST<Word> words;
};

#endif /* WORDLIST_H_ */
