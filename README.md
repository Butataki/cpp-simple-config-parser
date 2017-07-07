# cpp-simple-config-parser
Simple parser for configuration files

### Usage example
Config file:
```
iLine1
iOne=15
hHex=FFA

[section1]
iOne=45
fTestPArt=10.3405
iTest2=test
sSome=ssasd=sad=sad
bBool=trUe
bBool2=0
bBool3=1
bBool4=FaLse
sHost=http://127.0.0.1:8180
lList=value,value two, seconds,,seven,7
pPoint=10,2,t,0,45,12314141
vVec=45.456,23.5,34,344,u,0.1111
# comment
```

Code will be:
```cpp
#include <configparser.h>

Configuration conf = Configuration("test.cfg");
int one = conf.get_int_value("One");
cout << "Parameter \"One\" have value of " << one << endl;
int section_one = conf.get_int_value("One", "section1");
cout << "Parameter \"One\" from \"section1\" have value of " << section_one << endl;
int def_one = conf.get_int_value("AnotherOne");
cout << "Not present \"AnotherOne\" have default value of " << def_one << endl;
int nonex_section_one = conf.get_int_value("One", "section_nonex");
cout << "Parameter \"One\" from not existing section \"section_nonex\" have value of " << nonex_section_one << endl;
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
```
