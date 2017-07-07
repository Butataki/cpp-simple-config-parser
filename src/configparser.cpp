#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "configparser.h"
#include "utils.h"
using namespace std;

const unsigned char INT_ID_SYMBOL = 'i';
const unsigned char INT_HEX_ID_SYMBOL = 'h';
const unsigned char FLOAT_ID_SYMBOL = 'f';
const unsigned char STR_ID_SYMBOL = 's';
const unsigned char BOOL_ID_SYMBOL = 'b';
const unsigned char STR_VECTOR_ID_SYMBOL = 'l';
const unsigned char INT_VECTOR_ID_SYMBOL = 'p';
const unsigned char FLOAT_VECTOR_ID_SYMBOL = 'v';

/**
Try to open configuration file for read,
if successfull pass path to parse method.
*/
Configuration::Configuration(const char * path){
    FILE *config_file_pointer = fopen(path, "r");
    if (config_file_pointer) {
        this->parse(path);
        fclose(config_file_pointer);
    } else {
        cerr << "Failed to open " << path << endl;
    }
};

/**
Typecast raw string value to apropriate parameter type and add to type
storage.
*/
void Configuration::cast_parameter(string& name, string& raw_value, string& section){
    string::size_type sz;
    unsigned char parameter_symbol = name.front();
    string parameter_name = name.substr(1, name.size());
    vector<string> raw_split_value;
    vector<int> int_vector_value;
    vector<float> float_vector_value;
    parameter<int> ip;
    parameter<int> hip;
    parameter<float> fp;
    parameter<string> sp;
    parameter<bool> bp;
    parameter<vector<string>> lp;
    parameter<vector<int>> pp;
    parameter<vector<float>> vp;

    // depending on first symbol cast type of a parameter
    switch(parameter_symbol){
        case INT_ID_SYMBOL:
            ip.name = parameter_name;
            ip.section = section;
            try {
                ip.value = stoi(raw_value, &sz, 10);
            } catch (invalid_argument &e) {
                ip.value = 0;
                cerr << raw_value << " is invalid argument for " << e.what() << endl;
                break;
            }
            this->int_parameter_storage.push_back(ip);
            break;
        case INT_HEX_ID_SYMBOL:
            hip.name = parameter_name;
            hip.section = section;
            try {
                hip.value = stoi(raw_value, &sz, 16);
            } catch (invalid_argument &e) {
                hip.value = 0;
                cerr << raw_value << " is invalid argument for " << e.what() << endl;
                break;
            }
            this->int_parameter_storage.push_back(hip);
            break;
        case FLOAT_ID_SYMBOL:
            fp.name = parameter_name;
            fp.section = section;
            try {
                fp.value = stod(raw_value, &sz);
            } catch (invalid_argument &e) {
                ip.value = 0.0;
                cerr << raw_value << " is invalid argument for " << e.what() << endl;
                break;
            }
            this->float_parameter_storage.push_back(fp);
            break;
        case STR_ID_SYMBOL:
            sp.name = parameter_name;
            sp.section = section;
            sp.value = raw_value;
            this->string_parameter_storage.push_back(sp);
            break;
        case BOOL_ID_SYMBOL:
            transform(raw_value.begin(), raw_value.end(), raw_value.begin(), ::tolower);
            bool b;
            istringstream(raw_value) >> std::boolalpha >> b;
            bp.name = parameter_name;
            bp.section = section;
            bp.value = b;
            this->bool_parameter_storage.push_back(bp);
            break;
        case STR_VECTOR_ID_SYMBOL:
            raw_split_value = split(raw_value, ',');
            lp.name = parameter_name;
            lp.section = section;
            lp.value = raw_split_value;
            this->string_vector_parameter_storage.push_back(lp);
            break;
        case INT_VECTOR_ID_SYMBOL:
            raw_split_value = split(raw_value, ',');
            for(vector<string>::size_type i = 0; i != raw_split_value.size(); i++) {
                try {
                    int_vector_value.push_back(stoi(raw_split_value[i], &sz, 10));
                } catch (invalid_argument &e) {
                    int_vector_value.push_back(0);
                    cerr << i << " position of " << raw_value << " is invalid argument for " << e.what() << endl;
                }
            }
            pp.name = parameter_name;
            pp.section  = section;
            pp.value = int_vector_value;
            this->int_vector_parameter_storage.push_back(pp);
            break;
        case FLOAT_VECTOR_ID_SYMBOL:
            raw_split_value = split(raw_value, ',');
            for(vector<string>::size_type i = 0; i != raw_split_value.size(); i++) {
                try {
                    float_vector_value.push_back(stod(raw_split_value[i], &sz));
                } catch (invalid_argument &e) {
                    float_vector_value.push_back(0.0f);
                    cerr << i << " position of " << raw_value << " is invalid argument for " << e.what() << endl;
                }
            }
            vp.name = parameter_name;
            vp.section  = section;
            vp.value = float_vector_value;
            this->float_vector_parameter_storage.push_back(vp);
            break;
        default:
            cerr << parameter_name << " have unsuported first symbol" << endl;
            break;
    }
};

