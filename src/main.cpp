#include <iostream>
#include <vector>
#include <iterator>
#include <unistd.h>
#include <typeinfo>
#include "configparser.h"


//Example usage
int main() {
    Configuration conf = Configuration("test.cfg");
    Configuration * conf_ptr = new Configuration("test.cfg");
    char * name_ptr = getlogin();
    if (name_ptr) {
        std::cout << "user is " << name_ptr << std::endl;
    }
    int one_from_ptr = conf_ptr->get_int_value("One");
    std::cout << "ptr accressed Parameter \"One\" have value of " << one_from_ptr << std::endl;
    int one = conf.get_int_value("One");
    std::cout << "Parameter \"One\" have value of " << one << std::endl;
    int section_one = conf.get_int_value("One", "section1");
    std::cout << "Parameter \"One\" from \"section1\" have value of " << section_one << std::endl;
    int def_one = conf.get_int_value("AnotherOne");
    std::cout << "Not present \"AnotherOne\" have default value of " << def_one << std::endl;
    int nonex_section_one = conf.get_int_value("One", "section_nonex");
    std::cout << "Parameter \"One\" from not existsing section \"section_nonex\" have value of " << nonex_section_one << std::endl;
    float test_part = conf.get_float_value("TestPArt", "section1");
    std::cout << "Parameter \"TestPArt\" from \"section1\" have value of " << test_part << std::endl;
    std::string st = conf.get_string_value("Some", "section1");
    std::cout << "Parameter \"Some\" from \"section1\" have value of " << st << std::endl;
    std::vector<std::string> v_st = conf.get_string_vector_value("List", "section1");
    for(std::vector<std::string>::size_type i = 0; i != v_st.size(); i++) {
        std::cout << i << " position of parameter \"List\" from \"section1\" have value of " << v_st[i] << std::endl;
    }
    std::vector<int> v_in = conf.get_int_vector_value("Point", "section1");
    for(std::vector<int>::size_type i = 0; i != v_in.size(); i++) {
        std::cout << i << " position of parameter \"Point\" from \"section1\" have value of " << v_in[i] << std::endl;
    }
    if (conf_ptr) delete conf_ptr;
    return(1);
}
