#ifndef CPP_SIMPLE_CONFIG_PARSER_UTILS_H_
#define CPP_SIMPLE_CONFIG_PARSER_UTILS_H_
#include <vector>
#include <string>

namespace simple_config_parser { namespace utils {
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

}} // namespce simple_config_parser::utils
#endif // CPP_SIMPLE_CONFIG_PARSER_UTILS_H_
