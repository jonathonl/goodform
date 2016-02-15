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
  std::cout << "{ \"compact\": " << var2["compact"].get<bool>() ? "true" : "false" << ", \"schema\": " << var2["schema"].get<std::int64_t>() << " }" << std::endl
}
```