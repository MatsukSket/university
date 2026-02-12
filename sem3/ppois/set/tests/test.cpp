#include <UnitTest++/UnitTest++.h>
#include "Set.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

std::string capture_print(const Set& s) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    s.print();
    std::cout.rdbuf(old);
    return buffer.str();
}

// constructor
TEST(DefaultConstructor) {
    Set s;
    CHECK(s.empty());
    CHECK_EQUAL(0, s.get_power());
}

TEST(StringConstructor_EmptySet) {
    Set s("{}");
    CHECK(s.empty());
    CHECK_EQUAL(0, s.get_power());
}

TEST(StringConstructor_SimpleElements) {
    Set s("{a, b, c}");
    CHECK(!s.empty());
    CHECK_EQUAL(3, s.get_power());
    CHECK(s["a"]);
    CHECK(s["b"]);
    CHECK(s["c"]);
    CHECK(!s["d"]);
}

TEST(StringConstructor_NestedSets) {
    Set s("{{a}, {b, c}}");
    CHECK_EQUAL(2, s.get_power());
    Set sub1("{a}");
    Set sub2("{b, c}");
    CHECK(s[sub1]);
    CHECK(s[sub2]);
}

TEST(StringConstructor_Mixed) {
    Set s("{x, {y}, z}");
    CHECK_EQUAL(3, s.get_power());
    CHECK(s["x"]);
    CHECK(s["z"]);
    Set y("{y}");
    CHECK(s[y]);
}

TEST(StringConstructor_WhitespaceIgnored) {
    Set s("{ a , { b } }");
    CHECK_EQUAL(2, s.get_power());
    CHECK(s["a"]);
    Set b("{b}");
    CHECK(s[b]);
}

TEST(StringConstructor_Invalid_BadBraces) {
    CHECK_THROW(Set("{"), std::invalid_argument);
    CHECK_THROW(Set("}"), std::invalid_argument); 
    CHECK_THROW(Set("{{}"), std::invalid_argument);
    CHECK_THROW(Set("}{}"), std::invalid_argument);
    CHECK_THROW(Set("{}{"), std::invalid_argument);
    CHECK_THROW(Set("}{"), std::invalid_argument);
    CHECK_THROW(Set("{a, }"), std::invalid_argument);
    CHECK_THROW(Set("{, a}"), std::invalid_argument);
    CHECK_THROW(Set("{a,,b}"), std::invalid_argument);
    CHECK_THROW(Set("}a{"), std::invalid_argument);
    CHECK_THROW(Set("{a}{b}"), std::invalid_argument);
    CHECK_THROW(Set("{a}b"), std::invalid_argument);
    CHECK_THROW(Set("a{b}"), std::invalid_argument);
}

TEST(StringConstructor_EmptyInput) {
    Set s("");
    CHECK(s.empty());
}

TEST(CharPtrConstructor) {
    Set s("{hello}");
    Set t("{hello}");
    CHECK(s == t);
}


// add_el
TEST(AddElement_String) {
    Set s;
    s.add_el("x");
    CHECK(s["x"]);
    CHECK_EQUAL(1, s.get_power());
    s.add_el("x");
    CHECK_EQUAL(1, s.get_power());
}

TEST(AddElement_Set) {
    Set inner("{a}");
    Set s;
    s.add_el(inner);
    CHECK(s[inner]);
    CHECK_EQUAL(1, s.get_power());
    s.add_el(inner);
    CHECK_EQUAL(1, s.get_power());
}

TEST(AddDuplicateStringAndSet) {
    Set s;
    s.add_el("x");
    s.add_el("x");
    Set sub("{y}");
    s.add_el(sub);
    s.add_el(sub);
    CHECK_EQUAL(2, s.get_power());
}


// delete_el
TEST(DeleteElement_String) {
    Set s("{a, b}");
    s.delete_el("a");
    CHECK(!s["a"]);
    CHECK(s["b"]);
    CHECK_EQUAL(1, s.get_power());
}

TEST(DeleteElement_Set) {
    Set inner("{x}");
    Set s("{y, {x}}");
    s.delete_el(inner);
    CHECK(!s[inner]);
    CHECK(s["y"]);
    CHECK_EQUAL(1, s.get_power());
}

TEST(DeleteFromEmptySet_String) {
    Set s;
    s.delete_el("x"); 
    CHECK(s.empty());
}

TEST(DeleteFromEmptySet_Set) {
    Set s;
    Set x("{a}");
    s.delete_el(x);
    CHECK(s.empty());
}


// ==, !=
TEST(Equality_SameElements) {
    Set s1("{a, b}");
    Set s2("{b, a}");
    CHECK(s1 == s2);
}

TEST(Equality_DifferentElements) {
    Set s1("{a}");
    Set s2("{b}");
    CHECK(s1 != s2);
}

TEST(Equality_Nested) {
    Set s1("{{a}, b}");
    Set s2("{b, {a}}");
    CHECK(s1 == s2);
}


// []
TEST(Membership_String) {
    Set s("{hello}");
    CHECK(s["hello"]);
    CHECK(!s["world"]);
}

TEST(Membership_Set) {
    Set inner("{x}");
    Set s("{{x}}");
    CHECK(s[inner]);
    Set other("{y}");
    CHECK(!s[other]);
}

