
#include "variant.hpp"

//######################################################################//
namespace goodform
{
  //----------------------------------------------------------------------//
  const variant variant::null_variant = goodform::variant(nullptr);

  const std::nullptr_t variant::const_null = nullptr;
  const bool variant::const_bool = false;

  const std::int8_t   variant::const_int8   = 0;
  const std::int16_t  variant::const_int16  = 0;
  const std::int32_t  variant::const_int32  = 0;
  const std::int64_t  variant::const_int64  = 0;
  const std::uint8_t  variant::const_uint8  = 0;
  const std::uint16_t variant::const_uint16 = 0;
  const std::uint32_t variant::const_uint32 = 0;
  const std::uint64_t variant::const_uint64 = 0;

  const float variant::const_float   = 0.0;
  const double variant::const_double = 0.0;

  const std::string variant::const_string;
  const binary variant::const_binary;
  const array variant::const_array;
  const object variant::const_object;
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  void variant::destroy()
  {
    if (this->type_ == variant_type::string)
      this->data_.string_.~basic_string();     //~string();
    else if (this->type_ == variant_type::binary)
      this->data_.binary_.~vector();
    else if (this->type_ == variant_type::array)
      this->data_.array_.~vector();
    else if (this->type_ == variant_type::object)
      this->data_.object_.~map();
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  void variant::move(variant&& source)
  {
    this->type_ = source.type_;

    if (this->type_ == variant_type::boolean)
      this->data_.boolean_ = source.data_.boolean_;
    else if (this->type_ == variant_type::int8)
      this->data_.int8_ = source.data_.int8_;
    else if (this->type_ == variant_type::int16)
      this->data_.int16_ = source.data_.int16_;
    else if (this->type_ == variant_type::int32)
      this->data_.int32_ = source.data_.int32_;
    else if (this->type_ == variant_type::int64)
      this->data_.int64_ = source.data_.int64_;
    else if (this->type_ == variant_type::uint8)
      this->data_.uint8_ = source.data_.uint8_;
    else if (this->type_ == variant_type::uint16)
      this->data_.uint16_ = source.data_.uint16_;
    else if (this->type_ == variant_type::uint32)
      this->data_.uint32_ = source.data_.uint32_;
    else if (this->type_ == variant_type::uint64)
      this->data_.uint64_ = source.data_.uint64_;
    else if (this->type_ == variant_type::float32)
      this->data_.float32_ = source.data_.float32_;
    else if (this->type_ == variant_type::float64)
      this->data_.float64_ = source.data_.float64_;
    else if (this->type_ == variant_type::string)
      new(&this->data_.string_) std::string(std::move(source.data_.string_));
    else if (this->type_ == variant_type::binary)
      new(&this->data_.binary_) binary(std::move(source.data_.binary_));
    else if (this->type_ == variant_type::array)
      new(&this->data_.array_) array(std::move(source.data_.array_));
    else if (this->type_ == variant_type::object)
      new(&this->data_.object_) object(std::move(source.data_.object_));
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  void variant::copy(const variant& source)
  {
    this->type_ = source.type_;

    if (this->type_ == variant_type::boolean)
      this->data_.boolean_ = source.data_.boolean_;
    else if (this->type_ == variant_type::int8)
      this->data_.int8_ = source.data_.int8_;
    else if (this->type_ == variant_type::int16)
      this->data_.int16_ = source.data_.int16_;
    else if (this->type_ == variant_type::int32)
      this->data_.int32_ = source.data_.int32_;
    else if (this->type_ == variant_type::int64)
      this->data_.int64_ = source.data_.int64_;
    else if (this->type_ == variant_type::uint8)
      this->data_.uint8_ = source.data_.uint8_;
    else if (this->type_ == variant_type::uint16)
      this->data_.uint16_ = source.data_.uint16_;
    else if (this->type_ == variant_type::uint32)
      this->data_.uint32_ = source.data_.uint32_;
    else if (this->type_ == variant_type::uint64)
      this->data_.uint64_ = source.data_.uint64_;
    else if (this->type_ == variant_type::float32)
      this->data_.float32_ = source.data_.float32_;
    else if (this->type_ == variant_type::float64)
      this->data_.float64_ = source.data_.float64_;
    else if (this->type_ == variant_type::string)
      new(&this->data_.string_) std::string(source.data_.string_);
    else if (this->type_ == variant_type::binary)
      new(&this->data_.binary_) binary(source.data_.binary_);
    else if (this->type_ == variant_type::array)
      new(&this->data_.array_) array(source.data_.array_);
    else if (this->type_ == variant_type::object)
      new(&this->data_.object_) object(source.data_.object_);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(variant&& source)
  {
    this->move(std::move(source));
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const variant& source)
  {
    this->copy(source);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(variant&& source)
  {
    if (this != &source)
    {
      this->destroy();
      this->move(std::move(source));
    }
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(const variant& source)
  {
    if (this != &source)
    {
      this->destroy();
      this->copy(source);
    }
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::nullptr_t value)
  {
    this->type_ = variant_type::null;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::~variant()
  {
    this->destroy();
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(bool value)
  {
    this->type_ = variant_type::boolean;
    this->data_.boolean_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::int8_t value)
  {
    this->type_ = variant_type::int8;
    this->data_.int8_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::int16_t value)
  {
    this->type_ = variant_type::int16;
    this->data_.int16_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::int32_t value)
  {
    this->type_ = variant_type::int32;
    this->data_.int32_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::int64_t value)
  {
    this->type_ = variant_type::int64;
    this->data_.int64_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::uint8_t value)
  {
    this->type_ = variant_type::uint8;
    this->data_.uint8_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::uint16_t value)
  {
    this->type_ = variant_type::uint16;
    this->data_.uint16_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::uint32_t value)
  {
    this->type_ = variant_type::uint32;
    this->data_.uint32_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::uint64_t value)
  {
    this->type_ = variant_type::uint64;
    this->data_.uint64_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(float value)
  {
    this->type_ = variant_type::float32;
    this->data_.float32_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(double value)
  {
    this->type_ = variant_type::float64;
    this->data_.float64_ = value;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const char*const value)
  {
    this->type_ = variant_type::string;
    new(&this->data_.string_) std::string(value);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const char*const value, size_t size)
  {
    this->type_ = variant_type::string;
    new(&this->data_.string_) std::string(value, size);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(std::string&& value)
  {
    this->type_ = variant_type::string;
    new(&this->data_.string_) std::string(std::move(value));
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(goodform::binary&& value)
  {
    this->type_ = variant_type::binary;
    new (&this->data_.binary_) binary(std::move(value));
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(goodform::array&& value)
  {
    this->type_ = variant_type::array;
    new (&this->data_.array_) array(std::move(value));
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(goodform::object&& value)
  {
    this->type_ = variant_type::object;
    new(&this->data_.object_) object(std::move(value));
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const std::string& value)
  {
    this->type_ = variant_type::string;
    new(&this->data_.string_) std::string(value);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const binary& value)
  {
    this->type_ = variant_type::binary;
    new (&this->data_.binary_) binary(value);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const array& value)
  {
    this->type_ = variant_type::array;
    new (&this->data_.array_) array(value);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(const object& value)
  {
    this->type_ = variant_type::object;
    new(&this->data_.object_) object(value);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant::variant(variant_type type)
  {
    this->type_ = type;
    if (this->type_ == variant_type::string)
      new (&this->data_.string_) std::string();
    else if (this->type_ == variant_type::binary)
      new (&this->data_.binary_) goodform::binary();
    else if (this->type_ == variant_type::array)
      new (&this->data_.array_) goodform::array();
    else if (this->type_ == variant_type::object)
      new (&this->data_.object_) goodform::object();
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::nullptr_t value)
  {
    this->destroy();
    this->type_ = variant_type::null;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(bool value)
  {
    if (this->type_ != variant_type::boolean)
    {
      this->destroy();
      this->type_ = variant_type::boolean;
    }
    this->data_.boolean_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::int8_t value)
  {
    if (this->type_ != variant_type::int8)
    {
      this->destroy();
      this->type_ = variant_type::int8;
    }
    this->data_.int8_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::int16_t value)
  {
    if (this->type_ != variant_type::int16)
    {
      this->destroy();
      this->type_ = variant_type::int16;
    }
    this->data_.int16_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::int32_t value)
  {
    if (this->type_ != variant_type::int32)
    {
      this->destroy();
      this->type_ = variant_type::int32;
    }
    this->data_.int32_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::int64_t value)
  {
    if (this->type_ != variant_type::int64)
    {
      this->destroy();
      this->type_ = variant_type::int64;
    }
    this->data_.int64_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::uint8_t value)
  {
    if (this->type_ != variant_type::uint8)
    {
      this->destroy();
      this->type_ = variant_type::uint8;
    }
    this->data_.uint8_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::uint16_t value)
  {
    if (this->type_ != variant_type::uint16)
    {
      this->destroy();
      this->type_ = variant_type::uint16;
    }
    this->data_.uint16_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::uint32_t value)
  {
    if (this->type_ != variant_type::uint32)
    {
      this->destroy();
      this->type_ = variant_type::uint32;
    }
    this->data_.uint32_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::uint64_t value)
  {
    if (this->type_ != variant_type::uint64)
    {
      this->destroy();
      this->type_ = variant_type::uint64;
    }
    this->data_.uint64_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(float value)
  {
    if (this->type_ != variant_type::float32)
    {
      this->destroy();
      this->type_ = variant_type::float32;
    }
    this->data_.float32_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(double value)
  {
    if (this->type_ != variant_type::float64)
    {
      this->destroy();
      this->type_ = variant_type::float64;
    }
    this->data_.float64_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(const char* value)
  {
    if (this->type_ != variant_type::string)
    {
      this->destroy();
      this->type_ = variant_type::string;
      new (&this->data_.string_) std::string(value);
    }
    else
      this->data_.string_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(std::string&& value)
  {
    if (this->type_ != variant_type::string)
    {
      this->destroy();
      this->type_ = variant_type::string;
      new (&this->data_.string_) std::string(std::move(value));
    }
    else
      this->data_.string_ = std::move(value);
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(goodform::binary&& value)
  {
    if (this->type_ != variant_type::binary)
    {
      this->destroy();
      this->type_ = variant_type::binary;
      new (&this->data_.binary_) goodform::binary(std::move(value));
    }
    else
      this->data_.binary_ = std::move(value);
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(goodform::array&& value)
  {
    if (this->type_ != variant_type::array)
    {
      this->destroy();
      this->type_ = variant_type::array;
      new (&this->data_.array_) goodform::array(std::move(value));
    }
    else
      this->data_.array_ = std::move(value);
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(goodform::object&& value)
  {
    if (this->type_ != variant_type::object)
    {
      this->destroy();
      this->type_ = variant_type::object;
      new (&this->data_.object_) goodform::object(std::move(value));
    }
    else
      this->data_.object_ = std::move(value);
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(const std::string& value)
  {
    if (this->type_ != variant_type::string)
    {
      this->destroy();
      this->type_ = variant_type::string;
      new (&this->data_.string_) std::string(value);
    }
    else
      this->data_.string_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(const binary& value)
  {
    if (this->type_ != variant_type::binary)
    {
      this->destroy();
      this->type_ = variant_type::binary;
      new (&this->data_.binary_) goodform::binary(value);
    }
    else
      this->data_.binary_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(const array& value)
  {
    if (this->type_ != variant_type::array)
    {
      this->destroy();
      this->type_ = variant_type::array;
      new (&this->data_.array_) goodform::array(value);
    }
    else
      this->data_.array_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(const object& value)
  {
    if (this->type_ != variant_type::object)
    {
      this->destroy();
      this->type_ = variant_type::object;
      new (&this->data_.object_) goodform::object(value);
    }
    else
      this->data_.object_ = value;
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator=(variant_type type)
  {
    this->type(type);
    return *this;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant_type variant::type() const
  {
    return this->type_;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  void variant::type(variant_type type)
  {
    if (this->type_ != type)
    {
      this->destroy();
      if (type == variant_type::string)
        new (&this->data_.string_) std::string();
      else if (type == variant_type::binary)
        new (&this->data_.binary_) goodform::binary();
      else if (type == variant_type::array)
        new (&this->data_.array_) goodform::array();
      else if (type == variant_type::object)
        new (&this->data_.object_) goodform::object();
      this->type_ = type;
    }
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::is<std::nullptr_t>() const { return this->is_null(); }
  template<>
  bool variant::is<bool>() const { return this->is_boolean(); }
  template<>
  bool variant::is<std::int8_t>() const { return this->is_int8(); }
  template<>
  bool variant::is<std::int16_t>() const { return this->is_int16(); }
  template<>
  bool variant::is<std::int32_t>() const { return this->is_int32(); }
  template<>
  bool variant::is<std::int64_t>() const { return this->is_int64(); }
  template<>
  bool variant::is<std::uint8_t>() const { return this->is_uint8(); }
  template<>
  bool variant::is<std::uint16_t>() const { return this->is_uint16(); }
  template<>
  bool variant::is<std::uint32_t>() const { return this->is_uint32(); }
  template<>
  bool variant::is<std::uint64_t>() const { return this->is_uint64(); }
  template<>
  bool variant::is<float>() const { return this->is_float32(); }
  template<>
  bool variant::is<double>() const { return this->is_float64(); }
  template<>
  bool variant::is<std::string>() const { return this->is_string(); }
  template<>
  bool variant::is<goodform::binary>() const { return this->is_binary(); }
  template<>
  bool variant::is<goodform::array>() const { return this->is_array(); }
  template<>
  bool variant::is<goodform::object>() const { return this->is_object(); }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  bool variant::is_null()    const { return (this->type_ == variant_type::null);    }
  bool variant::is_boolean() const { return (this->type_ == variant_type::boolean); }
  bool variant::is_int8()    const { return (this->type_ == variant_type::int8);    }
  bool variant::is_int16()   const { return (this->type_ == variant_type::int16);   }
  bool variant::is_int32()   const { return (this->type_ == variant_type::int32);   }
  bool variant::is_int64()   const { return (this->type_ == variant_type::int64);   }
  bool variant::is_uint8()   const { return (this->type_ == variant_type::uint8);   }
  bool variant::is_uint16()  const { return (this->type_ == variant_type::uint16);  }
  bool variant::is_uint32()  const { return (this->type_ == variant_type::uint32);  }
  bool variant::is_uint64()  const { return (this->type_ == variant_type::uint64);  }
  bool variant::is_float32() const { return (this->type_ == variant_type::float32); }
  bool variant::is_float64() const { return (this->type_ == variant_type::float64); }
  bool variant::is_string()  const { return (this->type_ == variant_type::string);  }
  bool variant::is_binary()  const { return (this->type_ == variant_type::binary);  }
  bool variant::is_array()   const { return (this->type_ == variant_type::array);   }
  bool variant::is_object()  const { return (this->type_ == variant_type::object);  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  const std::nullptr_t& variant::get<std::nullptr_t>() const { return variant::const_null; }
  template<>
  const bool& variant::get<bool>() const { return this->get_boolean(); }
  template<>
  const std::int8_t& variant::get<std::int8_t>() const { return this->get_int8(); }
  template<>
  const std::int16_t& variant::get<std::int16_t>() const { return this->get_int16(); }
  template<>
  const std::int32_t& variant::get<std::int32_t>() const { return this->get_int32(); }
  template<>
  const std::int64_t& variant::get<std::int64_t>() const { return this->get_int64(); }
  template<>
  const std::uint8_t& variant::get<std::uint8_t>() const { return this->get_uint8(); }
  template<>
  const std::uint16_t& variant::get<std::uint16_t>() const { return this->get_uint16(); }
  template<>
  const std::uint32_t& variant::get<std::uint32_t>() const { return this->get_uint32(); }
  template<>
  const std::uint64_t& variant::get<std::uint64_t>() const { return this->get_uint64(); }
  template<>
  const float& variant::get<float>() const { return this->get_float32(); }
  template<>
  const double& variant::get<double>() const { return this->get_float64(); }
  template<>
  const std::string& variant::get<std::string>() const { return this->get_string(); }
  template<>
  const goodform::binary& variant::get<goodform::binary>() const { return this->get_binary(); }
  template<>
  const goodform::array& variant::get<goodform::array>() const { return this->get_array(); }
  template<>
  const goodform::object& variant::get<goodform::object>() const { return this->get_object(); }
  //----------------------------------------------------------------------//


  //----------------------------------------------------------------------//
  template<>
  bool variant::get(bool& dest) const
  {
    bool ret = (this->type_ == variant_type::boolean);
    if (ret)
      dest = this->get_boolean();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::int8_t& dest) const
  {
    bool ret = (this->type_ == variant_type::int8);
    if (ret)
      dest = this->get_int8();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::int16_t& dest) const
  {
    bool ret = (this->type_ == variant_type::int16);
    if (ret)
      dest = this->get_int16();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::int32_t& dest) const
  {
    bool ret = (this->type_ == variant_type::int32);
    if (ret)
      dest = this->get_int32();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::int64_t& dest) const
  {
    bool ret = (this->type_ == variant_type::int64);
    if (ret)
      dest = this->get_int64();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::uint8_t& dest) const
  {
    bool ret = (this->type_ == variant_type::uint8);
    if (ret)
      dest = this->get_uint8();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::uint16_t& dest) const
  {
    bool ret = (this->type_ == variant_type::uint16);
    if (ret)
      dest = this->get_uint16();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::uint32_t& dest) const
  {
    bool ret = (this->type_ == variant_type::uint32);
    if (ret)
      dest = this->get_uint32();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::uint64_t& dest) const
  {
    bool ret = (this->type_ == variant_type::uint64);
    if (ret)
      dest = this->get_uint64();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(float& dest) const
  {
    bool ret = (this->type_ == variant_type::float32);
    if (ret)
      dest = this->get_float32();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(double& dest) const
  {
    bool ret = (this->type_ == variant_type::float64);
    if (ret)
      dest = this->get_float64();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(std::string& dest) const
  {
    bool ret = (this->type_ == variant_type::string);
    if (ret)
      dest = this->get_string();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(goodform::binary& dest) const
  {
    bool ret = (this->type_ == variant_type::binary);
    if (ret)
      dest = this->get_binary();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(goodform::array& dest) const
  {
    bool ret = (this->type_ == variant_type::array);
    if (ret)
      dest = this->get_array();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  template<>
  bool variant::get(goodform::object& dest) const
  {
    bool ret = (this->type_ == variant_type::object);
    if (ret)
      dest = this->get_object();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const bool& variant::get_boolean() const { return (this->type_ == variant_type::boolean ? this->data_.boolean_ : const_bool); }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const std::int8_t&   variant::get_int8()   const { return (this->type_ == variant_type::int8   ? this->data_.int8_   : const_int8  ); }
  const std::int16_t&  variant::get_int16()  const { return (this->type_ == variant_type::int16  ? this->data_.int16_  : const_int16 ); }
  const std::int32_t&  variant::get_int32()  const { return (this->type_ == variant_type::int32  ? this->data_.int32_  : const_int32 ); }
  const std::int64_t&  variant::get_int64()  const { return (this->type_ == variant_type::int64  ? this->data_.int64_  : const_int64 ); }
  const std::uint8_t&  variant::get_uint8()  const { return (this->type_ == variant_type::uint8  ? this->data_.uint8_  : const_uint8 ); }
  const std::uint16_t& variant::get_uint16() const { return (this->type_ == variant_type::uint16 ? this->data_.uint16_ : const_uint16); }
  const std::uint32_t& variant::get_uint32() const { return (this->type_ == variant_type::uint32 ? this->data_.uint32_ : const_uint32); }
  const std::uint64_t& variant::get_uint64() const { return (this->type_ == variant_type::uint64 ? this->data_.uint64_ : const_uint64); }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const float&  variant::get_float32() const { return (this->type_ == variant_type::float32 ? this->data_.float32_ : const_float);  }
  const double& variant::get_float64() const { return (this->type_ == variant_type::float64 ? this->data_.float64_ : const_double); }
  //----------------------------------------------------------------------//



  //----------------------------------------------------------------------//
  const std::string& variant::get_string() const
  {
    return (this->type_ == variant_type::string ? this->data_.string_ : const_string);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const binary& variant::get_binary() const
  {
    return (this->type_ == variant_type::binary ? this->data_.binary_ : const_binary);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const array& variant::get_array() const
  {
    return (this->type_ == variant_type::array ? this->data_.array_ : const_array);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const object& variant::get_object() const
  {
    return (this->type_ == variant_type::object ? this->data_.object_ : const_object);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator[](size_t index)
  {
    if (this->type_ != variant_type::array)
    {
      this->destroy();
      this->type_ = variant_type::array;
      new (&this->data_.array_) goodform::array();
    }
    while (index >= this->data_.array_.size())
      this->data_.array_.push_back(variant());
    return this->data_.array_[index];
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  variant& variant::operator[](const std::string& index)
  {
    if (this->type_ != variant_type::object)
    {
      this->destroy();
      this->type_ = variant_type::object;
      new (&this->data_.object_) goodform::object();
    }
    return this->data_.object_[index];
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const variant& variant::operator[](size_t index) const
  {
    if (this->type_ == variant_type::array && index < this->data_.array_.size())
      return this->data_.array_[index];
    else
      return variant::null_variant;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  const variant& variant::operator[](const std::string& index) const
  {
    if (this->type_ != variant_type::object)
      return variant::null_variant;
    else
    {
      auto it =  this->data_.object_.find(index);
      if (it != this->data_.object_.end())
        return it->second;
      else
        return variant::null_variant;
    }
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  size_t variant::size() const
  {
    size_t ret = 0;
    if (this->type_ == variant_type::object)
      ret = this->data_.object_.size();
    else if (this->type_ == variant_type::array)
      ret = this->data_.array_.size();
    else if (this->type_ == variant_type::binary)
      ret = this->data_.binary_.size();
    else if (this->type_ == variant_type::string)
      ret = this->data_.string_.size();
    return ret;
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  void variant::push(const variant& value)
  {
    if (this->type_ != variant_type::array)
    {
      this->destroy();
      this->type_ = variant_type::array;
      new (&this->data_.array_) goodform::array();
    }
    this->data_.array_.push_back(value);
  }
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  void variant::push(variant&& value)
  {
    if (this->type_ != variant_type::array)
    {
      this->destroy();
      this->type_ = variant_type::array;
      new (&this->data_.array_) goodform::array();
    }
    this->data_.array_.push_back(std::move(value));
  }
  //----------------------------------------------------------------------//

#if !defined(GOOODFORM_NO_CAST_OPERATOR_OVERLOADS)
  //---------------------------------------------------------------------//
  variant::operator bool() const
  {
    return this->get_boolean();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::int8_t() const
  {
    return this->get_int8();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::int16_t() const
  {
    return this->get_int16();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::int32_t() const
  {
    return this->get_int32();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::int64_t() const
  {
    return this->get_int64();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::uint8_t() const
  {
    return this->get_uint8();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::uint16_t() const
  {
    return this->get_uint16();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::uint32_t() const
  {
    return this->get_uint32();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator std::uint64_t() const
  {
    return this->get_uint64();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator float() const
  {
    return this->get_float32();
  }
  //---------------------------------------------------------------------//
  //---------------------------------------------------------------------//
  variant::operator double() const
  {
    return this->get_float64();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator const std::string&() const
  {
    return this->get_string();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator const goodform::binary&() const
  {
    return this->get_binary();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator const goodform::array&() const
  {
    return this->get_array();
  }
  //---------------------------------------------------------------------//

  //---------------------------------------------------------------------//
  variant::operator const goodform::object&() const
  {
    return this->get_object();
  }
  //----------------------------------------------------------------------//
#endif
}
//######################################################################//
