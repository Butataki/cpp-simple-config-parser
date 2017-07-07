#ifndef UTILS_H_INCLUDED_
#define UTILS_H_INCLUDED_
#include <vector>
#include <string>
using namespace std;

/**
@fn split
@brief Split string by delimeter into string vector.

@param constant string target - string to split.
@param constant chracter delimeter - character to split target by.
@return string vector of splited strings.
*/
vector<string> split(const string& target, const char& delimeter);

/**
@fn join
@brief Join vector of strings into one sting.

@param vector string target - vector to join.
@param constant characer delimeter - concatenate vector values with this character.
@return joined string
*/
string join(vector<string>& target,  const char& delimeter);

#endif
