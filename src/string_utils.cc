/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include "string_utils.h"


Local<String> wstov8s(const wchar_t* str) {
  size_t length = wcslen(str);
  char* buf = new char[length];
  wcstombs(buf, str, length);

  Local<String> v8str = String::New(buf);
  delete[] buf;

  return v8str;
}


Local<String> astov8s(const char* str) {
  return String::New(str);
}



/*
wchar_t* v8stows(String v8str) {
  size_t length = v8str->Length();
  wchar_t str[length];
  mbstowcs(str, strdup(*v8str), length);
}


char* v8stoas(String v8str) {
  return strdup(*v8str));
}*/
