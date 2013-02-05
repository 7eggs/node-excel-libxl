/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef LIBXL_FONT_H_
#define LIBXL_FONT_H_

#include <node.h>
#include <libxl.h>
#include "libxl_bindings.h"
#include "libxl_book.h"

using namespace v8;
using namespace libxl;

class LibxlFont : public node::ObjectWrap {
  public:
    static void Initialize(Handle<Object>);
    static Handle<Value> NewInstance(unsigned, Local<Value>*);
    static Handle<Value> NewInstance(Book*, Font*);

    Font* getFont();
  private:
    static Persistent<Function> constructor;

    static Handle<Value> New(const Arguments&);

    Font* font;
    Book* book;

    LibxlFont(Book*, Font*);
    ~LibxlFont();
};

#endif