
#include "reader.h"
#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
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
  Reader r = Reader("oadr_20b.xsd");
  auto root = r.Elem();
  r.Info(root);
  XMLPlatformUtils::Terminate();
  return 0;
}
