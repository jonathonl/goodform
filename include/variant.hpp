#ifndef GOODFORM_VARIANT_HPP
#define GOODFORM_VARIANT_HPP

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <limits>

#if __has_include("any")
#include <any>
#endif


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
#if !__has_include("any")
  class any;
#else
  typedef std::any any;
#endif
  typedef std::vector<char> binary_t;
  typedef std::map<std::string, any> object_t;
  typedef std::vector<any> array_t;
  //----------------------------------------------------------------------//
#if !__has_include("any")
  //----------------------------------------------------------------------//
  enum class variant_type
  {
    null = 0,
    boolean,
    //int8,
    //int16,
    //int32,
    //int64,
    //uint8,
    //uint16,
    //uint32,
    //uint64,
    //float32,
    //float64,
    signed_integer,
    unsigned_integer,
    floating_point,
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
    union data_union
    {
      bool boolean_;
      std::uint64_t unsigned_integer_;
      std::int64_t signed_integer_;
      double floating_point_;
      std::string string_;
      binary_t binary_;
      array_t array_;
      object_t object_;
      data_union(){}
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
    GOOODFORM_EXPLICIT_MACRO variant(binary_t&& value);
    GOOODFORM_EXPLICIT_MACRO variant(array_t&& value);
    GOOODFORM_EXPLICIT_MACRO variant(object_t&& value);
    GOOODFORM_EXPLICIT_MACRO variant(const std::string& value);
    GOOODFORM_EXPLICIT_MACRO variant(const binary_t& value);
    GOOODFORM_EXPLICIT_MACRO variant(const array_t& value);
    GOOODFORM_EXPLICIT_MACRO variant(const object_t& value);
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
    variant& operator=(binary_t&& value);
    variant& operator=(array_t&& value);
    variant& operator=(object_t&& value);
    variant& operator=(const std::string& value);
    variant& operator=(const binary_t& value);
    variant& operator=(const array_t& value);
    variant& operator=(const object_t& value);
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
    template <typename T>
    bool is() const;

    template <typename T>
    bool can_be() const;
    //----------------------------------------------------------------------//


    //----------------------------------------------------------------------//
    //void Exceptions(ExceptionFlag exceptionFlag=wrongTypeBit|outOfRangeBit);
    //----------------------------------------------------------------------//

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //--- VALUE GETTERS ----------------------------------------------------//
    //----------------------------------------------------------------------//
    template <typename T>
    const T& get() const;

    template <typename T>
    bool get(T& dest) const;
    //----------------------------------------------------------------------//

#if !defined(GOOODFORM_NO_CAST_OPERATOR_OVERLOADS)
    //---------------------------------------------------------------------//
    explicit operator bool() const;
    explicit operator std::int64_t() const;
    explicit operator std::uint64_t() const;
    explicit operator double() const;
    explicit operator const std::string&() const;
    explicit operator const goodform::binary_t&() const;
    explicit operator const goodform::array_t&() const;
    explicit operator const goodform::object_t&() const;
    //----------------------------------------------------------------------//
#endif
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  };
  //======================================================================//
#endif

//#if defined(__GNUC__) && (__GNUC__ >= 5)
//# if __GNUC__ == 7
//  typedef std::any any;
//# else
//  typedef std::experimental::any any;
//  template<typename T>
//  constexpr auto any_cast = std::experimental::any_cast<T>;
//# endif
  template <typename T>
  bool is(const any& v)
  {
#if __has_include("any")
    return v.type() == typeid(T);
#else
    return v.is<T>();
#endif
  }

//  template <typename T>
//  bool can_be(const any& v);

  template <typename T>
  const T& get(const any& v)
  {
#if __has_include("any")
    return std::any_cast<const T&>(v);
#else
    return v.get<T>();
#endif
  }

  template <typename T>
  T& get(any& v)
  {
#if __has_include("any")
    return std::any_cast<T&>(v);
#else
    return v.get<T>();
#endif
  }

  template <typename T>
  bool get(const any& v, T& dest)
  {
    if (is<T>(v))
    {
      dest = get<T>(v);
      return true;
    }
    return false;
  }



//#else
//  typedef variant any;
//  template <typename T>
//  bool is(const any& v) { return v.is<T>(); }
//
//  template <typename T>
//  bool can_be(const any& v) { return v.can_be<T>(); }
//
//  template <typename T>
//  const T& get(const any& v) { return v.get<T>(); }
//
//  template <typename T>
//  bool get(const any& v, T& dest) { return v.get<T>(dest); }
//#endif
}
//######################################################################//
#endif //GOODFORM_VARIANT_HPP