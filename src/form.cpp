#include "goodform/form.hpp"
//######################################################################//
namespace goodform
{

  //======================================================================//
  boolean_validator::boolean_validator(bool value)
    : value_(value)
  {
  }

  bool boolean_validator::val() const
  {
    return this->value_;
  }
  //======================================================================//

  //======================================================================//
  string_validator::string_validator(const std::string& value, error_message& errorMessage) : value_(value), error_(errorMessage)
  {

  }

  string_validator string_validator::match(std::regex expression)
  {
    if (!std::regex_match(this->value_, expression))
      this->error_ = error_message("STRING DOES NOT MATCH EXPRESSION");

    string_validator ret(*this);
    return ret;
  }

  const std::string& string_validator::val() const
  {
    return this->value_;
  }
  //======================================================================//

  //======================================================================//
  array_validator::array_validator(const std::vector<any>& value, error_message& errorMessage) : value_(value), error_(errorMessage)
  {

  }


  sub_form array_validator::at(size_t index)
  {
    if (this->value_.size() > index)
    {
      sub_form ret(this->value_[index], this->error_);
      return ret;
    }
    else
    {
      sub_form ret(nullptr, this->error_);
      if (this->error_.empty())
        this->error_ = error_message("INDEX (" + std::to_string(index) + ") OUT OF RANGE");
      return ret;
    }
  }

  sub_form array_validator::at(size_t index, const any& default_variant)
  {
    sub_form ret(this->value_.size() > index ? this->value_[index] : default_variant, this->error_);
    return ret;
  }

  void array_validator::for_each(const std::function<void(sub_form& element, size_t index)>& fn)
  {
    for (size_t i = 0; i < this->value_.size(); ++i)
    {
      sub_form tmp(this->value_[i], this->error_);
      fn(tmp, i);
    }
  }

  const std::vector<any>& array_validator::val() const
  {
    return this->value_;
  }
  //======================================================================//

  //======================================================================//
  object_validator::object_validator(const std::map<std::string,any>& value, error_message& errorMessage) : value_(value), error_(errorMessage)
  {

  }

  sub_form object_validator::at(const std::string& key)
  {
    auto it = this->value_.find(key);
    if (it != this->value_.end())
    {
      sub_form ret(sub_form(it->second, this->error_));
      return ret;
    }
    else
    {
      sub_form ret(nullptr, this->error_);
      if (this->error_.empty())
        this->error_ = error_message("KEY (" + key + ") DOES NOT EXIST");
      return ret;
    }
  }

  sub_form object_validator::at(const std::string& key, const any& default_variant)
  {
    auto it = this->value_.find(key);
    sub_form ret(it != this->value_.end() ? it->second : default_variant, this->error_);
    return ret;
  }

  const std::map<std::string, any>& object_validator::val() const
  {
    return this->value_;
  }
  //======================================================================//

  //======================================================================//
  const std::string sub_form::const_string;
  const array_t sub_form::const_array;
  const object_t sub_form::const_object;

  sub_form::sub_form(const any& v, error_message& err_msg) :
    variant_(v),
    error_(err_msg)
  {

  }


//  sub_form::sub_form(const sub_form& source) :
//    variant_(source.variant_),
//    error_(source.error_)
//  {
//
//  }

  boolean_validator sub_form::boolean()
  {
    if (!is<bool>(this->variant_))
      this->error_ = error_message("TYPE NOT BOOLEAN");

    boolean_validator ret(get<bool>(is<bool>(this->variant_) ? this->variant_ : false));
    return ret;
  }

