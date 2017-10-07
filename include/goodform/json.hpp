#pragma once
#ifndef GOODFORM_JSON_HPP
#define GOODFORM_JSON_HPP

#include <iostream>
#include <iterator>

#include "variant.hpp"

//######################################################################//
namespace goodform
{
  //**********************************************************************//
  class json
  {
  private:
    json() = delete;
    //static bool deserializeobject();

    static void write_string(const std::string& input, std::ostream& output);
    static void stringify_object(const any& v, std::ostream& output);
    static void stringify_array(const any& v, std::ostream& output);

    static char parse_escaped_char(char input);
    static void strip_white_space(std::istream& input);
    static int convert_hex_to_dec(char input);

    static bool parse_array(std::istream& input, any& v);
    static bool parse_object(std::istream& input, any& v);
    static bool read_string(std::istream& input, std::string& s);
  public:
    static void serialize(const any& v, std::ostream& output);
    static bool deserialize(std::istream& input, any& v);
  };
}

#endif //GOODFORM_JSON_HPP