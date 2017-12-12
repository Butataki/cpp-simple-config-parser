#ifndef CPP_SIMPLE_CONFIG_PARSER_PARSER_H_
#define CPP_SIMPLE_CONFIG_PARSER_PARSER_H_
#include <iostream>
#include <vector>
#include <string>

namespace simple_config_parser { namespace parser {
    /** @struct parameter
        @brief Structure for config parameter.

        Store parameter data for easy access.
        Made as template to support diffrent types of values.
    */
    template <typename T>
    struct parameter {
        std::string name; /**< string pramater name. */
        std::string section; /**< string parameter section name. */
        T value;  /**< templated type for parameter value. */
        parameter() = default;
    };

    /** @class Configuration
        @brief A class for configuration.

        Parse configuration file and access casted values.
    */
    class Configuration {
        public:
            Configuration();
            /**
            A constructor. Construct configuration object.
            @param path a constant character pointer - path to configuration file to parse.
            */
            Configuration(const char* path);
            /**
            Public method to aquire integer parameter from config.
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an integer - default value to return if parameter is not found, default is 0
            @return integer value of a parameter or default_value
            */
            int get_int_value(
                std::string name,
                std::string section="",
                int default_value=0
            );
            /**
            Public method to aquire float parameter from config.
            @see get_int_value()
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an float - default value to return if parameter is not found, default is 0.0f
            @return float value of a parameter or default_value
            */
            float get_float_value(
                std::string name,
                std::string section="",
                float default_value=0.0f
            );
            /**
            Public method to aquire string parameter from config.
            @see get_int_value()
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an string - default value to return if parameter is not found, default is empty string
            @return string value of a parameter or default_value
            */
            std::string get_string_value(
                std::string name,
                std::string section="",
                std::string default_value=""
            );
            /**
            Public method to aquire boolean parameter from config.
            Supported string values as "true" for true and anything else is false.
            @see get_int_value()
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an bool - default value to return if parameter is not found, default is false
            @return booelan value of a parameter or default_value
            */
            bool get_boolean_value(
                std::string name,
                std::string section="",
                bool default_value=false
            );
            /**
            Public method to aquire vector of integers parameter from config.
            @see get_int_value()
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an integer vector - default value to return if parameter is not found, default is empty integer vector
            @return integer vector value of a parameter or default_value
            */
            std::vector<int> get_int_vector_value(
                std::string name,
                std::string section="",
                std::vector<int> default_value=std::vector<int>()
            );
            /**
            Public method to aquire float vector parameter from config.
            @see get_int_vector_value()
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an float vector - default value to return if parameter is not found, default is empty float vector
            @return float vector value of a parameter or default_value
            */
            std::vector<float> get_float_vector_value(
                std::string name,
                std::string section="",
                std::vector<float> default_value=std::vector<float>()
            );
            /**
            Public method to aquire string vector parameter from config.
            @see get_int_vector_value()
            @param name a string - parameter names
            @param section a string - section name, default is empty string if config have no sections
            @param default_value an string vector - default value to return if parameter is not found, default is empty string vector
            @return string vector value of a parameter or default_value
            */
            std::vector<std::string> get_string_vector_value(
                std::string name,
                std::string section="",
                std::vector<std::string>
                default_value=std::vector<std::string>()
            );
            /**
            Public method get sorted list of sections names
            @return string vector of sections in configuration file
            */
            std::vector<std::string> get_sections();

        private:
            /**
            A private variable int_parameter_storage.
            Stores integer parameters.
            */
            std::vector<parameter<int>> int_parameter_storage;
            /**
            A private variable string_parameter_storage.
            Stores string parameters.
            */
            std::vector<parameter<std::string>> string_parameter_storage;
            /**
            A private varaiable float_parameter_storage.
            Stores float parameters.
            */
            std::vector<parameter<float>> float_parameter_storage;
            /**
            A private variable bool_parameter_storage.
            Stores boolean parameters.
            */
            std::vector<parameter<bool>> bool_parameter_storage;
            /**
            A private varaible int_vector_parameter_storage.
            Stores integer vector parameters.
            */
            std::vector<parameter<std::vector<int>>> int_vector_parameter_storage;
            /**
            A private varaiable float_vector_parameter_storage.
            Stores float vector parameters.
            */
            std::vector<parameter<std::vector<float>>> float_vector_parameter_storage;
            /**
            A private varaiable  string_vector_parameter_storage.
            Stores string vector parameters.
            */
            std::vector<parameter<std::vector<std::string>>> string_vector_parameter_storage;
            /**
            A private varaiable section_storage.
            Stores configuration sections names.
            */
            std::vector<std::string> section_storage;
            /**
            A private method that parses configuration file.
            @param a constant character pointer path - path to configuration file.
            @return void
            */
            void parse(const char * path);
            /**
            A private method typecasts parsed strings from commfiguration file.
            @param string name - parameter name.
            @param string raw_value - string value parsed from file.
            @param strin section - section name
            @return void
            */
            void cast_parameter(
                std::string & name,
                std::string & raw_value,
                std::string & section
            );
    };
}} // namespace simple_config_parser::parser
#endif //CPP_SIMPLE_CONFIG_PARSER_PARSER_H_
