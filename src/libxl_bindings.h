/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef LIBXL_BINDINGS_H_
#define LIBXL_BINDINGS_H_

#include <cstdlib>
#include "string_utils.h"

#ifdef _UNICODE
  #define REQ_STR_ARG(I, VAR) \
    if (args.Length() <= (I) || !args[I]->IsString()) \
    return ThrowException(Exception::TypeError( \
    String::New("Argument " #I " must be a string"))); \
    wchar_t* VAR[args[I]->ToString()->Length()]; \
    mbstowcs(VAR, strdup(*(String::Utf8Value(args[I]->ToString()))), args[I]->ToString()->Length());
#else
  #define REQ_STR_ARG(I, VAR) \
    if (args.Length() <= (I) || !args[I]->IsString()) \
    return ThrowException(Exception::TypeError( \
    String::New("Argument " #I " must be a string"))); \
    char* VAR = strdup(*(String::Utf8Value(args[I]->ToString())));
#endif


#define V8EXC(str) Exception::Error(String::New(str))
#define THREXC(str) ThrowException(Exception::Error(String::New(str)));

#define REQ_INT_ARG(I, VAR) \
  if (args.Length() <= (I) || !args[I]->IsInt32()) \
  return ThrowException(Exception::TypeError( \
  String::New("Argument " #I " must be an integer"))); \
  int32_t VAR = args[I]->Int32Value();



#define REQ_FUNC_ARG(I, VAR) \
  if (args.Length() <= (I) || !args[I]->IsFunction()) \
  return ThrowException(Exception::TypeError( \
  String::New("Argument " #I " must be a function"))); \
  Local<Function> VAR = Local<Function>::Cast(args[I]);

#endif