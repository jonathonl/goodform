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
}
else
{
  // Invalid form.
}
```