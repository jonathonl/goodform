#include <iostream>
#include <sstream>
#include <limits>

#include "variant.hpp"
#include "form.hpp"
#include "msgpack.hpp"
#include "json.hpp"

using namespace std;
using namespace goodform;

void fn(const goodform::variant& v)
{
  auto a = v[0].get<std::string>();
}

int main(int argc, char** argv)
{

  std::int8_t eight = 8;
  variant v("cstring");
  cout << (int)v.type() << endl;
  variant v2(std::string("std::string"));
  cout << (int)v2.type() << endl;
  v2 = "foobar";
  cout << (int)v2.type() << endl;

  cout << v2.get_string() << endl;

  variant v3;
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
    variant var1, var2;
    var1 = object{{"foo", "bar"}};
    std::stringstream ss;
    msgpack::serialize(var1, ss);
    msgpack::deserialize(ss, var2);
  }

  {
    variant var1, var2;
    var1 = object{{"foo", "bar"},{"foo","baz"}};
    std::stringstream ss;
    json::serialize(var1, ss);
    json::deserialize(ss, var2);
  }

  {
    variant var;
    std::stringstream ss;
    ss << "{" << std::endl
      << "\"foo\":\"bar\", // This is a comment         " << std::endl
      << "  //This is a nother comment" << std::endl
      << "\"bar\":\"barman\",        " << std::endl
      << "\"fooman\":12395" << std::endl
      << "}" << std::endl;
    json::deserialize(ss, var);
    fn(var);
    form f(var);

    struct
    {
      std::string foo;
      std::string bar;
      short fooman;
    } form_data;
    form_data.foo = f.object().at("foo").string().val();
    form_data.bar = f.object().at("bar").string().match(std::regex("^b.*$")).val();
    form_data.fooman = (short)f.object().at("fooman").number().gt(0).lte(std::numeric_limits<short>::max()).val();


    if (f.is_good())
    {
      // Use form_data.
      auto a = form_data.fooman;
    }
    else
    {
      // Invalid form.
      auto b = 0;
    }

  }


  return 0;
}