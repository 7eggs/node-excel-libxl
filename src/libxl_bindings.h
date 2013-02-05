/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef LIBXL_BINDINGS_H_
#define LIBXL_BINDINGS_H_

#include <cstdlib>
#include <libxl.h>
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


#define REQ_BOOL_ARG(I, VAR) \
  if (args.Length() <= (I) || !args[I]->IsBoolean()) \
  return ThrowException(Exception::TypeError( \
  String::New("Argument " #I " must be a boolean"))); \
  bool VAR = args[I]->BooleanValue();


#define REQ_FUNC_ARG(I, VAR) \
  if (args.Length() <= (I) || !args[I]->IsFunction()) \
  return ThrowException(Exception::TypeError( \
  String::New("Argument " #I " must be a function"))); \
  Local<Function> VAR = Local<Function>::Cast(args[I]);


#define COLOR_IS_VALID(color) \
  if (color < COLOR_BLACK || \
  (color > COLOR_GRAY80 && \
  color != COLOR_DEFAULT_FOREGROUND && \
  color != COLOR_DEFAULT_BACKGROUND && \
  color != COLOR_TOOLTIP && \
  color != COLOR_AUTO)) \
  return THREXC("Unknown color identifier");


#define UNDERLINE_IS_VALID(ul) \
  if (ul < UNDERLINE_NONE || \
  (ul > UNDERLINE_DOUBLE && \
  ul != UNDERLINE_SINGLEACC && \
  ul != UNDERLINE_DOUBLEACC)) \
  return THREXC("Unknown underline identifier");


#define SCRIPT_IS_VALID(script) \
  if ( \
  script != SCRIPT_NORMAL && \
  script != SCRIPT_SUPER && \
  script != SCRIPT_SUB) \
  return THREXC("Unknown script identifier");

#endif