#include <vector>
#include <string>
#include <sstream>
#include "utils.h"
using namespace std;

/**
Traverse string by characters and build vector
result if delimeter is encountered.
*/
vector<string> split(const string& target, const char& delimeter) {
    string part;
    vector<string> result;

    for (string::const_iterator it = target.begin(); it != target.end(); it++) {
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
string join(vector<string>& target, const char& delimeter){
    string result;
    stringstream stream;

    for(size_t i = 0; i < target.size(); ++i) {
        if(i != 0)
            stream << delimeter;
        stream << target[i];
    }
    result = stream.str();
    return result;
};