TEST(Membership_NonExistent) {
    Set s("{a}");
    CHECK(!s["b"]);
    Set sub("{b}");
    CHECK(!s[sub]);
}


// Set operations
TEST(Union) {
    Set s1("{a}");
    Set s2("{b}");
    Set res = s1 + s2;
    CHECK(res["a"]);
    CHECK(res["b"]);
    CHECK_EQUAL(2, res.get_power());
}

TEST(UnionEquals) {
    Set s("{a}");
    Set t("{a, b}");
    s += t;
    CHECK_EQUAL(2, s.get_power());
    CHECK(s["a"]);
    CHECK(s["b"]);
}

TEST(Difference) {
    Set s1("{a, b, c}");
    Set s2("{b, d}");
    Set res = s1 - s2;
    CHECK(res["a"]);
    CHECK(res["c"]);
    CHECK(!res["b"]);
    CHECK_EQUAL(2, res.get_power());
}

TEST(DifferenseEquals) {
    Set s("{a}");
    Set t("{b}");
    s -= t;
    CHECK_EQUAL(1, s.get_power());
    CHECK(s["a"]);
}

TEST(Intersection) {
    Set s1("{a, b, {x}}");
    Set s2("{b, c, {x}}");
    Set res = s1 * s2;
    CHECK(res["b"]);
    Set x("{x}");
    CHECK(res[x]);
    CHECK_EQUAL(2, res.get_power());
}

TEST(IntersectionEquals) {
    Set s("{a}");
    Set t("{b}");
    s *= t; 
    CHECK(s.empty());
}

TEST(SymmetricDifference) {
    Set s1("{a, b}");
    Set s2("{b, c}");
    Set res = s1 / s2;
    CHECK(res["a"]);
    CHECK(res["c"]);
    CHECK(!res["b"]);
    CHECK_EQUAL(2, res.get_power());
}

TEST(GetPower) {
    Set s("{a, {b}, c}");
    CHECK_EQUAL(3, s.get_power());
}

TEST(Empty) {
    Set s;
    CHECK(s.empty());
    s.add_el("x");
    CHECK(!s.empty());
}

TEST(Print) {
    Set s("{a, {b}}");
    std::string out = capture_print(s);
    CHECK(out.find("a") != std::string::npos);
    CHECK(out.find("{ b }") != std::string::npos);
}


// boolean
TEST(Boolean_Empty) {
    Set s;
    Set bs = s.boolean();
    CHECK_EQUAL(1, bs.get_power());
    Set empty;
    CHECK(bs[empty]);
}

TEST(Boolean_Singleton) {
    Set s("{x}");
    Set bs = s.boolean();
    CHECK_EQUAL(2, bs.get_power());
    Set empty;
    Set with_x("{x}");
    CHECK(bs[empty]);
    CHECK(bs[with_x]);
}

TEST(Boolean_WithEmptySubset) {
    Set empty;
    Set s;
    s.add_el(empty);
    Set bs = s.boolean();
    CHECK_EQUAL(2, bs.get_power());
    Set empty2;
    Set with_empty;
    with_empty.add_el(empty);
    CHECK(bs[empty2]);
    CHECK(bs[with_empty]);
}


// is_valid_string
TEST(InvalidString_Case1_BraceAfterBrace) {
    CHECK_THROW(Set("}{}"), std::invalid_argument); 
    CHECK_THROW(Set("}{"), std::invalid_argument);
}

TEST(InvalidString_Case2_CommaBeforeClosing) {
    CHECK_THROW(Set("{,}"), std::invalid_argument); 
    CHECK_THROW(Set("{a,}"), std::invalid_argument); 
}

TEST(InvalidString_Case3_DoubleComma) {
    CHECK_THROW(Set("{a,,b}"), std::invalid_argument);
}

TEST(InvalidString_Case4_ClosingFollowedByNonComma) {
    CHECK_THROW(Set("{a}b"), std::invalid_argument);
    CHECK_THROW(Set("{a} {b}"), std::invalid_argument);
}

TEST(InvalidString_Case5_OpeningAfterNonOpeningNonComma) {
    CHECK_THROW(Set("a{b}"), std::invalid_argument);
    CHECK_THROW(Set("{a}x{b}"), std::invalid_argument);
}


// other tests
TEST(DeepNesting) {
    Set s("{{{{a}}}}");
    Set level3("{{{a}}}");
    CHECK(s[level3]);
}

TEST(CharPtrNull) {
    Set s((char*)nullptr);
    CHECK(s.empty());
}

TEST(ValidDeepEmptySet) {
    Set s("{{}}");
    CHECK_EQUAL(1, s.get_power());
    Set empty;
    CHECK(s[empty]);
}

TEST(Parse_EmptyInnerSet) {
    Set s("{{}, a}");
    CHECK_EQUAL(2, s.get_power());
    Set empty;
    CHECK(s[empty]);
    CHECK(s["a"]);
}

TEST(Print_EmptySet) {
    Set s;
    std::string out = capture_print(s);
    CHECK_EQUAL("{  }", out);
}

TEST(GetPower_AfterDeletion) {
    Set s("{a, b}");
    s.delete_el("a");
    CHECK_EQUAL(1, s.get_power());
}

TEST(InvalidString_TooShort) {
    CHECK_THROW(Set("a"), std::invalid_argument);
}

int main() {
    return UnitTest::RunAllTests();
}

