package main

import (
	"bytes"
	"fmt"
	"os"
	"regexp"
	"strings"
)

func GenCode(ns []string, name string, inherit map[string]string, typedef map[string]string, varMap map[string]string, enum []string) {
	fmt.Println("*****************")

	var genStr string
	if len(inherit) != 1 {
		// root element
	} else {
		fmt.Println(ns, name)

		genStr = GenGeneral(ns, name, inherit, typedef, varMap, enum)

	}

	if len(genStr) > 0 {
		err := os.WriteFile("./xsd/"+name+".hxx", []byte(genStr), 0666)
		if err != nil {
			panic(err.Error())
		}
	}
}

func GenGeneral(ns []string, name string, inherit map[string]string, typedef map[string]string, varMap map[string]string, enum []string) string {
	buf := bytes.NewBuffer([]byte{})

	s := ""
	// namespace {{}}
	// buf.WriteString("")
	s += constructors(name)
	s += var_list("", varMap, typedef)

	s = add_enum(s, enum)

	s = class(s, name, inherit[name])

	s = namespace(s, ns)

	s = add_include(s, include[name], name)

	s = defineHeader(s, name)

	buf.WriteString(s)

	return buf.String()
}

func add_enum(s string, enum []string) string {
	if len(enum) == 0 {
		return s
	}

	ret := "public:\n  enum value{"
	for _, i := range enum {
		ret += i + ","
	}
	ret = ret[:len(ret)-1]
	ret += "};\n"

	a := `

    virtual
    operator value () const
    {
      return _xsd_type_convert ();
    }

    protected:
    value
    _xsd_type_convert () const;

    public:
    static const char* const _xsd_type_literals_[%d];
    static const value _xsd_type_indexes_[%d];
    `

	ret += fmt.Sprintf(a, len(enum), len(enum))
	s += ret
	return s
}

func defineHeader(s string, name string) string {
	s = "#ifndef __XSD_TYPE__" + name + "__" + "\n" + "#define __XSD_TYPE__" + name + "__" + "\n" + s +
		"\n#endif"
	return s
}

func namespace(s string, ns []string) string {
	ret := ""
	for _, i := range ns {
		ret += "namespace " + i + "\n{\n"
	}
	ret += s
	for i := 0; i < len(ns); i++ {
		ret += "\n}"
	}
	return ret
}

func class(s string, name string, inherit string) string {
	vmap := map[string]string{
		// "::xml_schema::type": "::xsd::type",
	}

	// ::xml_schema::type
	ret := ""

	if inherit == "" {
		ret += "class " + name
	} else {
		// class AccuracyType : public ::xsd::cxx::tree::fundamental_base< ::xml_schema::float_, char, ::xml_schema::simple_type >

		// 如果是基础数据类型，要进行替换 one_container
		if strings.Contains(inherit, "fundamental") {
			inherit = get_fundmental_base(inherit)
			inherit = " public xsd::one_container<" + vmap[inherit] + ">"
		}
		for k, v := range vmap {
			if strings.Contains(inherit, k) {
				inherit = strings.ReplaceAll(inherit, k, v)
				break
			}
		}
		// inherit = strings.ReplaceAll(inherit, "xml_schema", "xsd")

		ret += "class " + name + " : " + inherit
	}

	ret += "\n{\n"
	ret += s
	ret += "\n};\n"
	return ret
}

func var_list(s string, varmap map[string]string, typedef map[string]string) string {
	typedef_string := ""

	ret := ""
	ret += "protected:\n"
	for k, v := range varmap {
		ret += v + " " + k + ";\n"

		varname := k[:len(k)-1]
		fmt.Println(varname, typedef[varname+"_type"])

		typedef_string += "typedef " + typedef[varname+"_type"] + " " + varname + "_type;\n"

		// serviceDeliveryPoint_
	}

	ret = "public:\n" + typedef_string + "\n" + ret + "\n"
	return ret
}

func get_fundmental_base(s string) string {
	str := string(s)
	reg := regexp.MustCompile(`::xml_schema::[a-zA-Z_]+`)
	ans := reg.FindString(str)
	args := strings.Split(ans, "::")
	return args[2]
}

func add_include(s string, args []string, name string) string {
	header := `

    #include "../../src/type.h"

    `
	set := map[string]bool{}
	for _, i := range args {
		if set[i] == true || i == name {
			continue
		}
		header += "#include\"" + i + ".hxx\"\n"
		set[i] = true
	}

	s = header + "\n" + s
	return s
}

func constructors(name string) string {
	ret := ""
	ret = "public:\n"

	constructor := `
      %s (const ::xercesc::DOMElement& e);
      %s (const ::xercesc::DOMAttr& a);
      %s (const %s& x);
      virtual ~%s();
    `

	ret += fmt.Sprintf(constructor, name, name, name, name, name)
	return ret
}
