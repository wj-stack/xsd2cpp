package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"regexp"
	"strings"
)

var (
	include = make(map[string][]string)
	keyword = []string{}
)

func main() {
	path := "/home/wyatt/code/fuda/OpenADR-VEN-Library-master/oadrsd/oadrsd/2b/"
	dir, err := os.ReadDir(path)
	if err != nil {
		panic(err.Error())
	}

	for _, d := range dir {
		name := d.Name()
		name = name[:len(name)-4]
		keyword = append(keyword, name)
		include[name] = make([]string, 0)
	}

	// cfg := ini.Empty()
	// cnt := map[string]int{}
	for _, d := range dir {
		name := d.Name()
		if strings.HasSuffix(name, ".hxx") {

			body, err := os.ReadFile(path + name)
			if err != nil {
				panic(err.Error())
			}
			r := bufio.NewReader(bytes.NewBuffer(body))

			inherit := map[string]string{}

			typedef := map[string]string{}

			enum := []string{}

			namespace := getNameSpace(path+name, name[:len(name)-4])
			// fmt.Println(namespace)

			inherit[name[:len(name)-4]] = getInherit(path + name)
			// fmt.Println(inherit)
			varMap := getVar(path+name, name)
			// fmt.Println("var map:", varMap)
			for {
				line, _, err := r.ReadLine()
				if err != nil {
					break
				}
				str := string(line)
				if strings.Contains(str, "typedef") {
					s := strings.TrimSpace(str)
					args := strings.Split(s, " ")
					// typedef[] = args[len(args)-1][:len(args[len(args)-1])-1]
					a := (args[len(args)-1][:len(args[len(args)-1])-1])
					b := s[7 : len(s)-len(a)-1]
					b = strings.TrimSpace(b)
					a = strings.TrimSpace(a)
					typedef[a] = b

					// fmt.Println(a)
					// fmt.Println(b)
				}
				// if strings.Contains(str, "class") && !strings.HasSuffix(str, ";") {
				// 	s := strings.TrimSpace(str)
				// 	args := strings.Split(s, " ")
				// 	a := args[1][:len(args[1])-1]
				// 	c := len("class " + a + " : public")
				// 	b := s[c:]
				// 	inherit[a] = b
				// 	fmt.Println("继承状态", a, b)
				// }

				if strings.Contains(str, "enum ") {
					// fmt.Println("发现 枚举 类型", str)
					// fmt.Println(name)
					enum = GetEnum(path + name)
					// fmt.Println(enum)
				}
				// 查找成员变量

				// 查找命名空间
			}
			// fmt.Println(inherit)
			if len(inherit) != 1 {
				// fmt.Println("没有继承", name)
			}

			ns := ""
			for _, i := range namespace {
				ns += i + "."
			}

			// fmt.Println("namespace:", ns)

			if len(namespace) > 0 {
				ns = ns[:len(ns)-1]
			}

			name = name[:len(name)-4]
			for _, key := range keyword {
				for k, v := range inherit {
					if strings.Contains(k, key) {
						include[name] = append(include[name], key)
					}
					if strings.Contains(v, key) {
						include[name] = append(include[name], key)
					}
				}

				for k, v := range typedef {
					if strings.Contains(k, key) {
						include[name] = append(include[name], key)
					}
					if strings.Contains(v, key) {
						include[name] = append(include[name], key)
					}
				}

				for k, v := range varMap {
					if strings.Contains(k, key) {
						include[name] = append(include[name], key)
					}
					if strings.Contains(v, key) {
						include[name] = append(include[name], key)
					}
				}
			}

			fmt.Println("继承状态", inherit)
			GenCode(namespace, name, inherit, typedef, varMap, enum)

		}
	}
	// cfg.SaveTo("var.ini")
}

func GetEnum(path string) []string {
	body, err := os.ReadFile(path)
	if err != nil {
		panic(err.Error())
	}
	str := string(body)
	reg := regexp.MustCompile("enum value\\s+\\{[\\sA-Za-z,_0-9]+\\};")
	ans := reg.FindString(str)
	args := strings.Split(ans, "\n")
	ret := []string{}
	for i := 2; i < len(args)-1; i++ {
		a := args[i]
		a = strings.TrimSpace(a)
		if strings.HasSuffix(a, ",") {
			a = a[:len(a)-1]
		}
		ret = append(ret, a)
	}
	return ret
}

func getNameSpace(path string, name string) []string {
	body, err := os.ReadFile(path)
	if err != nil {
		panic(err.Error())
	}
	str := string(body)
	reg := regexp.MustCompile(`namespace[\{\sA-Za-z0-9_]+` + name)
	ans := reg.FindString(str)
	args := strings.Split(ans, "\n")
	ret := []string{}
	for _, i := range args {
		i = strings.TrimSpace(i)
		if strings.Contains(i, "namespace") {
			a := strings.Split(i, " ")
			ret = append(ret, strings.TrimSpace(a[1]))
		}
	}
	// fmt.Println("namespace ret", ret)
	return ret
}

func getVar(path string, name string) map[string]string {
	body, err := os.ReadFile(path)
	if err != nil {
		panic(err.Error())
	}
	str := string(body)
	reg := regexp.MustCompile(`protected:[\{\sA-Za-z0-9_;]+\}`)
	ans := reg.FindString(str)
	// fmt.Println(ans)
	args := strings.Split(ans, "\n")
	ret := map[string]string{}
	for _, i := range args {
		i = strings.TrimSpace(i)
		if strings.Contains(i, ";") {
			// fmt.Println(i)
			a := strings.Split(i, " ")
			varName := strings.TrimSpace(a[1][:len(a[1])-1])
			varType := strings.TrimSpace(a[0])
			ret[varName] = varType
		}
	}
	return ret
}

func getInherit(path string) string {
	//
	body, err := os.ReadFile(path)
	if err != nil {
		panic(err.Error())
	}
	str := string(body)
	reg := regexp.MustCompile("public[A-Za-z\\s:_,<>0-9]+\\{")
	ans := reg.FindAllString(str, -1)

	for _, i := range ans {
		if strings.Contains(i, "public") {
			return i[:len(i)-1]
		}
	}

	fmt.Println("没有找到继承", ans)
	return ""
}

// func getHeader() map[string][]string {
// 	path := "/home/wyatt/code/fuda/OpenADR-VEN-Library-master/oadrsd/oadrsd/2b/"
// 	dir, err := os.ReadDir(path)
// 	if err != nil {
// 		panic(err.Error())
// 	}
// 	// cfg := ini.Empty()
// 	// cnt := map[string]int{}
// 	key := []string{}
// 	ret := map[string][]string{}
// 	for _, d := range dir {
// 		name := d.Name()
// 		key = append(key, name[:len(name)-4])
// 		ret[name[:len(name)-4]] = make([]string, 0)
// 	}
// 	for _, d := range dir {
//
// 		name := d.Name()
// 		if strings.HasSuffix(name, ".hxx") {
// 			body, _ := os.ReadFile(path + name)
// 			s := string(body)
// 			for _, k := range key {
// 				if strings.Contains(s, k) {
// 					ret[name[:len(name)-4]] = append(ret[name[:len(name)-4]], k)
// 				}
// 			}
// 		}
// 	}
// 	return ret
// }
