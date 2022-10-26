
#include "reader.h"
#include <iostream>
#include <ostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "base.hxx"
#include "container.hxx"
#include "traits.hxx"

#include "personType.hxx"

using namespace std;
using namespace xercesc;
int main(int argc, char *argv[]) {
  try {
    XMLPlatformUtils::Initialize();
  } catch (const XMLException &toCatch) {
    std::cerr << XMLString::transcode(toCatch.getMessage());
    return -1;
  }

  // do somethiong
  Reader r = Reader("1.xml");
  auto root = r.Elem();
  r.Info(root);

  cout << "------------start----------" << endl;
  xsd::container::one<std::string> a("sasd");
  cout << a.value() << endl;

  xsd::container::sequence<std::string> seq;

  seq.push_back("123");
  seq.push_back("35234");

  xsd::container::sequence<std::string> seq_copy(seq);
  for (auto v : seq_copy) {
    cout << v << endl;
  }

  xsd::container::one<std::string> float_one(
      xsd::traits::traits<std::string>::create(*root));

  cout << "float:" << float_one.value() << endl;
  cout << "------------end----------" << endl;

  Atom::personType p;

  p.name(::xsd::container::sequence<Atom::personType::name_type>(

      {Atom::personType::name_type("wujie"),
       Atom::personType::name_type("hello")}

      ));

  cout << "person :" << endl;

  for (auto &v : p.name()) {
    cout << v.value() << endl;
  }

  for (auto &v : p.email()) {
    cout << v.value() << endl;
  }
  XMLPlatformUtils::Terminate();
  return 0;
}
