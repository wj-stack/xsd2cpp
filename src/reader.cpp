#include "reader.h"
#include <iostream>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;
using namespace std;

Reader::Reader(const std::string &path) {

  XercesDOMParser *parser = new XercesDOMParser();
  ErrorHandler *errHandler = new HandlerBase();
  parser->setErrorHandler(errHandler);
  parser->setValidationScheme(XercesDOMParser::Val_Always);
  parser->setDoNamespaces(true); // optionalkkk
  try {
    parser->parse(path.c_str());
  } catch (const XMLException &toCatch) {
    std::cerr << XMLString::transcode(toCatch.getMessage());
  }
  DOMDocument *doc = parser->getDocument();
  DOMElement *root = doc->getDocumentElement();
  this->elem = root;
}
vector<DOMElement *> Reader::ElemVec() { return ElemVec(elem); }

DOMNamedNodeMap *Reader::AttrVec() { return AttrVec(elem); }
vector<DOMElement *> Reader::ElemVec(DOMElement *root) {
  vector<DOMElement *> v;
  while (root != nullptr) {
    v.push_back(root);
    root = root->getNextElementSibling();
  }
  return v;
}
DOMNamedNodeMap *Reader::AttrVec(DOMElement *root) {
  return root->getAttributes();
}

TypeInfo Reader::Info(DOMElement *root) {

  auto prefix = XMLString::transcode(root->getPrefix());
  auto tagName = XMLString::transcode(root->getTagName());
  auto schemaTypeInfo = root->getSchemaTypeInfo();
  auto typeNamespace = XMLString::transcode(schemaTypeInfo->getTypeNamespace());
  auto typeName = XMLString::transcode(schemaTypeInfo->getTypeName());
  auto localName = XMLString::transcode(root->getLocalName());
  auto namespaceURI = XMLString::transcode(root->getNamespaceURI());
  auto baseURI = XMLString::transcode(root->getBaseURI());
  auto nodeName = XMLString::transcode(root->getNodeName());

  cout << "prefix:" << prefix << " tagName:"
       << tagName
       // << " typeName:" << typeName << " typeNamespace:" << typeNamespace
       << " localName:" << localName << " NS URI:" << namespaceURI
       << " base URI:" << baseURI << " nodeName:" << nodeName << endl;
  // auto elems = ElemVec(root);
  // for (auto &p : elems) {
  //   auto attrs = AttrVec(p);
  // }

  return TypeInfo{

  };
}
