// RUN: %check_clang_tidy %s fmt-unnecessary-cstr %t

// check_clang_tidy can't find C++ headers, so we have to make do with something
// else #include <string>
namespace std {

    template<typename CharType>
    struct basic_string {
    const char *c_str() const;
    };

    using string = basic_string<char>;
//    using wstring = basic_string<wchar_t>;
    // struct string {
    // const char *c_str() const;
//};
}

namespace fmt {
    template<typename ...Args>
    void print(const char *, Args...);
}

namespace notfmt {
    template<typename ...Args>
    void print(const char *, Args...);
}

void fmt_print(const std::string &s1, std::string s2) {
    fmt::print("One:{} Two:{}\n", s1.c_str(), s2.c_str());
  // CHECK-MESSAGES: [[@LINE-1]]:3: warning: Remove unnecessary call to c_str() [fmt-unnecessary-cstr]
  // CHECK-FIXES: fmt::print("One:{} Two:{}\n", s1, s2);
}

void fmt_print_pointers(const std::string *s1, std::string *s2) {
    fmt::print("One:{} Two:{}\n", s1->c_str(), s2->c_str());
  // CHECK-MESSAGES: [[@LINE-1]]:3: warning: Remove unnecessary call to c_str() [fmt-unnecessary-cstr]
  // CHECK-FIXES: fmt::print("One:{} Two:{}\n", *s1, *s2);
}

const std::string &get_s1();
std::string get_s2();

void fmt_print_functions() {
    fmt::print("One:{} Two:{}\n", get_s1().c_str(), get_s2().c_str());
  // CHECK-MESSAGES: [[@LINE-1]]:3: warning: Remove unnecessary call to c_str() [fmt-unnecessary-cstr]
  // CHECK-FIXES: fmt::print("One:{} Two:{}\n", *s1, *s2);}
}

const std::string *get_s1_pointer();
std::string *get_s2_pointer();

void fmt_print_pointers_functions() {
    fmt::print("One:{} Two:{}\n", get_s1_pointer()->c_str(), get_s2_pointer()->c_str());
  // CHECK-MESSAGES: [[@LINE-1]]:3: warning: Remove unnecessary call to c_str() [fmt-unnecessary-cstr]
  // CHECK-FIXES: fmt::print("One:{} Two:{}\n", *get_s1_pointer(), *get_s2_pointer());
}

void not_fmt(const std::string &s1) {
    notfmt::print("One: {}\n", s1.c_str());
}
