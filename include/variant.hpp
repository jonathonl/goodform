#ifndef GOODFORM_VARIANT_HPP
#define GOODFORM_VARIANT_HPP

#include <vector>
#include <map>
#include <string>
#include <cstdint>

//#define GOOODFORM_NO_CAST_OPERATOR_OVERLOADS

#ifdef GOOODFORM_EXPLICIT_CONSTRUCTORS
#define GOOODFORM_EXPLICIT_MACRO explicit
#else
#define GOOODFORM_EXPLICIT_MACRO
#endif

//######################################################################//
namespace goodform
{
  //----------------------------------------------------------------------//
  class variant;
  typedef std::vector<char> binary;
  typedef std::map<std::string, goodform::variant> object;
  typedef std::vector<goodform::variant> array;
  //----------------------------------------------------------------------//

  //----------------------------------------------------------------------//
  enum class variant_type
  {
    null = 0,
    boolean,
    int8,
    int16,
    int32,
    int64,
    uint8,
    uint16,
    uint32,
    uint64,
    float32,
    float64,
    string,
    binary,
    array,
    object
  };
  //----------------------------------------------------------------------//

  //======================================================================//
  class variant
  {
  private:
    //----------------------------------------------------------------------//
    static const variant null_variant;
    static const std::nullptr_t const_null;

    static const bool const_bool;

    static const std::int8_t  const_int8;
    static const std::int16_t const_int16;
    static const std::int32_t const_int32;
    static const std::int64_t const_int64;

    static const std::uint8_t  const_uint8;
    static const std::uint16_t const_uint16;
    static const std::uint32_t const_uint32;
    static const std::uint64_t const_uint64;

    static const float const_float;
    static const double const_double;

    static const std::string const_string;
    static const binary const_binary;
    static const array const_array;
    static const object const_object;
    //----------------------------------------------------------------------//
  private:
    //----------------------------------------------------------------------//
    union data_union
    {
      bool boolean_;

      std::int8_t  int8_;
      std::int16_t int16_;
      std::int32_t int32_;
      std::int64_t int64_;

      std::uint8_t  uint8_;
      std::uint16_t uint16_;
      std::uint32_t uint32_;
      std::uint64_t uint64_;

      float float32_;
      double float64_;

      std::string string_;
      binary binary_;
      array array_;
      object object_;
      data_union(){}
      data_union(const data_union&){}
      data_union& operator=(const data_union&) { return (*this); }
      ~data_union(){}
    };

    data_union data_;
    variant_type type_;
    //----------------------------------------------------------------------//

    //----------------------------------------------------------------------//
    void move(variant&& source);
    void copy(const variant& source);
    void destroy();
    //----------------------------------------------------------------------//
  public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //--- ALTER INTERNAL VALUE TYPE ----------------------------------------//
    //----------------------------------------------------------------------//
    GOOODFORM_EXPLICIT_MACRO variant(std::nullptr_t value=nullptr);

    GOOODFORM_EXPLICIT_MACRO variant(bool value);

    GOOODFORM_EXPLICIT_MACRO variant(std::int8_t value);
    GOOODFORM_EXPLICIT_MACRO variant(std::int16_t value);
    GOOODFORM_EXPLICIT_MACRO variant(std::int32_t value);
    GOOODFORM_EXPLICIT_MACRO variant(std::int64_t value);

    GOOODFORM_EXPLICIT_MACRO variant(std::uint8_t value);
    GOOODFORM_EXPLICIT_MACRO variant(std::uint16_t value);
    GOOODFORM_EXPLICIT_MACRO variant(std::uint32_t value);
    GOOODFORM_EXPLICIT_MACRO variant(std::uint64_t value);

    GOOODFORM_EXPLICIT_MACRO variant(float value);
    GOOODFORM_EXPLICIT_MACRO variant(double value);

    GOOODFORM_EXPLICIT_MACRO variant(const char*const value);
    GOOODFORM_EXPLICIT_MACRO variant(const char*const value, std::size_t size);
    GOOODFORM_EXPLICIT_MACRO variant(std::string&& value);
    GOOODFORM_EXPLICIT_MACRO variant(binary&& value);
    GOOODFORM_EXPLICIT_MACRO variant(array&& value);
    GOOODFORM_EXPLICIT_MACRO variant(object&& value);
    GOOODFORM_EXPLICIT_MACRO variant(const std::string& value);
    GOOODFORM_EXPLICIT_MACRO variant(const binary& value);
    GOOODFORM_EXPLICIT_MACRO variant(const array& value);
    GOOODFORM_EXPLICIT_MACRO variant(const object& value);
    GOOODFORM_EXPLICIT_MACRO variant(variant_type type);
    ~variant();
    //----------------------------------------------------------------------//

