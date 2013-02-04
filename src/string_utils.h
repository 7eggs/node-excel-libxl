/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <cstdlib>
#include <cwchar>
#include <node.h>

using namespace v8;

extern Local<String> wstov8s(const wchar_t*);
extern Local<String> astov8s(const char*);

/*extern wchar_t* v8stows(String&);
extern char* v8stoas(String&);*/

#ifdef _UNICODE
  #define CHAR wchar_t

  #define stov8s wstov8s
  #define __strdup wcsdup
  /*#define v8stos v8stows*/
#else
  #define CHAR char

  #define stov8s astov8s
  #define __strdup strdup
  /*#define v8stos v8stoas*/
#endif

#endif