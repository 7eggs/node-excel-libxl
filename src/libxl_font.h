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

class LibxlFont : public node::ObjectWrap {
  public:
    static void Initialize(Handle<Object>);
    static Handle<Value> NewInstance(unsigned, Local<Value>*);
    static Handle<Value> NewInstance(libxl::Book*, libxl::Font*);

    libxl::Font* getFont();
  private:
    static Persistent<Function> constructor;

    static Handle<Value> New(const Arguments&);
    static Handle<Value> Size(const Arguments&);
    static Handle<Value> SetSize(const Arguments&);
    static Handle<Value> Italic(const Arguments&);
    static Handle<Value> SetItalic(const Arguments&);
    static Handle<Value> StrikeOut(const Arguments&);
    static Handle<Value> SetStrikeOut(const Arguments&);
    static Handle<Value> Color(const Arguments&);
    static Handle<Value> SetColor(const Arguments&);
    static Handle<Value> Bold(const Arguments&);
    static Handle<Value> SetBold(const Arguments&);
    static Handle<Value> Script(const Arguments&);
    static Handle<Value> SetScript(const Arguments&);
    static Handle<Value> Underline(const Arguments&);
    static Handle<Value> SetUnderline(const Arguments&);
    static Handle<Value> Name(const Arguments&);
    static Handle<Value> SetName(const Arguments&);

    libxl::Font* font;
    libxl::Book* book;

    LibxlFont(libxl::Book*, libxl::Font*);
    ~LibxlFont();
};

#endif