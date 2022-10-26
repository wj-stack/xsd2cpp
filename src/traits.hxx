

#ifndef __XSD__TRAITS__
#define __XSD__TRAITS__

#include "base.hxx"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>
namespace xsd {
namespace traits {

using namespace xercesc;

template <typename T, bool fund = xsd::fundamental::fundamental_p<T>::r>
class traits;

// base_type : string->base_type
template <class T> class traits<T, true> {
public:
  static T *create(DOMElement &e) {
    std::cout << XMLString::transcode(e.getTextContent()) << std::endl;

    return new T(
        boost::lexical_cast<T>(XMLString::transcode(e.getTextContent())));
  };
};

// other_type
template <class T> class traits<T, false> {
public:
  T *create(DOMElement &e) {
    return new T(e);
  }; // 需要 构造函数 完成 prase 递归构造
};

} // namespace traits
} // namespace xsd

#endif
