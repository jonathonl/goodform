#include <iostream>
#include <sstream>
#include <limits>

#include "variant.hpp"
#include "form.hpp"
#include "msgpack.hpp"
#include "json.hpp"

using namespace std;
using namespace goodform;

int main(int argc, char** argv)
{


  {
    bool passed = false;
    variant var1, var2;
    var1 = object{
      {"compact", true},
      {"schema", 0}};

    std::stringstream ss;
    msgpack::serialize(var1, ss);
    msgpack::deserialize(ss, var2);

    if (var2.is<object>())
    {
      if (var2["compact"].is<bool>()
        && var2["compact"].get<bool>() == true
        && var2["schema"].is<std::int32_t>()
        && var2["schema"].get<std::int32_t>() == 0)
      {
        passed = true;
      }
    }

    std::cout << "MsgPack " << (passed ? "Passed." : "FAILED!") << std::endl;
  }

  {
    variant var;
    std::stringstream ss;
    ss << "{" << std::endl
      << "\"str\":\"a string\", // This is a comment         " << std::endl
      << "  //This is a nother comment" << std::endl
      << "\"ui8\":221     ,   " << std::endl
      << "\"i8\":-99," << std::endl
      << "\"ui16\":26721,   " << std::endl
      << "\"i16\":-13672," << std::endl
      << "\"ui32\":26721," << std::endl
      << "\"i32\":-13672," << std::endl
      << "\"ui64\":26721," << std::endl
      << "\"i64\":-13672," << std::endl
      << "\"real\":0.989876," << std::endl
      << "\"bin\": null," << std::endl
      << "\"dreal\":10.00001," << std::endl
      << "\"arr\": [\"a\",\"b\",   \"c\"  ]," << std::endl
      << "\"boolean\": false ," << std::endl
      << "}" << std::endl;
    json::deserialize(ss, var);

    form f(var);

    struct
    {
      bool boolean;

      std::uint8_t ui8;
      std::int8_t i8;

      std::uint16_t ui16;
      std::int16_t i16;

      std::uint32_t ui32;
      std::int32_t i32;

      std::uint64_t ui64;
      std::int64_t i64;

      float real;
      double dreal;

      std::string str;
      std::vector<unsigned char> bin;

      std::vector<std::string> arr;
      object obj;
    } form_data;

    form_data.boolean = f.object().at("boolean").boolean().val();
    form_data.ui8 = (std::uint8_t)f.object().at("ui8").number().gte(0).lte(std::numeric_limits<std::uint8_t>::max()).val();
    form_data.i8 = (std::int8_t)f.object().at("i8").number().gte(std::numeric_limits<std::int8_t>::min()).lte(std::numeric_limits<std::int8_t>::max()).val();
    
    form_data.ui16 = (std::uint16_t)f.object().at("ui16").number().gte(0).lte(std::numeric_limits<std::uint16_t>::max()).val();
    form_data.i16 = (std::int16_t)f.object().at("i16").number().gte(std::numeric_limits<std::int16_t>::min()).lte(std::numeric_limits<std::int16_t>::max()).val();

    form_data.ui32 = (std::uint32_t)f.object().at("ui32").number().gte(0).lte(std::numeric_limits<std::uint32_t>::max()).val();
    form_data.i32 = (std::int32_t)f.object().at("i32").number().gte(std::numeric_limits<std::int32_t>::min()).lte(std::numeric_limits<std::int32_t>::max()).val();

    form_data.ui64 = (std::uint64_t)f.object().at("ui64").number().gte(0).lte(std::numeric_limits<std::uint64_t>::max()).val();
    form_data.i64 = (std::int64_t)f.object().at("i64").number().gte(std::numeric_limits<std::int64_t>::min()).lte(std::numeric_limits<std::int64_t>::max()).val();

    form_data.real = (float)f.object().at("real").number().gte(std::numeric_limits<float>::min()).lte(std::numeric_limits<float>::max()).val();
    form_data.dreal = f.object().at("dreal").number().gte(10).lt(11).val();
    
    form_data.str = f.object().at("str").string().match(std::regex("^a.*$")).val();
    f.object().at("bin");

    f.object().at("arr").array().for_each([&form_data](sub_form& sf, std::size_t i)
    {
      form_data.arr.push_back(sf.string().val());
    });




    if (f.is_good())
    {
      std::cout << "JSON passed." << std::endl;
    }
    else
    {
      std::cout << "JSON FAILED!" << std::endl;
    }

  }


  return 0;
}