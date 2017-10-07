#ifndef GOODFORM_FORM_HPP
#define GOODFORM_FORM_HPP

#include "variant.hpp"

#include <functional>
#include <regex>

//######################################################################//
namespace goodform
{

  class error_message
  {
  private:
    std::string message_;
  public:
    error_message(const std::string& message) { this->message_ = message; }
    bool empty() const { return this->message_.empty(); }
    const std::string& message() const; // { return this->message_; }
  };

  //======================================================================//
  class boolean_validator
  {
  private:
    const bool value_;
  public:
    boolean_validator(bool value);

    /**
     * @return Returns boolean value.
     */
    bool val() const;
  };
  //======================================================================//

  //======================================================================//
  template <typename N>
  class number_validator
  {
  private:
    error_message& error_;
    const N value_;
  public:
    number_validator(N value, error_message& error_message);
    number_validator(const number_validator& source);

    /**
     * @return Returns numeric value of type N.
     */
    N val() const;

    /**
     * Validates that value is greater than parameter.
     *
     * @param greater_than Numeric value to check against.
     * @return Returns number_validator object for further validation.
     */
    number_validator gt(N greater_than);

    /**
     * Validates that value is less than than parameter.
     *
     * @param less_than Numeric value to check against.
     * @return Returns number_validator object for further validation.
     */
    number_validator lt(N less_than);

    /**
     * Validates that value is greater than or equal to parameter.
     *
     * @param greater_or_equal_to Numeric value to check against.
     * @return Returns number_validator object for further validation.
     */
    number_validator gte(N greater_or_equal_to);

    /**
     * Validates that value is less than or equal to parameter.
     *
     * @param less_or_equal_to Numeric value to check against.
     * @return Returns number_validator object for further validation.
     */
    number_validator lte(N less_or_equal_to);
  };
  //======================================================================//

  //======================================================================//
  class string_validator
  {
  private:
    error_message& error_;
    const std::string& value_;
  public:
    string_validator(const std::string& value, error_message& error_message);

    /**
     * Matches string value against regular expression.
     *
     * @param expression Regular expression to match against.
     * @return Returns string_validator object for further validation.
     */
    string_validator match(std::regex expression);

    /**
    * @return Returns string value.
    */
    const std::string& val() const;
  };
  //======================================================================//

  class sub_form;

  //======================================================================//
  class array_validator
  {
  private:
    error_message& error_;
    const std::vector<any>& value_;
  public:
    array_validator(const std::vector<any>& value, error_message& error_message);

    /**
     * Retrieves variant at array index or sets error if index does not exist.
     *
     * @param index Position in array.
     * @return Returns sub_form object for further validation.
     */
    sub_form at(size_t index);

    /**
     * Retrieves variant at array index or default_variant if index does not exist.
     *
     * @param index Position in array.
     * @param default_variant Variant to use if index does not exist.
     * @return Returns sub_form object for further validation.
     */
    sub_form at(size_t index, const any& default_variant);

    /**
     * Iterates elements in array.
     *
     * @param fn Function used to validate each array element.
     */
    void for_each(const std::function<void(sub_form& element, size_t index)>& fn);

    /**
     * @return Returns array value.
     */
    const std::vector<any>& val() const;
  };
  //======================================================================//

  //======================================================================//
  class object_validator
  {
  private:
    error_message& error_;
    const std::map<std::string, any>& value_;
  public:
    object_validator(const std::map<std::string, any>& value, error_message& error_message);

    /**
     * Retrieves variant at key or sets error if key does not exist.
     *
     * @param key Key in key-value map.
     * @return Returns sub_form object for further validation.
     */
    sub_form at(const std::string& key);

    /**
     * Retrieves variant at key or default_variant if index does not exist.
     *
     * @param key Key in key-value map.
     * @param default_variant Variant to use if key does not exist.
     * @return Returns sub_form object for further validation.
     */
    sub_form at(const std::string& key, const any& default_variant);

    /**
     * @return Returns object value.
     */
    const std::map<std::string, any>& val() const;
  };
  //======================================================================//

  //======================================================================//
  class sub_form
  {
  private:
    static const std::string const_string;
    static const array_t const_array;
    static const object_t const_object;

