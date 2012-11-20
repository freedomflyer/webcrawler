#include "Occurence.h"

using namespace std;

Occurence::Occurence(URL _url):url(_url)
{
	occurenceCount = 1;
}
Occurence::Occurence(const Occurence &o)
{
	occurenceCount = o.occurenceCount;
	url = o.url;
}

URL Occurence::getURL()
{
	return url;
}

int Occurence::getOccurenceCount()
{
	return occurenceCount;
}

void Occurence::incrementOccurenceCount()
{
	occurenceCount++;
}

bool Occurence::operator==(const Occurence & other)  const
{
	return(url == other.url);
}

bool Occurence::operator<(const Occurence & other)  const
{
	return(url < other.url);
}

bool Occurence::operator>(const Occurence & other)  const
{
	return(url > other.url);
}