/**
Read configuration file line by line and transform
strings to parameter name and value.
*/
void Configuration::parse(const char * path) {
    ifstream infile(path);
    string line;
    string current_section = "";
    string param_name;
    string raw_value;
    vector<string> raw_parameter;
    vector<string>::size_type raw_parameter_size = raw_parameter.size();
    const char split_parameter_delimiter = '=';


    while (std::getline(infile, line)){
        // reset name and value at each line
        param_name = "";
        raw_value = "";
        // skip empty lines and comments
        if(line.empty() or line[0] == '#')
            continue;
        // process sections
        if(line[0] == '[' and line.back() == ']') {
            current_section = line.substr(1, line.size() - 2);
            this->section_storage.push_back(current_section);
            continue;
        }
        // process names and values
        raw_parameter = split(line, split_parameter_delimiter);
        raw_parameter_size = raw_parameter.size();
        // if split vector empty
        if (raw_parameter_size == 0)
            continue;
        // if right part empty take only name
        if (raw_parameter_size == 1){
            param_name = raw_parameter[0];
            raw_value = "";
        }
        // if splited succesfully take first as name and splited as value
        if (raw_parameter_size == 2)  {
            param_name = raw_parameter[0];
            raw_value = raw_parameter[1];
        }
        // if `=` in parameter value join it all back
        if (raw_parameter_size > 2)  {
            param_name = raw_parameter[0];
            raw_parameter.erase(raw_parameter.begin());
            raw_value = join(raw_parameter, split_parameter_delimiter);
        }
        // cast parameter by type symbol
        this->cast_parameter(param_name, raw_value, current_section);
    }
};

/**
Cycle through integer parameters storage and return first found match or default value.
*/
int Configuration::get_int_value(string name, string section, int default_value) {
    for(vector<parameter<int>>::size_type i = 0; i != this->int_parameter_storage.size(); i++) {
        parameter<int> _p =  this->int_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Cycle through float parameters storage and return first found match or default value.
*/
float Configuration::get_float_value(string name, string section, float default_value){
    for(vector<parameter<float>>::size_type i = 0; i != this->float_parameter_storage.size(); i++) {
        parameter<float> _p =  this->float_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Cycle through string parameters storage and return first found match or default value.
*/
string Configuration::get_string_value(string name, string section, string default_value){
    for(vector<parameter<string>>::size_type i = 0; i != this->string_parameter_storage.size(); i++) {
        parameter<string> _p =  this->string_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Cycle through booelan parameters storage and return first found match or default value.
*/
bool Configuration::get_boolean_value(string name, string section, bool default_value){
    for(vector<parameter<bool>>::size_type i = 0; i != this->bool_parameter_storage.size(); i++) {
        parameter<bool> _p =  this->bool_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Cycle through integer vector parameters storage and return first found match or default value.
*/
vector<int> Configuration::get_int_vector_value(string name, string section, vector<int> default_value){
    for(vector<parameter<vector<int>>>::size_type i = 0; i != this->int_vector_parameter_storage.size(); i++) {
        parameter<vector<int>> _p =  this->int_vector_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Cycle through float vector parameters storage and return first found match or default value.
*/
vector<float> Configuration::get_float_vector_value(string name, string section, vector<float> default_value){
    for(vector<parameter<vector<float>>>::size_type i = 0; i != this->float_vector_parameter_storage.size(); i++) {
        parameter<vector<float>> _p =  this->float_vector_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Cycle through string vector parameters storage and return first found match or default value.
*/
vector<string> Configuration::get_string_vector_value(string name, string section, vector<string> default_value){
    for(vector<parameter<vector<string>>>::size_type i = 0; i != this->string_vector_parameter_storage.size(); i++) {
        parameter<vector<string>> _p =  this->string_vector_parameter_storage[i];
        if (_p.name == name and _p.section == section)
            return _p.value;
    }
    return default_value;
};

/**
Return section_storage private varaiable;
*/
vector<string> Configuration::get_sections(void){
    return this->section_storage;
};
