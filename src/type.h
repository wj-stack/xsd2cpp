

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/XMLString.hpp>
// Test whether T is a fundamental C++ type.
//

template <typename T> struct fundamental_p {
  static const bool r = false;
};

// byte
//
template <> struct fundamental_p<signed char> {
  static const bool r = true;
};

template <> struct fundamental_p<unsigned char> {
  static const bool r = true;
};

// short
//
template <> struct fundamental_p<short> {
  static const bool r = true;
};

template <> struct fundamental_p<unsigned short> {
  static const bool r = true;
};

// int
//
template <> struct fundamental_p<int> {
  static const bool r = true;
};

template <> struct fundamental_p<unsigned int> {
  static const bool r = true;
};

// long
//
template <> struct fundamental_p<long> {
  static const bool r = true;
};

template <> struct fundamental_p<unsigned long> {
  static const bool r = true;
};

template <> struct fundamental_p<long long> {
  static const bool r = true;
};

template <> struct fundamental_p<unsigned long long> {
  static const bool r = true;
};

// bool
//
template <> struct fundamental_p<bool> {
  static const bool r = true;
};

// float
//
template <> struct fundamental_p<float> {
  static const bool r = true;
};

template <> struct fundamental_p<double> {
  static const bool r = true;
};

template <> struct fundamental_p<std::string> {
  static const bool r = true;
};

using namespace xercesc;

// traits
template <typename T, bool fund = fundamental_p<T>::r> class traits;

// base_type : string->base_type
template <class T> class traits<T, true> {
public:
  static T *create(const DOMElement &e) {
    return new T(
        boost::lexical_cast<T>(XMLString::transcode(e.getTextContent())));
  };
};

// other_type
template <class T> class traits<T, false> {
public:
  T *create(const DOMElement &e) { return new T(e); };
};

// type
//
template <typename T, bool fund = fundamental_p<T>::r> class one_container;

// simple
template <typename T> class one_container<T, true> {
private:
  std::unique_ptr<T> g;

public:
  // type(const DOMElement &e) {
  //   this->p = std::unique_ptr<T>(traits<T>::create(e));
  // }
  T *get() const { return g.get(); }
  void set(T *x) { g = std::unique_ptr<T>(x); }
};

template <typename T> class one_container<T, false> {};
//
// // string_type
// template <typename T> class string_type : public type {
//   string_type(const T &);
// };
//
// // TODO：　ｍｏｒｅ　ｔｙｐｅ
//
// // any type
// template <typename T> class any_type : public type {
//   any_type(const T &);
// };

// traits : new T();

class Hello : public one_container<std::string> {
  Hello(); // prase
};

class Body {

  typedef float hello_type;
  typedef std::string world_type;

  typedef traits<hello_type> hello_traits;
  typedef traits<world_type> world_traits;

  Body(const DOMElement &e) { // 遍历 e ， prase to var
  }

  one_container<float> to_; // 容器
  one_container<std::string> from_;
};

class Note {
public:
  typedef float to_type;
  typedef std::string from_type;

  typedef traits<to_type> to_traits;
  typedef traits<from_type> from_traits;

  Note(const DOMElement &e) { // 遍历 e ， prase to var
    this->to_.set(to_traits::create(e));
    this->from_.set(from_traits::create(e));
  }

  to_type *to() { return this->to_.get(); }
  from_type *from() { return this->from_.get(); }

private:
  one_container<float> to_; // 容器
  one_container<std::string> from_;
};
