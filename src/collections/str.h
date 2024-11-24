#pragma once
#include <cstring>
#include <iostream>
#include "vec.h"

namespace str {
struct String {
    char* data;
    size_t size;
};

String NewString();
String FromCStr(char* s);
String FromStaticCStr(const char* s);
String FromVec(const vec::Vec<char>& vector);

char* AsCStr(const String& s);
char GetChar(const String& s, size_t idx);
size_t Len(const String& s);

String Joined(const vec::Vec<String>& str_vec);
String Slice(const String& s, size_t start);
String Slice(const String& s, size_t start, size_t end);

vec::Vec<String> GroupedBy(const String& s, size_t group_size);
vec::Vec<String> Split(String s);
vec::Vec<String> Split(String s, String delimeter);

bool Equals(String s1, String s2);
bool StartsWith(String s, String prefix);

}  // namespace str
