#include <iostream>
#include <vector>
#include <iterator>
#include <unistd.h>
#include <typeinfo>
#include "configparser.h"
using namespace std;

//Example usage
int main() {
    Configuration conf = Configuration("test.cfg");
    Configuration * conf_ptr = new Configuration("test.cfg");
    char * name_ptr = getlogin();
    if (name_ptr) {
        cout << "user is " << name_ptr << endl;
    }
    int one_from_ptr = conf_ptr->get_int_value("One");
    cout << "ptr accressed Parameter \"One\" have value of " << one_from_ptr << endl;
    int one = conf.get_int_value("One");
    cout << "Parameter \"One\" have value of " << one << endl;
    int section_one = conf.get_int_value("One", "section1");
    cout << "Parameter \"One\" from \"section1\" have value of " << section_one << endl;
    int def_one = conf.get_int_value("AnotherOne");
    cout << "Not present \"AnotherOne\" have default value of " << def_one << endl;
    int nonex_section_one = conf.get_int_value("One", "section_nonex");
    cout << "Parameter \"One\" from not existsing section \"section_nonex\" have value of " << nonex_section_one << endl;
    float test_part = conf.get_float_value("TestPArt", "section1");
    cout << "Parameter \"TestPArt\" from \"section1\" have value of " << test_part << endl;
    string st = conf.get_string_value("Some", "section1");
    cout << "Parameter \"Some\" from \"section1\" have value of " << st << endl;
    vector<string> v_st = conf.get_string_vector_value("List", "section1");
    for(vector<string>::size_type i = 0; i != v_st.size(); i++) {
        cout << i << " position of parameter \"List\" from \"section1\" have value of " << v_st[i] << endl;
    }
    vector<int> v_in = conf.get_int_vector_value("Point", "section1");
    for(vector<int>::size_type i = 0; i != v_in.size(); i++) {
        cout << i << " position of parameter \"Point\" from \"section1\" have value of " << v_in[i] << endl;
    }
    if (conf_ptr) delete conf_ptr;
    return(1);
}
