#include "WordList.h"

WordList::WordList()
{
}

WordList::~WordList()
{
}

void WordList::addWord(string _theWord, URL _theURL)
{
	Word tempWord(_theWord);
	if(words.Find(tempWord) == NULL)
	{
		Word wordToInsert(_theWord, _theURL);
		words.Insert(wordToInsert);
	}
	else
	{
		Word * wordToEdit = words.FindPointerToValue(tempWord);

		wordToEdit->addOccurence(_theURL);
	}
}

BST<Word> * WordList::getWords()
{
	return &words;
}

int WordList::getSize()
{
	return words.GetSize();
}

bool Test(ostream & os)
{
	return false;
}