  boolean_validator sub_form::boolean(bool default_value)
  {
    boolean_validator ret(is<bool>(this->variant_) ? get<bool>(this->variant_) : default_value);
    return ret;
  }

//  bool sub_form::can_be_int8(const variant& v)
//  {
//    return (v.type() == variant_type::signed_integer && v.get<std::int64_t>() >= std::numeric_limits<std::int8_t>::min() && v.get<std::int64_t>() <= std::numeric_limits<std::int8_t>::max())
//     || (v.type() == variant_type::unsigned_integer && v.get<std::uint64_t>() <= std::numeric_limits<std::int8_t>::max());
//  }
//
//  bool sub_form::can_be_int16(const variant& v)
//  {
//    return (v.type() == variant_type::signed_integer && v.get<std::int64_t>() >= std::numeric_limits<std::int16_t>::min() && v.get<std::int64_t>() <= std::numeric_limits<std::int16_t>::max())
//      || (v.type() == variant_type::unsigned_integer && v.get<std::uint64_t>() <= std::numeric_limits<std::int16_t>::max());
//  }
//
//  bool sub_form::can_be_int32(const variant& v)
//  {
//    return (v.type() == variant_type::signed_integer && v.get<std::int64_t>() >= std::numeric_limits<std::int32_t>::min() && v.get<std::int64_t>() <= std::numeric_limits<std::int32_t>::max())
//      || (v.type() == variant_type::unsigned_integer && v.get{std::uint64_t>() <= std::numeric_limits<std::int32_t>::max());
//  }
//
//  bool sub_form::can_be_int64(const variant& v)
//  {
//    return (v.type() == variant_type::signed_integer && v.get<std::int64_t>() >= std::numeric_limits<std::int64_t>::min() && v.get<std::int64_t>() <= std::numeric_limits<std::int64_t>::max())
//      || (v.type() == variant_type::unsigned_integer && v.get<std::uint64_t>() <= std::numeric_limits<std::int64_t>::max());
//  }


//  double sub_form::convert_to_double(const variant& v)
//  {
//    double ret = 0;
//
//    if (v.is<std::int8_t>())    ret = (double)(v.get<std::int8_t>());
//    if (v.is<std::int16_t>())   ret = (double)(v.get<std::int16_t>());
//    if (v.is<std::int32_t>())   ret = (double)(v.get<std::int32_t>());
//    if (v.is<std::int64_t>())   ret = (double)(v.get<std::int64_t>());
//    if (v.is<std::uint8_t>())   ret = (double)(v.get<std::uint8_t>());
//    if (v.is<std::uint16_t>())  ret = (double)(v.get<std::uint16_t>());
//    if (v.is<std::uint32_t>())  ret = (double)(v.get<std::uint32_t>());
//    if (v.is<std::uint64_t>())  ret = (double)(v.get<std::uint64_t>());
//    if (v.is<float>())          ret = (double)(v.get<float>());
//    if (v.is<double>())         ret = v.get<double>();
//
//    return ret;
//  }

  number_validator<std::int8_t> sub_form::int8()
  {
    std::int8_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A int8_t");
    return number_validator<std::int8_t>(val, this->error_);
  }

  number_validator<std::int8_t> sub_form::int8(std::int8_t default_value)
  {
    std::int8_t val;
    if (convert(this->variant_, val))
      return number_validator<std::int8_t>(val, this->error_);
    else
      return number_validator<std::int8_t>(default_value, this->error_);
  }

  number_validator<std::int16_t> sub_form::int16()
  {
    std::int16_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A int16_t");
    return number_validator<std::int16_t>(val, this->error_);
  }

  number_validator<std::int16_t> sub_form::int16(std::int16_t default_value)
  {
    std::int16_t val;
    if (convert(this->variant_, val))
      return number_validator<std::int16_t>(val, this->error_);
    else
      return number_validator<std::int16_t>(default_value, this->error_);
  }

  number_validator<std::int32_t> sub_form::int32()
  {
    std::int32_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A int32_t");
    return number_validator<std::int32_t>(val, this->error_);
  }

  number_validator<std::int32_t> sub_form::int32(std::int32_t default_value)
  {
    std::int8_t val;
    if (convert(this->variant_, val))
      return number_validator<std::int32_t>(val, this->error_);
    else
      return number_validator<std::int32_t>(default_value, this->error_);
  }

  number_validator<std::int64_t> sub_form::int64()
  {
    std::int64_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A int64_t");
    return number_validator<std::int64_t>(val, this->error_);
  }

