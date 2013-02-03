/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef LIBXL_BINDINGS_H_
#define LIBXL_BINDINGS_H_

#define REQ_INT_ARG(I, VAR) \
  if (args.Length() <= (I) || !args[I]->IsInt32()) \
  return ThrowException(Exception::TypeError( \
  String::New("Argument " #I " must be an integer"))); \
  int32_t VAR = args[I]->Int32Value();

#define THREXC(str) \
  ThrowException(Exception::Error(String::New(str)))

#endif