    error_message& error_;
    //static double convert_to_double(const variant& v);
  protected:
    const any& variant_;
  public:
    sub_form(const any& v, error_message& error_message);
    //sub_form(const sub_form& source);

    /**
     * Verifies that the current variant has a boolean value and otherwise sets an error.
     *
     * @return boolean_validator object.
     */
    boolean_validator boolean();

    /**
     * Verifies that the current variant has a boolean value and otherwise uses default passed as parameter.
     *
     * @param default_value The value to use if variant is not boolean.
     * @return boolean_validator object.
     */
    boolean_validator boolean(bool default_value);

    /**
     * Verifies that the current variant's value can be represented as a signed 8-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int8_t> int8();

    /**
     * Verifies that the current variant's value can be represented as a signed 8-bit integer and otherwise uses default passed as parameter.
     *
     * @param default_value The value to use if validation fails.
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int8_t> int8(std::int8_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a signed 16-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int16_t> int16();

    /**
     * Verifies that the current variant's value can be represented as a signed 16-bit integer and otherwise uses default passed as parameter.
     *
     * @param default_value The value to use if validation fails.
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int16_t> int16(std::int16_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a signed 32-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int32_t> int32();

    /**
     * Verifies that the current variant's value can be represented as a signed 32-bit integer and otherwise uses default passed as parameter.
     *
     * @param default_value The value to use if validation fails.
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int32_t> int32(std::int32_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a signed 64-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int64_t> int64();

    /**
     * Verifies that the current variant's value can be represented as a signed 8-bit integer and otherwise uses default passed as parameter.
     *
     * @param default_value The value to use if validation fails.
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::int64_t> int64(std::int64_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a unsigned 8-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::uint8_t> uint8();

    /**
     * Verifies that the current variant's value can be represented as a unsigned 8-bit integer and otherwise uses default passed as parameter.
     *
     * @param default_value The value to use if validation fails.
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::uint8_t> uint8(std::uint8_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a unsigned 16-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::uint16_t> uint16();

    /**
    * Verifies that the current variant's value can be represented as a unsigned 16-bit integer and otherwise uses default passed as parameter.
    *
    * @param default_value The value to use if validation fails.
    * @return A number_validator object is returned for further validation of the value.
    */
    number_validator<std::uint16_t> uint16(std::uint16_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a unsigned 32-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::uint32_t> uint32();

    /**
    * Verifies that the current variant's value can be represented as a unsigned 32-bit integer and otherwise uses default passed as parameter.
    *
    * @param default_value The value to use if validation fails.
    * @return A number_validator object is returned for further validation of the value.
    */
    number_validator<std::uint32_t> uint32(std::uint32_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a unsigned 64-bit integer and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<std::uint64_t> uint64();

    /**
    * Verifies that the current variant's value can be represented as a unsigned 64-bit integer and otherwise uses default passed as parameter.
    *
    * @param default_value The value to use if validation fails.
    * @return A number_validator object is returned for further validation of the value.
    */
    number_validator<std::uint64_t> uint64(std::uint64_t default_value);

    /**
     * Verifies that the current variant's value can be represented as a float and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<float> float32();

    /**
    * Verifies that the current variant's value can be represented as a float and otherwise uses default passed as parameter.
    *
    * @param default_value The value to use if validation fails.
    * @return A number_validator object is returned for further validation of the value.
    */
    number_validator<float> float32(float default_value);

    /**
     * Verifies that the current variant's value can be represented as a double and otherwise sets an error.
     *
     * @return A number_validator object is returned for further validation of the value.
     */
    number_validator<double> float64();

    /**
    * Verifies that the current variant's value can be represented as a double and otherwise uses default passed as parameter.
    *
    * @param default_value The value to use if validation fails.
    * @return A number_validator object is returned for further validation of the value.
    */
    number_validator<double> float64(double default_value);

    /**
     * Verifies that the current variant has a string value and otherwise sets an error.
     *
     * @return A string_validator object is returned for further validation of the value.
     */
    string_validator string();

    /**
    * Verifies that the current variant has a string value and otherwise uses default passed as parameter.
    *
    * @param default_value The value to use if validation fails.
    * @return A string_validator object is returned for further validation of the value.
    */
    string_validator string(const std::string& default_value);

    /**
     * Verifies that the current variant has an array value and otherwise sets an error.
     *
     * @return An array_validator object is returned for further validation of the value.
     */
    array_validator array();

    /**
     * Verifies that the current variant has an array value and otherwise sets an error.
     *
     * @param default_value The value to use if validation fails.
     * @return An array_validator object is returned for further validation of the value.
     */
    array_validator array(const std::vector<any>& default_value);

    /**
     * Verifies that the current variant has a key-value map value and otherwise sets an error.
     *
     * @return An object_validator object is returned for further validation of the value.
     */
    object_validator object();

    /**
     * Verifies that the current variant has a key-value map value and otherwise sets an error.
     *
     * @param default_value The value to use if validation fails.
     * @return An object_validator object is returned for further validation of the value.
     */
    object_validator object(const std::map<std::string, any>& default_value);


    /**
     * Shortcut method for array_validator::at. An error is set if the current variant is not an array or the index does not exist.
     *
     * @param index The current variant's array position to access.
     * @return A sub_form object is returned representing the variant at the index passed.
     */
    sub_form at(size_t index);

    /**
     * Shortcut method for array_validator::at. The default_variant is used if the current variant is not an array or the index does not exist.
     *
     * @param index The current variant's array position to access.
     * @param default_variant The variant to use if validation fails.
     * @return A sub_form object is returned representing the variant at the index passed.
     */
    sub_form at(size_t index, const any& default_variant);

    /**
     * Shortcut method for array_validator::for_each. An error is set if the current variant is not an array or the index does not exist.
     *
     * @param fn A function used to validate each array element.
     */
    void for_each(const std::function<void(sub_form& element, size_t index)>& fn);

    /**
     * Shortcut method for object_validator::at. An error is set if the current variant is not an object or the key does not exist.
     *
     * @param key The current variant's key-value map key to access.
     * @return A sub_form object is returned representing the variant at the key passed.
     */
    sub_form at(const std::string& key);

    /**
     * Shortcut method for object_validator::at. The default_variant is used if the current variant is not an object or the key does not exist.
     *
     * @param key The current variant's key-value map key to access.
     * @param default_variant The variant to use if validation fails.
     * @return A sub_form object is returned representing the variant at the key passed.
     */
    sub_form at(const std::string& key, const any& default_variant);
  };
  //======================================================================//

  //======================================================================//
  class form : public sub_form
  {
  private:
    error_message error_;
  public:
    form(const any& v);
    bool is_good() const;
  };
  //======================================================================//

  //======================================================================//
  template <typename N>
  number_validator<N>::number_validator(N value, error_message& errorMessage)
    : value_(value), error_(errorMessage)
  {

  }

  template <typename N>
  number_validator<N>::number_validator(const number_validator& source)
    : value_(source.value_), error_(source.error_)
  {

  }

  template <typename N>
  N number_validator<N>::val() const
  {
    return this->value_;
  }

  template <typename N>
  number_validator<N> number_validator<N>::gt(N greater_than)
  {
    if (this->value_ <= greater_than && this->error_.empty())
      this->error_ = "VALUE MUST BE GREATER THAN " + std::to_string(greater_than);

    number_validator<N> ret(*this);
    return ret;
  }

  template <typename N>
  number_validator<N> number_validator<N>::lt(N less_than)
  {
    if (this->value_ >= less_than && this->error_.empty())
      this->error_ = "VALUE MUST BE LESS THAN " + std::to_string(less_than);
    number_validator<N> ret(*this);
    return ret;
  }

  template <typename N>
  number_validator<N> number_validator<N>::gte(N greater_or_equal_to)
  {
    if (this->value_ < greater_or_equal_to && this->error_.empty())
      this->error_ = "VALUE MUST BE GREATER THAN OR EQUAL TO " + std::to_string(greater_or_equal_to);
    number_validator<N> ret(*this);
    return ret;
  }

  template <typename N>
  number_validator<N> number_validator<N>::lte(N less_or_equal_to)
  {
    if (this->value_ > less_or_equal_to && this->error_.empty())
      this->error_ = "VALUE MUST BE LESS THAN OR EQUAL TO " + std::to_string(less_or_equal_to);
    number_validator<N> ret(*this);
    return ret;
  }
  //======================================================================//
}
//######################################################################//
#endif //GOODFORM_FORM_HPP
