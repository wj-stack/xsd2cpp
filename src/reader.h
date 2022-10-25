#ifndef XML_GEN_READER__
#define XML_GEN_READER__

#include <cstdint>
#include <istream>
#include <stddef.h>
#include <string>
#include <vector>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax2/ContentHandler.hpp>
using namespace xercesc;
using namespace std;

struct TypeInfo {
  string namespace_;
  string name;
  vector<DOMAttr> attr;
  int64_t flag;
};

class Reader {
public:
  Reader(const std::string &path);
  Reader(DOMElement *root) : elem(root){};
  vector<DOMElement *> ElemVec();
  DOMNamedNodeMap *AttrVec();
  vector<DOMElement *> ElemVec(DOMElement *root);
  DOMNamedNodeMap *AttrVec(DOMElement *root);
  TypeInfo Info(DOMElement *root);
  DOMElement *Elem() const { return elem; }

private:
  DOMElement *elem;
};

#endif // !XML_GEN_READER__
