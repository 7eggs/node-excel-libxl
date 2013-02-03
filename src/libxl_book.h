/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef LIBXL_BOOK_H_
#define LIBXL_BOOK_H_

#include <node.h>
#include <libxl.h>
#include "libxl_bindings.h"

using namespace v8;

class LibxlBook : public node::ObjectWrap {
  public:
    static void Initialize(Handle<Object>);

  private:
    LibxlBook(int);
    ~LibxlBook();

    static Handle<Value> New(const Arguments&);
    static Handle<Value> CreateBookFactory(HandleScope&, int);
    static Handle<Value> CreateBook(const Arguments&);
    static Handle<Value> CreateXMLBook(const Arguments&);

    libxl::Book* book;
    static Persistent<Function> constructor;
};

#endif
