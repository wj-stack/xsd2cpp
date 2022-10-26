#ifndef __XSD__CONTAINER__
#define __XSD__CONTAINER__

#include "base.hxx"
#include <vector>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>
namespace xsd {
namespace container {

// one
template <typename T> class one : public xsd::type::base_type<T> {
public:
  one(const T &x) : xsd::type::base_type<T>(x) {}
  one(T &x) : xsd::type::base_type<T>(x) {}
  one(T *x) : xsd::type::base_type<T>(x) {}
  one() : xsd::type::base_type<T>() {}
  virtual ~one() = default;
};

// minOccurs = 0  ---> optional
template <typename T> class optional : public xsd::type::base_type<T> {
public:
  optional(const T &x) : xsd::type::base_type<T>(x) {}
  optional(T &x) : xsd::type::base_type<T>(x) {}
  optional(T *x) : xsd::type::base_type<T>(x) {}
  optional() : xsd::type::base_type<T>() {}
  virtual ~optional() = default;
};

template <typename T> class sequence : public std::vector<T> {
public:
  typedef std::vector<T> _vec;
  sequence(const _vec &x) : _vec(x) {}
  sequence(_vec &x) : _vec(x) {}
  sequence(const sequence &x) : _vec(x) {}
  sequence(sequence &x) : _vec(x) {}
  sequence() : _vec() {}
  virtual ~sequence() = default;
};

} // namespace container
} // namespace xsd

#endif // !__XSD__CONTAINER__
