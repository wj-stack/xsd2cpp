#include "base.hxx"
#include "xercesc/dom/DOM.hpp"
namespace Atom {

class emailType : public ::xsd::type::base_type<std::string> {
public:
  // Constructors.
  //
  emailType() : xsd::type::base_type<std::string>() {}

  emailType(const char *x) : xsd::type::base_type<std::string>(x) {}

  emailType(const ::std::string &x) : xsd::type::base_type<std::string>(x) {}

  emailType(const ::xsd::type::base_type<std::string> &);

  emailType(const ::xercesc::DOMElement &e);

  emailType(const ::xercesc::DOMAttr &a);

  emailType(const ::std::string &s, const ::xercesc::DOMElement *e);

  emailType(const emailType &x);

  virtual ~emailType();
};
} // namespace Atom
