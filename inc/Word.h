#ifndef WORD_H_
#define WORD_H_

#include <string>
#include "Page.h"
#include "Occurence.h"

using namespace std;

//This class stores a word along with all of its occurences, which in turn
//store how many times the word has occured.
class Word
{
	public:
		//Constructor
		Word(const Word &_other);

		//Constructor
		Word(string _word);

		//Constructor
		Word(string _word, URL _theURL);

		//Destructor
		~Word();

		//Overloaded operators
		bool operator== (const Word & other)  const;
		Word& operator= (const Word & other);
		bool operator< (const Word & other)  const;
		bool operator> (const Word & other)  const;

		//Return a poitner to the inner refererences object.
		BST<Occurence> * getOccurences();

		//Add an occurence to the word.
		void addOccurence(URL & _theURL);

		//Get the value of the word.
		string getValue();

	private:
		//The word being stored
		string value;

		//A set of occurences of each distinct page that this word appears on.
		BST<Occurence> * Occurences;
};

#endif  /* WORD_H_ */
