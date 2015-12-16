#pragma 1
#ifndef GOODFORM_MSGPACK_HPP
#define GOODFORM_MSGPACK_HPP

#include <iostream>
#include <iterator>

#include "variant.hpp"

//######################################################################//
namespace goodform
{
  //**********************************************************************//
  class msgpack
  {
  private:
    msgpack() = delete;
    //static bool deserializeobject();

  public:
    static bool serialize(const variant& v, std::ostream& output);
    static bool deserialize(std::istream& input, variant& v);
  };
}

#endif //GOODFORM_MSGPACK_HPP