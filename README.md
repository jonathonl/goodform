# GoodForm
Form validation library. Includes MsgPack and JSON serializer/deserializer.

#Usage
```c++
using namsepace goodform;
    
variant var;
std::stringstream s;
s << "{" << std::endl
  << "\"foo\":\"bar\"," << std::endl
  << "\"bar\":\"barman\"," << std::endl
  << "\"fooman\":12395" << std::endl
  << "}" << std::endl;
  
json::deserialize(ss, var);
form f(var);

struct
{
  std::string foo;
  std::string bar;
  std::int16_t fooman;
} form_data;
form_data.foo = f.at("foo").string().val();
form_data.bar = f.at("bar").string().match(std::regex("^b.*$")).val();
form_data.fooman = f.at("fooman").int16().gt(0).val();

if (f.is_good())
{
  // Use form_data.
}
else
{
  // Invalid form.
}
```