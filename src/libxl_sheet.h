/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#ifndef LIBXL_SHEET_H_
#define LIBXL_SHEET_H_

#include <node.h>
#include <libxl.h>
#include "libxl_bindings.h"
#include "libxl_book.h"

using namespace v8;
using namespace libxl;

class LibxlSheet : public node::ObjectWrap {
  public:
    static void Initialize(Handle<Object>);
    static Handle<Value> NewInstance(unsigned, Local<Value>*);
    static Handle<Value> NewInstance(Book*, Sheet*);

    Sheet* getSheet();
  private:
    static Persistent<Function> constructor;

    static Handle<Value> New(const Arguments&);
    static Handle<Value> GetName(const Arguments&);
    static Handle<Value> SetName(const Arguments&);

    static Handle<Value> CellType(const Arguments&);
    static Handle<Value> ReadString(const Arguments&);
    static Handle<Value> WriteString(const Arguments&);

    Sheet* sheet;
    Book* book;

    LibxlSheet(Book*, Sheet*);
    ~LibxlSheet();
};

#endif