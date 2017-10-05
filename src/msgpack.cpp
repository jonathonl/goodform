#include "msgpack.hpp"
#include "portable_endian.hpp"

namespace goodform
{
  //----------------------------------------------------------------//
  bool msgpack::serialize(const any& v, std::ostream& output)
  {
    bool ret = true;

    if (is<object_t>(v) && get<object_t>(v).size() <= 15) // fixmap	1000xxxx
    {
      ret = output.put(static_cast<char>(0x80 | (0x0F & get<object_t>(v).size()))).good();
      if (ret)
      {
        const goodform::object_t& tmp = get<object_t>(v);
        for (auto it = tmp.begin(); it != tmp.end(); ++it)
        {
          any key = it->first;
          ret = msgpack::serialize(key, output);
          if (ret)
            ret = msgpack::serialize(it->second, output);
        }
      }
    }
    else if (is<array_t>(v) && get<array_t>(v).size() <= 15) // fixarray	1001xxxx
    {
      ret = output.put(static_cast<char>(0x90 | (0x0F & get<array_t>(v).size()))).good();
      if (ret)
      {
        const goodform::array_t& tmp = get<array_t>(v);
        for (auto it = tmp.begin(); it != tmp.end(); ++it)
        {
          ret = msgpack::serialize(*it, output);
        }
      }
    }
    else if (is<std::string>(v) && get<std::string>(v).size() <= 31) // fixstr	101xxxxx
    {
      ret = output.put(static_cast<char>(0xA0 | (0x1F & get<std::string>(v).size()))).good();
      if (ret)
      {
        ret = output.write(&(get<std::string>(v)[0]), get<std::string>(v).size()).good();
      }
    }
    else if (is<std::nullptr_t>(v))
    {
      output.put(static_cast<char>(0xC0));
    }
    else if (is<bool>(v))
    {
      if (get<bool>(v))
        output.put(static_cast<char>(0xC3));
      else
        output.put(static_cast<char>(0xC2));
    }
    else if (is<binary_t>(v) && get<binary_t>(v).size() <= 0xFF) // Bin 8
    {
      if (!output.put(static_cast<char>(0xC4))
        || !output.put(static_cast<char>(0xFF & get<binary_t>(v).size()))
        || !output.write(get<binary_t>(v).data(), get<binary_t>(v).size()))
      {
        ret = false;
      }
    }
    else if (is<binary_t>(v) && get<binary_t>(v).size() <= 0xFFFF) // Bin 16
    {
      std::uint16_t sz_be(htobe16(0xFFFF & get<binary_t>(v).size()));
      if (!output.put(static_cast<char>(0xC5))
        || !output.write((char*)(&sz_be), sizeof(sz_be))
        || !output.write(get<binary_t>(v).data(), get<binary_t>(v).size()))
      {
        ret = false;
      }
    }
    else if (is<binary_t>(v) && get<binary_t>(v).size() <= 0xFFFFFFFF) // Bin 32
    {
      std::uint32_t sz_be(htobe32(0xFFFFFFFF & get<binary_t>(v).size()));
      if (!output.put(static_cast<char>(0xC6))
        || !output.write((char*)(&sz_be), sizeof(sz_be))
        || !output.write(get<binary_t>(v).data(), get<binary_t>(v).size()))
      {
        ret = false;
      }
    }
    else if (is<float>(v))
    {
      float flt = get<float>(v);

      numeric_union32 nu;
      nu.f = static_cast<float>(flt);
      std::uint32_t be(htobe32(nu.i));
      ret = output.put(static_cast<char>(0xCA)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<double>(v))
    {
      double dbl = get<double>(v);
      numeric_union64 nu;
      nu.f = dbl;
      std::uint64_t be(htobe64(nu.i));
      ret = output.put(static_cast<char>(0xCB)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
      // IGNORING fixint types for now.
//    else if (v.type() == variant_type::unsigned_integer && v.get<std::uint64_t>() <= 0x7F) // positive fixint 0xxxxxxx
//    {
//      std::uint8_t val = static_cast<std::uint8_t>(v.get<std::uint64_t>());
//      ret = output.put(static_cast<char>(std::uint8_t(0x7F) & val)).good();
//    }
//    else if (v.type() == variant_type::signed_integer && v.get<std::int64_t>() < 0 && v.get<std::int64_t>() >= -31) // negative fixint	111xxxxx
//    {
//      std::int8_t val = static_cast<std::int8_t>(v.get<std::int64_t>());
//      ret = output.put(static_cast<char>(0xE0 | (0x1F & (val * -1)))).good();
//    }
    else if (is<std::uint8_t>(v)) // Uint 8
    {
      std::uint8_t val = get<std::uint8_t>(v);
      ret = output.put(static_cast<char>(0xCC)).good();
      if (ret)
        ret = output.write((char*)&val, sizeof(std::uint8_t)).good();
    }
    else if (is<std::uint16_t>(v)) // Uint 16
    {
      std::uint16_t val = get<std::uint16_t>(v);
      std::uint16_t be(htobe16(val));
      ret = output.put(static_cast<char>(0xCD)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<std::uint32_t>(v)) // Uint 32
    {
      std::uint32_t val = get<std::uint64_t>(v);
      std::uint32_t be(htobe32(val));
      ret = output.put(static_cast<char>(0xCE)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<std::uint64_t>(v)) // Uint 64
    {
      std::uint64_t be(htobe64(get<std::uint64_t>(v)));
      ret = output.put(static_cast<char>(0xCF)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<std::int8_t>(v)) // Int 8
    {
      std::int8_t val = get<std::int8_t>(v);
      ret = output.put(static_cast<char>(0xD0)).good();
      if (ret)
        ret = output.write((char*)&val, sizeof(std::int8_t)).good();
    }
    else if (is<std::int16_t>(v)) // Int 16
    {
      std::int16_t val = get<std::int16_t>(v);
      std::int16_t be(htobe16(val));
      ret = output.put(static_cast<char>(0xD1)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<std::int32_t>(v)) // Int 32
    {
      std::int32_t val = get<std::int32_t>(v);
      std::int32_t be(htobe32(val));
      ret = output.put(static_cast<char>(0xD2)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<std::int64_t>(v)) // Int 64
    {
      std::int64_t be(htobe64(get<std::int64_t>(v)));
      ret = output.put(static_cast<char>(0xD3)).good();
      if (ret)
        ret = output.write((char*)&be, sizeof(be)).good();
    }
    else if (is<std::string>(v) && get<std::string>(v).size() <= 0xFF) // str 8
    {
      if (!output.put(static_cast<char>(0xD9))
        || !output.put(static_cast<char>(0xFF & get<std::string>(v).size()))
        || !output.write(get<std::string>(v).data(), get<std::string>(v).size()))
      {
        ret = false;
      }
    }
    else if (is<std::string>(v) && get<std::string>(v).size() <= 0xFFFF) // str 16
    {
      std::uint16_t sz_be(htobe16(0xFFFF & get<std::string>(v).size()));
      if (!output.put(static_cast<char>(0xDA))
        || !output.write((char*)(&sz_be), sizeof(sz_be))
        || !output.write(get<std::string>(v).data(), get<std::string>(v).size()))
      {
        ret = false;
      }
    }
    else if (is<std::string>(v) && get<std::string>(v).size() <= 0xFFFFFFFF) // str 32
    {
      std::uint32_t sz_be(htobe32(0xFFFFFFFF & get<std::string>(v).size()));
      if (!output.put(static_cast<char>(0xDB))
        || !output.write((char*)(&sz_be), sizeof(sz_be))
        || !output.write(get<std::string>(v).data(), get<std::string>(v).size()))
      {
        ret = false;
      }
    }
    else if (is<array_t>(v) && get<array_t>(v).size() <= 0xFFFF) // array 16
    {
      std::uint16_t sz_be(htobe16(0xFFFF & get<array_t>(v).size()));
      if (!output.put(static_cast<char>(0xDC))
        || !output.write((char*)(&sz_be), sizeof(sz_be)))
      {
        ret = false;
      }
      else
      {
        for (size_t i = 0; i < get<array_t>(v).size() && ret; ++i)
          ret = msgpack::serialize(get<array_t>(v)[i], output);
      }
    }
    else if (is<array_t>(v) && get<array_t>(v).size() <= 0xFFFFFFFF) // array 32
    {
      std::uint32_t sz_be(htobe32(0xFFFFFFFF & get<array_t>(v).size()));
      if (!output.put(static_cast<char>(0xDD))
        || !output.write((char*)(&sz_be), sizeof(sz_be)))
      {
        ret = false;
      }
      else
      {
        for (size_t i = 0; i < get<array_t>(v).size() && ret; ++i)
          ret = msgpack::serialize(get<array_t>(v)[i], output);
      }
    }
    else if (is<object_t>(v) && get<object_t>(v).size() <= 0xFFFF) // map 16
    {
      std::uint16_t sz_be(htobe16(0xFFFF & get<object_t>(v).size()));
      if (!output.put(static_cast<char>(0xDE))
        || !output.write((char*)(&sz_be), sizeof(sz_be)))
      {
        ret = false;
      }
      else
      {
        const goodform::object_t& o = get<object_t>(v);
        for (auto it = o.begin(); it != o.end() && ret; ++it)
        {
          any key(it->first);
          if (!msgpack::serialize(key, output) || !msgpack::serialize(it->second, output))
          {
            ret = false;
          }
        }
      }
    }
    else if (is<object_t>(v) && get<object_t>(v).size() <= 0xFFFFFFFF) // map 32
    {
      std::uint32_t sz_be(htobe32(0xFFFFFFFF & get<object_t>(v).size()));
      if (!output.put(static_cast<char>(0xDF))
        || !output.write((char*)(&sz_be), sizeof(sz_be)))
      {
        ret = false;
      }
      else
      {
        const goodform::object_t& o = get<object_t>(v);
        for (auto it = o.begin(); it != o.end() && ret; ++it)
        {
          any key(it->first);
          if (!msgpack::serialize(key, output) || !msgpack::serialize(it->second, output))
          {
            ret = false;
          }
        }
      }
    }
    else
    {
      ret = false;
    }

    return ret;
  }
  //----------------------------------------------------------------//

  //----------------------------------------------------------------//
  bool msgpack::deserialize(std::istream& input, any& v)
  {
    unsigned int typeByte = static_cast<unsigned int>(0xFF & input.get());
    bool ret = input.good();
    if (ret)
    {
      if (/*typeByte >= 0x00 &&*/ typeByte <= 0x7F) // positive fixint 0xxxxxxx
      {
        v = std::uint8_t(0x7F & typeByte);
      }
      else if (typeByte >= 0xE0 && typeByte <= 0xFF) // negative fixint	111xxxxx
      {
        v = std::int8_t((0x1F & typeByte ) * -1);
      }
      else if (typeByte >= 0x80 && typeByte <= 0x8F) // fixmap	1000xxxx
      {
        std::size_t sz(0x0F & typeByte);
        v = goodform::object_t();
        for (size_t i = 0; i < sz; ++i)
        {
          any key;
          if (!msgpack::deserialize(input, key) || !is<std::string>(key)) // Only supporting string keys.
            ret = false;
          else
            ret = msgpack::deserialize(input, get<object_t>(v)[get<std::string>(key)]);
        }
      }
      else if (typeByte >= 0x90 && typeByte <= 0x9F) // fixarray	1001xxxx
      {
        std::size_t sz(0x0F & typeByte);
        goodform::array_t a(sz);
        for (size_t i = 0; i < sz; ++i)
          msgpack::deserialize(input, a[i]);
        v = std::move(a);
      }
      else if (typeByte >= 0xA0 && typeByte <= 0xBF) // fixstr	101xxxxx
      {
        std::size_t sz(0x1F & typeByte);
        std::string s;
        s.resize(sz);
        input.read(&s[0], sz);
        if (!input.good())
          ret = false;
        else
          v = std::move(s);
      }
      else if (typeByte == 0xC0) // null
      {
        v = nullptr;
      }
      else if (typeByte == 0xC2) // false
      {
        v = false;
      }
      else if (typeByte == 0xC3) // true
      {
        v = true;
      }
      else if (typeByte == 0xC4) // Bin 8
      {
        std::size_t sz (0xFF & static_cast<unsigned int>(input.get()));
        ret = input.good();
        if (ret)
        {
          goodform::binary_t b(sz);
          if (!input.read(b.data(), sz).good())
            ret = false;
          else
            v = std::move(b);
        }
      }
      else if (typeByte == 0xC5) // Bin 16
      {
        std::uint16_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          goodform::binary_t b(be16toh(sz_be));
          if (!input.read(b.data(), b.size()).good())
            ret = false;
          else
            v = std::move(b);
        }
      }
      else if (typeByte == 0xC6) // Bin 32
      {
        std::uint32_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          goodform::binary_t b(be32toh(sz_be));
          if (!input.read(b.data(), b.size()).good())
            ret = false;
          else
            v = std::move(b);
        }
      }
      else if (typeByte == 0xCA) // Float 32
      {
        std::uint32_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          numeric_union32 u;
          u.i = be32toh(be);
          v = u.f;
        }
      }
      else if (typeByte == 0xCB) // Float 64
      {
        std::uint64_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          numeric_union64 u;
          u.i = be64toh(be);
          v = u.f;
        }
      }
      else if (typeByte == 0xCC) // Uint 8
      {
        std::uint8_t val;
        ret = input.read((char*)&val, sizeof(val)).good();
        if (ret)
          v = val;
      }
      else if (typeByte == 0xCD) // Uint 16
      {
        std::uint16_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          std::uint16_t val(be16toh(be));
          v = val;
        }
      }
      else if (typeByte == 0xCE) // Uint 32
      {
        std::uint32_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          std::uint32_t val(be32toh(be));
          v = val;
        }
      }
      else if (typeByte == 0xCF) // Uint 64
      {
        std::uint64_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          std::uint64_t val(be64toh(be));
          v = val;
        }
      }
      else if (typeByte == 0xD0) // Int 8
      {
        std::int8_t val;
        ret = input.read((char*)&val, sizeof(val)).good();
        if (ret)
          v = val;
      }
      else if (typeByte == 0xD1) // Int 16
      {
        std::int16_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          std::int16_t val(be16toh(be));
          v = val;
        }
      }
      else if (typeByte == 0xD2) // Int 32
      {
        std::int32_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          std::int32_t val(be32toh(be));
          v = val;
        }
      }
      else if (typeByte == 0xD3) // Int 64
      {
        std::int64_t be;
        ret = input.read((char*)&be, sizeof(be)).good();
        if (ret)
        {
          std::int64_t val(be64toh(be));
          v = val;
        }
      }
      else if (typeByte == 0xD9) // str 8
      {
        std::size_t sz(0xFF & static_cast<unsigned int>(input.get()));
        ret = input.good();
        if (ret)
        {
          std::string s;
          s.resize(sz);
          if (!input.read(&s[0], sz).good())
            ret = false;
          else
            v = std::move(s);
        }
      }
      else if (typeByte == 0xDA) // str 16
      {
        std::uint16_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          std::string s;
          s.resize(be16toh(sz_be));
          if (!input.read(&s[0], s.size()).good())
            ret = false;
          else
            v = std::move(s);
        }
      }
      else if (typeByte == 0xDB) // str 32
      {
        std::uint32_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          std::string s;
          s.resize(be32toh(sz_be));
          if (!input.read(&s[0], s.size()).good())
            ret = false;
          else
            v = std::move(s);
        }
      }
      else if (typeByte == 0xDC) // array 16
      {
        std::uint16_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          goodform::array_t a(be16toh(sz_be));
          for (size_t i = 0; ret && i < a.size(); ++i)
            ret = msgpack::deserialize(input, a[i]);
          v = std::move(a);
        }
      }
      else if (typeByte == 0xDD) // array 32
      {
        std::uint32_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          goodform::array_t a(be32toh(sz_be));
          for (size_t i = 0; ret && i < a.size(); ++i)
            ret = msgpack::deserialize(input, a[i]);
          v = std::move(a);
        }
      }
      else if (typeByte == 0xDE) // map 16
      {
        std::uint16_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          v = object_t();
          std::uint16_t sz(be16toh(sz_be));
          for (size_t i = 0; ret && i < sz; ++i)
          {
            any key;
            if (!msgpack::deserialize(input, key) || !is<std::string>(key)) // Only supporting string keys.
              ret = false;
            else
              ret = msgpack::deserialize(input, get<object_t>(v)[get<std::string>(key)]);
          }
        }
      }
      else if (typeByte == 0xDF) // map 32
      {
        std::uint32_t sz_be;
        ret = input.read((char*)&sz_be, sizeof(sz_be)).good();
        if (ret)
        {
          v = object_t();
          std::uint32_t sz(be32toh(sz_be));
          for (size_t i = 0; ret && i < sz; ++i)
          {
            any key;
            if (!msgpack::deserialize(input, key) || !is<std::string>(key)) // Only supporting string keys.
              ret = false;
            else
              ret = msgpack::deserialize(input, get<object_t>(v)[get<std::string>(key)]);
          }
        }
      }
      else // Not Supported
      {
        ret = false;
      }
    }

    return ret;
  }
  //----------------------------------------------------------------//
}