  number_validator<std::int64_t> sub_form::int64(std::int64_t default_value)
  {
    std::int64_t val;
    if (convert(this->variant_, val))
      return number_validator<std::int64_t>(val, this->error_);
    else
      return number_validator<std::int64_t>(default_value, this->error_);
  }

  number_validator<std::uint8_t> sub_form::uint8()
  {
    std::uint8_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A uint8_t");
    return number_validator<std::uint8_t>(val, this->error_);
  }

  number_validator<std::uint8_t> sub_form::uint8(std::uint8_t default_value)
  {
    std::uint8_t val;
    if (convert(this->variant_, val))
      return number_validator<std::uint8_t>(val, this->error_);
    else
      return number_validator<std::uint8_t>(default_value, this->error_);
  }

  number_validator<std::uint16_t> sub_form::uint16()
  {
    std::uint16_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A uint16_t");
    return number_validator<std::uint16_t>(val, this->error_);
  }

  number_validator<std::uint16_t> sub_form::uint16(std::uint16_t default_value)
  {
    std::uint16_t val;
    if (convert(this->variant_, val))
      return number_validator<std::uint16_t>(val, this->error_);
    else
      return number_validator<std::uint16_t>(default_value, this->error_);
  }

  number_validator<std::uint32_t> sub_form::uint32()
  {
    std::uint32_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A uint32_t");
    return number_validator<std::uint32_t>(val, this->error_);
  }

  number_validator<std::uint32_t> sub_form::uint32(std::uint32_t default_value)
  {
    std::uint32_t val;
    if (convert(this->variant_, val))
      return number_validator<std::uint32_t>(val, this->error_);
    else
      return number_validator<std::uint32_t>(default_value, this->error_);
  }

  number_validator<std::uint64_t> sub_form::uint64()
  {
    std::uint64_t val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A uint64_t");
    return number_validator<std::uint64_t>(val, this->error_);
  }

  number_validator<std::uint64_t> sub_form::uint64(std::uint64_t default_value)
  {
    std::uint64_t val;
    if (convert(this->variant_, val))
      return number_validator<std::uint64_t>(val, this->error_);
    else
      return number_validator<std::uint64_t>(default_value, this->error_);
  }

  number_validator<float> sub_form::float32()
  {
    float val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A float32");
    return number_validator<float>(val, this->error_);
  }

  number_validator<float> sub_form::float32(float default_value)
  {
    float val;
    if (convert(this->variant_, val))
      return number_validator<float>(val, this->error_);
    else
      return number_validator<float>(default_value, this->error_);
  }

  number_validator<double> sub_form::float64()
  {
    double val;
    if (!convert(this->variant_, val))
      this->error_ = error_message("NOT A float64");
    return number_validator<double>(val, this->error_);
  }

