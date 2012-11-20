#include "URL.h"

URL::URL(string _incomingURL)
{
	url = _incomingURL;
}

URL::URL()
{
}

bool URL::operator== (const URL & other) const
{
	if(url == other.url)
		return true;
	return false;
}

bool URL::operator> (const URL & other) const
{
	if(url > other.url)
		return true;
	return false;
}

bool URL::operator< (const URL & other) const
{
	if(url < other.url)
		return true;
	return false;
}

string URL::ResolveRelative(string _relativeURL)
{
	return "";
}


//TEST CASES FOR MY URL
bool URL::Test(ostream & os)
{
	return false;
}


