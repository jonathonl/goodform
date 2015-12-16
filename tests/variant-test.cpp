#include <iostream>
#include <sstream>

#include "variant.hpp"
#include "msgpack.hpp"
#include "json.hpp"

using namespace std;

void fn(const goodform::variant& v)
{

}

int main(int argc, char** argv)
{

  std::int8_t eight = 8;
  goodform::variant v("cstring");
  cout << (int)v.type() << endl;
  goodform::variant v2(std::string("std::string"));
  cout << (int)v2.type() << endl;
  v2 = "foobar";
  cout << (int)v2.type() << endl;

  cout << v2.get_string() << endl;

  goodform::variant v3;
  std::string foo;
  v3[2] = "Test";
  if (v3[2].get(foo))
  {
    cout << v3[0].get_string() << endl;
    cout << v3[2].get_string() << endl;
    cout << foo << endl;
  }


  fn(nullptr);
  fn("");
  fn(std::string("b"));


  {
    goodform::variant var1, var2;
    var1 = goodform::object{{"foo", "bar"}};
    std::stringstream ss;
    goodform::msgpack::serialize(var1, ss);
    goodform::msgpack::deserialize(ss, var2);
  }

  {
    goodform::variant var1, var2;
    var1 = goodform::object{{"foo", "bar"}};
    std::stringstream ss;
    goodform::json::serialize(var1, ss);
    goodform::json::deserialize(ss, var2);
  }





  return 0;
}