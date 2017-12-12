#include <vector>
#include <string>
#include <sstream>
#include "simple_config_parser/utils.h"

/**
Traverse string by characters and build vector
result if delimeter is encountered.
*/
std::vector<std::string> simple_config_parser::utils::split(
    const std::string &target,
    const char &delimeter
) {
    std::string part;
    std::vector<std::string> result;

    for (std::string::const_iterator it = target.begin(); it != target.end(); it++) {
        // If we've hit the terminal character
        if (*it == delimeter) {
            // If we have some characters accumulated
            if (!part.empty()) {
                // Add them to the result vector
                result.push_back(part);
                part.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            part += *it;
        }
    }
    if (!part.empty())
         result.push_back(part);
    return result;
};

/**
Traverse vector target and send values to string stream.
*/
std::string simple_config_parser::utils::join(
    std::vector<std::string> &target, const char &delimeter
){
    std::string result;
    std::stringstream stream;

    for(size_t i = 0; i < target.size(); ++i) {
        if(i != 0)
            stream << delimeter;
        stream << target[i];
    }
    result = stream.str();
    return result;
};