  number_validator<double> sub_form::float64(double default_value)
  {
    double val;
    if (convert(this->variant_, val))
      return number_validator<double>(val, this->error_);
    else
      return number_validator<double>(default_value, this->error_);
  }

//  number_validator<std::int64_t> sub_form::integer()
//  {
//    return this->integer(error_message("NOT A NUMBER"));
//  }
//
//  number_validator<std::int64_t> sub_form::integer(const error_message& customerror_message)
//  {
//    if (!this->variant_.isNumber())
//      this->error_ = customerror_message;
//    return this->int64Types_.back();
//  }
//
//  number_validator<std::int64_t> sub_form::integer(std::int64_t default_value)
//  {
//    if (!this->variant_.isNumber())
//      this->int64Types_.push_back(number_validator<int64_t>(default_value, this->error_));
//    else
//      this->int64Types_.push_back(number_validator<int64_t>(this->variant_.integer(), this->error_));
//    return this->int64Types_.back();
//  }
//
//  number_validator<std::uint64_t> sub_form::unsignedInteger()
//  {
//    return this->unsignedInteger(error_message("NOT A NUMBER"));
//  }
//
//  number_validator<std::uint64_t> sub_form::unsignedInteger(const error_message& customerror_message)
//  {
//    this->uint64Types_.push_back(number_validator<uint64_t>(this->variant_.unsignedInteger(), this->error_));
//    if (!this->variant_.isNumber() || this->variant_.isSignedNumber())
//      this->error_ = customerror_message;
//    return this->uint64Types_.back();
//  }
//
//  number_validator<std::uint64_t> sub_form::unsignedInteger(std::uint64_t default_value)
//  {
//    if (!this->variant_.isNumber() || this->variant_.isSignedNumber())
//      this->uint64Types_.push_back(number_validator<uint64_t>(default_value, this->error_));
//    else
//      this->uint64Types_.push_back(number_validator<uint64_t>(this->variant_.unsignedInteger(), this->error_));
//    return this->uint64Types_.back();
//  }
//
//  number_validator<double> sub_form::floatingPoint()
//  {
//    return this->floatingPoint(error_message("NOT A NUMBER"));
//  }
//
//  number_validator<double> sub_form::floatingPoint(const error_message& customerror_message)
//  {
//    this->realTypes_.push_back(number_validator<double>(this->variant_.floatingPoint(), this->error_));
//    if (!this->variant_.isNumber())
//      this->error_ = customerror_message;
//    return this->realTypes_.back();
//  }
//
//  number_validator<double> sub_form::floatingPoint(double default_value)
//  {
//    if (!this->variant_.isNumber())
//      this->realTypes_.push_back(number_validator<double>(default_value, this->error_));
//    else
//      this->realTypes_.push_back(number_validator<double>(this->variant_.floatingPoint(), this->error_));
//    return this->realTypes_.back();
//  }

  string_validator sub_form::string()
  {
    if (!is<std::string>(this->variant_))
    {
      this->error_ = error_message("TYPE NOT STRING");
      return string_validator(const_string, this->error_);
    }
    else
    {
      return string_validator(get<std::string>(this->variant_), this->error_);
    }
  }

  string_validator sub_form::string(const std::string& default_value)
  {
    string_validator ret(is<std::string>(this->variant_) ? get<std::string>(this->variant_) : default_value, this->error_);
    return ret;
  }

  array_validator sub_form::array()
  {

    if (!is<goodform::array_t>(this->variant_))
    {
      this->error_ = error_message("NOT AN ARRAY");
      return array_validator(const_array, this->error_);
    }
    else
    {
      return array_validator(get<goodform::array_t>(this->variant_), this->error_);
    }
  }

  array_validator sub_form::array(const std::vector<any>& default_value)
  {
    array_validator ret(is<goodform::array_t>(this->variant_) ? get<goodform::array_t>(this->variant_) : default_value, this->error_);
    return ret;
  }

  object_validator sub_form::object()
  {
    if (!is<goodform::object_t>(this->variant_))
    {
      this->error_ = error_message("NOT AN OBJECT");
      return object_validator(get<goodform::object_t>(const_object), this->error_);
    }
    else
    {
      return object_validator(get<goodform::object_t>(this->variant_), this->error_);
    }
  }

  object_validator sub_form::object(const std::map<std::string,any>& default_value)
  {
    object_validator ret(is<goodform::object_t>(this->variant_) ? get<goodform::object_t>(this->variant_) : default_value, this->error_);
    return ret;
  }

  sub_form sub_form::at(size_t index)
  {
    return this->array().at(index);
  }

  sub_form sub_form::at(size_t index, const any& default_variant)
  {
    return this->array(std::vector<any>()).at(index, default_variant);
  }

  void sub_form::for_each(const std::function<void(sub_form& element, size_t index)>& fn)
  {
    this->array().for_each(fn);
  }

  sub_form sub_form::at(const std::string& key)
  {
    return this->object().at(key);
  }

  sub_form sub_form::at(const std::string& key, const any& default_variant)
  {
    return this->object(std::map<std::string, any>()).at(key, default_variant);
  }
  //======================================================================//

  //======================================================================//
  form::form(const any& v) : error_(""), sub_form(v, error_)
  {

  }

  bool form::is_good() const
  {
    return this->error_.empty();
  }
  //======================================================================//
}
//######################################################################//
