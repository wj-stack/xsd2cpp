// file      : xsde/cxx/hybrid/base.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_HYBRID_BASE_HXX
#define XSDE_CXX_HYBRID_BASE_HXX
#include "fundamental.hxx"
#include <memory>
#include <string>

namespace xsd {
namespace type {

template <typename T, bool fund = xsd::fundamental::fundamental_p<T>::r>
class base_type {};

template <typename T> class base_type<T, true> {
public:
  base_type() : val(0) {}
  base_type(T &x) : val(x) {}
  base_type(T *x) : val(*x) {}
  base_type(const T &x) : val(x) {}
  const T &value() const { return val; }
  virtual ~base_type() = default;
  void set(T *x) { val = *x; }

private:
  T val;
};

template <typename T> class base_type<T, false> {
public:
  base_type() {} // delay , need to set
  base_type(T &x) { this->p = std::unique_ptr<T>(new T(x)); }
  base_type(T *x) { this->p = std::unique_ptr<T>(new T(*x)); }
  base_type(const T &x) { this->p = std::unique_ptr<T>(new T(x)); }
  T &value() const { return *p.get(); }
  virtual ~base_type() = default;
  void set(T *x) { this->p = std::unique_ptr<T>(new T(x)); } // traits只负责创建

private:
  std::unique_ptr<T> p;
};

} // namespace type

} // namespace xsd

#endif // XSDE_CXX_HYBRID_BASE_HXX
