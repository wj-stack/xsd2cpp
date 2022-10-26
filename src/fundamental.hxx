
#ifndef __XML_FUNDAMENTAL_
#define __XML_FUNDAMENTAL_

#include <string>

namespace xsd {
namespace fundamental {

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

} // namespace fundamental

} // namespace xsd
#endif // !__XML_FUNDAMENTAL_
