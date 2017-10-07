#include <iostream>
#include <sstream>
#include <limits>
#include <list>

#include "goodform/variant.hpp"
#include "goodform/form.hpp"
#include "goodform/msgpack.hpp"
#include "goodform/json.hpp"

#include <cmath>
#include <cstdlib>

bool run_msgpack_example()
{
  std::stringstream ss;
  goodform::any var, var2;
  var = goodform::object_t
    {
      {"compact", true},
      {"schema", 0}
    };

  goodform::msgpack::serialize(var, ss);
  goodform::msgpack::deserialize(ss, var2);

  goodform::form form(var2);

  struct
  {
    bool compact;
    std::int32_t schema;
  } mpack;

  mpack.compact = form.at("compact").boolean().val();
  mpack.schema = form.at("schema").int32().val();

  if (form.is_good())
  {
    std::cout << "{ \"compact\": " << std::boolalpha << mpack.compact << ", \"schema\": " << mpack.schema << " }" << std::endl;
    std::cout << "MsgPack Passed." << std::endl;
    return true;
  }

  std::cerr << "MsgPack Passed." << std::endl;
  return false;
}

bool run_json_example()
{
  goodform::any var;
  std::stringstream ss;
  ss << "{" << std::endl
     << "\"first_name\":\"John\", // This is a comment" << std::endl
     << "\"last_name\":\"Smith\", " << std::endl
     << "\"age\": 23," << std::endl
     << "\"gpa\": 4.0," << std::endl
     << "\"email\":\"john.smith@example.com\"," << std::endl
     << "\"password_hash\":\"5f4dcc3b5aa765d61d8327deb882cf99\"," << std::endl
     << "\"interests\": [\"sailing\",\"swimming\",\"yoga\"]" << std::endl
     << "}" << std::endl;

  goodform::json::deserialize(ss, var);

  goodform::form form(var);

  struct
  {
    std::string first_name;
    std::string last_name;
    std::uint8_t age;
    float gpa;
    std::string email;
    std::string password_hash;
    bool subscribe_to_email_marketing;
    std::list<std::string> interests;
  } form_data;


  form_data.first_name = form.at("first_name").string().match(std::regex("^[a-zA-Z ]{1,64}$")).val();
  form_data.last_name = form.at("last_name").string().match(std::regex("^[a-zA-Z ]{1,64}$")).val();
  form_data.age = form.at("age").uint8().val();
  form_data.gpa = form.at("gpa").float32().gte(0).lte(4.0).val();
  form_data.email = form.at("email").string().match(std::regex("^.{3,256}$")).val();
  form_data.password_hash = form.at("password_hash").string().match(std::regex("^[a-fA-F0-9]{32}$")).val();
  form_data.subscribe_to_email_marketing = form.at("subscribe_to_email_marketing", true).boolean().val(); // Optional field defaults to true.

  form.at("interests").array().for_each([&form_data](goodform::sub_form& sf, std::size_t i)
  {
    form_data.interests.push_back(sf.string().val());
  });




  if (!form.is_good())
  {
    std::cerr << "JSON FAILED!" << std::endl;
    return false;
  }

  std::cout << "JSON passed." << std::endl;
  return true;
}

bool run_simple_msgpack_test()
{
  std::stringstream ss;
  goodform::any var, var2;
  var = goodform::object_t
    {
      {"bool", true},
      {"int8", std::int8_t(-8)},
      {"int16", std::int8_t(-16)},
      {"int32", std::int8_t(-32)},
      {"int64", std::int8_t(-64)},
      {"uint8", std::uint8_t(8)},
      {"uint16", std::uint8_t(16)},
      {"uint32", std::uint8_t(32)},
      {"uint64", std::uint8_t(64)},
      {"string", std::string("sting value")}
    };

  goodform::msgpack::serialize(var, ss);
  goodform::msgpack::deserialize(ss, var2);

  goodform::form form(var2);

  struct
  {
    bool          boolean;
    std::int8_t   int8;
    std::int16_t  int16;
    std::int32_t  int32;
    std::int64_t  int64;
    std::uint8_t  uint8;
    std::uint16_t uint16;
    std::uint32_t uint32;
    std::uint64_t uint64;
    std::string   str;
  } form_data {
    form.at("bool").boolean().val(),
    form.at("int8").int8().val(),
    form.at("int16").int16().val(),
    form.at("int32").int32().val(),
    form.at("int64").int64().val(),
    form.at("uint8").uint8().val(),
    form.at("uint16").uint16().val(),
    form.at("uint32").uint32().val(),
    form.at("uint64").uint64().val(),
    form.at("string").string().val()
  };

  if (!form.is_good())
  {
    std::cerr << "Simple MsgPack FAILED!" << std::endl;
    return false;
  }

  if (!form_data.boolean
    || form_data.int8 != -8
    || form_data.int16 != -16
    || form_data.int32 != -32
    || form_data.int64 != -64
    || form_data.uint8 != 8
    || form_data.uint16 != 16
    || form_data.uint32 != 32
    || form_data.uint64 != 64
    || form_data.str != "sting value")
  {
    std::cerr << "Simple MsgPack FAILED!" << std::endl;
    return false;
  }


  std::cout << "Simple MsgPack passed." << std::endl;
  return true;
}

int main(int argc, char** argv)
{

  if (argc > 1)
  {
    std::string test_name = argv[1];
    if (test_name == "example")
      return (run_json_example() && run_msgpack_example() ? EXIT_SUCCESS : EXIT_FAILURE);
    else if (test_name == "simple")
      return (run_simple_msgpack_test() ? EXIT_SUCCESS : EXIT_FAILURE);
  }

  return EXIT_FAILURE;
}