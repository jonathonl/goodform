#MsgPack Usage
```c++
using namsepace goodform;
    
std::stringstream ss;
variant var, var2;
var = object
{
  {"compact", true},
  {"schema", 0}
};
  
msgpack::serialize(var, ss);
msgpack::deserialize(ss, var2);

if (var2.is<object>())
{
  const object& obj = var2.get<object>();
  std::cout << "{ \"compact\": " << obj["compact"].get<bool>() ? "true" : "false" << ", \"schema\": " << obj["schema"].get<int>() << " }" << std::endl
}
```