    //----------------------------------------------------------------------//
    variant& operator=(std::nullptr_t value);
    variant& operator=(bool value);

    variant& operator=(std::int8_t value);
    variant& operator=(std::int16_t value);
    variant& operator=(std::int32_t value);
    variant& operator=(std::int64_t value);

    variant& operator=(std::uint8_t value);
    variant& operator=(std::uint16_t value);
    variant& operator=(std::uint32_t value);
    variant& operator=(std::uint64_t value);

    variant& operator=(float value);
    variant& operator=(double value);

    variant& operator=(const char* value);
    variant& operator=(std::string&& value);
    variant& operator=(binary&& value);
    variant& operator=(array&& value);
    variant& operator=(object&& value);
    variant& operator=(const std::string& value);
    variant& operator=(const binary& value);
    variant& operator=(const array& value);
    variant& operator=(const object& value);
    variant& operator=(variant_type type);
    //----------------------------------------------------------------------//

    //----------------------------------------------------------------------//
    variant(variant&& source);
    variant(const variant& source);
    variant& operator=(variant&& source);
    variant& operator=(const variant& source);
    //----------------------------------------------------------------------//

    //----------------------------------------------------------------------//
    // Helpers
    variant& operator[](size_t index);
    variant& operator[](const std::string& index);
    const variant& operator[](size_t index) const;
    const variant& operator[](const std::string& index) const;
    size_t size() const;
    void push(const variant& value);
    void push(variant&& value);
    //----------------------------------------------------------------------//
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

    //----------------------------------------------------------------------//
    variant_type type() const;
    void type(variant_type type);
    //----------------------------------------------------------------------//

    //----------------------------------------------------------------------//
    bool is_null() const;
    bool is_boolean() const;

    bool is_int8() const;
    bool is_int16() const;
    bool is_int32() const;
    bool is_int64() const;
    bool is_uint8() const;
    bool is_uint16() const;
    bool is_uint32() const;
    bool is_uint64() const;
    bool is_float32() const;
    bool is_float64() const;

    bool is_string() const;
    bool is_binary() const;
    bool is_array() const;
    bool is_object() const;

    template <typename T>
    bool is() const;
    //----------------------------------------------------------------------//


    //----------------------------------------------------------------------//
    //void Exceptions(ExceptionFlag exceptionFlag=wrongTypeBit|outOfRangeBit);
    //----------------------------------------------------------------------//

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //--- VALUE GETTERS ----------------------------------------------------//
    //----------------------------------------------------------------------//
    const bool& get_boolean() const;

    const std::int8_t&  get_int8() const;
    const std::int16_t& get_int16() const;
    const std::int32_t& get_int32() const;
    const std::int64_t& get_int64() const;

    const std::uint8_t&  get_uint8() const;
    const std::uint16_t& get_uint16() const;
    const std::uint32_t& get_uint32() const;
    const std::uint64_t& get_uint64() const;

    const float& get_float32() const;
    const double& get_float64() const;

    const std::string& get_string() const;
    const binary& get_binary() const;
    const array& get_array() const;
    const object& get_object() const;

    template <typename T>
    const T& get() const;

//    bool getBoolean(bool& dest) const;
//
//    bool getInt8( std::int8_t&   dest) const;
//    bool getInt16(std::int16_t& dest) const;
//    bool getInt32(std::int32_t& dest) const;
//    bool getInt64(std::int64_t& dest) const;
//
//    bool getUInt8( UInt8&  dest) const;
//    bool getUInt16(UInt16& dest) const;
//    bool getUInt32(UInt32& dest) const;
//    bool getUInt64(UInt64& dest) const;
//
//    bool getFloat32(float& dest) const;
//    bool getFloat64(double& dest) const;
//
//    bool getString(std::string& dest) const;
//    bool getArray(Array& dest) const;
//    bool getObject(Object& dest) const;

    template <typename T>
    bool get(T& dest) const;
    //----------------------------------------------------------------------//

#if !defined(GOOODFORM_NO_CAST_OPERATOR_OVERLOADS)
    //---------------------------------------------------------------------//
    explicit operator bool() const;
    explicit operator std::int8_t() const;
    explicit operator std::int16_t() const;
    explicit operator std::int32_t() const;
    explicit operator std::int64_t() const;
    explicit operator std::uint8_t() const;
    explicit operator std::uint16_t() const;
    explicit operator std::uint32_t() const;
    explicit operator std::uint64_t() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator const std::string&() const;
    explicit operator const goodform::binary&() const;
    explicit operator const goodform::array&() const;
    explicit operator const goodform::object&() const;
    //----------------------------------------------------------------------//
#endif
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  };
  //======================================================================//
}
//######################################################################//
#endif //GOODFORM_VARIANT_HPP