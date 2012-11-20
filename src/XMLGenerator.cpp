#include <iostream>
#include <fstream>
#include "XMLGenerator.h"
#include "StopWords.h"
#include "StringUtil.h"

using namespace std;

//Constructor
XMLGenerator::XMLGenerator(string _startURL, WordList & _MasterWordList,
		BST<Page> & _PageHistory, string _outputFile, string _stopWordFile):
			startURL(_startURL), MasterWordList(_MasterWordList), PageHistory(_PageHistory),
				outputFile(_outputFile), stopWordFile(_stopWordFile)
{
}

XMLGenerator::~XMLGenerator()
{
}

//Print the entire file
void XMLGenerator::printFile()
{
	ofstream output(outputFile.c_str());
	printPages(output);
	printWords(output);
}

//Print all pages to output
void XMLGenerator::printPages(ofstream & output)
{
	output << "<website>" << endl;
	output << "<start-url>" << endl;
		output << startURL << endl;
	output << "</start-url>" << endl;
	output << "<pages>" << endl;
	LinkedList<Page> * pages = PageHistory.GetList();
	while(pages->GetSize() > 0)
	{
		LLNode<Page> * tempNode = pages->GetFirst();
		output << "<page>" << endl;
			output << "<url>";
				output << tempNode->GetValueNonConst().getURL().getURL();
			output << "</url>" << endl;
			output << "<description>";
				output << StringUtil::EncodeToXmlCopy(tempNode->GetValueNonConst().GetDescription());
			output << "</description>"  << endl;
		output << "</page>" << endl;;
		pages->Remove(tempNode);
	}
	output << "</pages>" << endl;
	delete pages;
}

//Print all words to output
void XMLGenerator::printWords(ofstream & output)
{
	//Print out all words found, besides stopwords.
	output << "<index>" << endl;

	StopWords stopwords(stopWordFile);
	LinkedList<Word> * words = MasterWordList.getWords()->GetList();
	while(words->GetSize() > 0)
	{
		LLNode<Word> * tempWord = words->GetFirst();

		//Check to make sure stopwords are not included in the output file.
		if(!stopwords.IsStopWord(tempWord->GetValueNonConst().getValue()) && tempWord->GetValueNonConst().getValue() != "z")
		{
			//Print out valid XML.
			output << "<word>" << endl;
				output << "<value>";
					output << tempWord->GetValueNonConst().getValue();
				output << "</value>" << endl;

				LinkedList<Occurence> * occurences = tempWord->GetValueNonConst().getOccurences()->GetList();
				while(occurences->GetSize() > 0)
				{
					LLNode<Occurence> * tempOccurrence = occurences->GetFirst();
					output << "<occurrence>" << endl;;
						output << "<url>";
							output << tempOccurrence->GetValueNonConst().getURL().getURL();
						output << "</url>" << endl;
						output << "<count>";
							output << tempOccurrence->GetValueNonConst().getOccurenceCount();
						output << "</count>" << endl;;
					output << "</occurrence>" << endl;
					occurences->Remove(tempOccurrence);
				}
				delete occurences;
			output << "</word>" << endl;
		}
		words->Remove(tempWord);
	}
	delete words;
	output << "</index>" << endl;
	output << "</website>" << endl;
}
