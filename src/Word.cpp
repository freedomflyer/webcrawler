#include "Word.h"

//Used to make a full on...word!
Word::Word(string _word, URL _theURL):value(_word), Occurences(NULL)
{
	//cout << "Creating Word" << endl;
	Occurences = new BST<Occurence>();

	Occurence o(_theURL);
	Occurences->Insert(o);
}

//Used to construct a dummy word object.
Word::Word(string _word):value(_word), Occurences(NULL)
{
	Occurences = new BST<Occurence>();
}

//Copy constructor
Word::Word(const Word &_word)
{
	Occurences = new BST<Occurence>(*_word.Occurences);
	value = _word.value;
}

Word::~Word()
{
	delete Occurences;
}

string Word::getValue()
{
	return value;
}

Word& Word::operator= (const Word & other)
{
	if(this != &other)
	{
		//The word being stored
		value = other.value;

		//A set of occurences of each distinct page that this word appears on.
		Occurences = other.Occurences;
	}
	return *this;
}

bool Word::operator== (const Word & other) const
{
	return(value == other.value);
}

bool Word::operator< (const Word & other) const
{
	return(value < other.value);
}

bool Word::operator> (const Word & other) const
{
	return(value > other.value);
}

BST<Occurence> * Word::getOccurences()
{
	return Occurences;
}

void Word::addOccurence(URL & _theURL)
{
	Occurence tempOccurence(_theURL);
	if(Occurences->Find(tempOccurence) ==  NULL)
	{
		Occurences->Insert(Occurence(_theURL.getURL()));
	}
	else
	{
		Occurence * theOccurence = Occurences->FindPointerToValue(tempOccurence);
		theOccurence->incrementOccurenceCount();
	}
}
