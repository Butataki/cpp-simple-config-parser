#ifndef UTILS_H_INCLUDED_
#define UTILS_H_INCLUDED_
#include <vector>
#include <string>

/**
@fn split
@brief Split string by delimeter into string vector.

@param constant string target - string to split.
@param constant chracter delimeter - character to split target by.
@return string vector of splited strings.
*/
std::vector<std::string> split(const std::string & target, const char & delimeter);

/**
@fn join
@brief Join vector of strings into one sting.

@param vector string target - vector to join.
@param constant characer delimeter - concatenate vector values with this character.
@return joined string
*/
std::string join(std::vector<std::string>& target,  const char& delimeter);

#endif
