
#include "base.hxx"
#include "container.hxx"
#include "emailType.hxx"
#include "traits.hxx"
#include <istream>

namespace Atom {
class personType {
public:
  // name
  //
  typedef ::xsd::type::base_type<std::string> name_type;
  typedef ::xsd::container::sequence<name_type> name_sequence;
  typedef name_sequence::iterator name_iterator;
  typedef name_sequence::const_iterator name_const_iterator;
  typedef ::xsd::traits::traits<name_type> name_traits;

  const name_sequence &name() const { return this->name_; }

  name_sequence &name() { return this->name_; }

  void name(const name_sequence &s) { this->name_ = s; }

  // uri
  //
  // typedef ::Atom::uriType uri_type;
  // typedef ::xsd::cxx::tree::sequence<uri_type> uri_sequence;
  // typedef uri_sequence::iterator uri_iterator;
  // typedef uri_sequence::const_iterator uri_const_iterator;
  // typedef ::xsd::cxx::tree::traits<uri_type, char> uri_traits;
  //
  // const uri_sequence &uri() const;
  //
  // uri_sequence &uri();
  //
  // void uri(const uri_sequence &s);

  // email
  //
  typedef ::Atom::emailType email_type;
  typedef ::xsd::container::sequence<email_type> email_sequence;
  typedef email_sequence::iterator email_iterator;
  typedef email_sequence::const_iterator email_const_iterator;
  typedef ::xsd::traits::traits<email_type> email_traits;

  const email_sequence &email() const { return this->email_; }

  email_sequence &email() { return this->email_; }

  void email(const email_sequence &s);

  // base
  //
  typedef ::xsd::type::base_type<std::string> base_type;
  typedef ::xsd::container::optional<base_type> base_optional;
  typedef ::xsd::traits::traits<base_type> base_traits;

  const base_optional &base() const;

  base_optional &base();

  void base(const base_type &x);

  void base(const base_optional &x);

  void base(::std::unique_ptr<base_type> p);

  // lang
  //
  typedef ::xsd::type::base_type<std::string> lang_type;
  typedef ::xsd::container::optional<lang_type> lang_optional;
  typedef ::xsd::traits::traits<lang_type> lang_traits;

  const lang_optional &lang() const;

  lang_optional &lang();

  void lang(const lang_type &x);

  void lang(const lang_optional &x);

  void lang(::std::unique_ptr<lang_type> p);

  // Constructors.
  //
  personType() = default;

  personType(const ::xercesc::DOMElement &e);

  personType(const personType &x) = default;

  virtual ~personType() = default;

  // Implementation.
  //
protected:
  void parse();

protected:
  name_sequence name_;
  // uri_sequence uri_;
  email_sequence email_;
  base_optional base_;
  lang_optional lang_;
};
} // namespace Atom
