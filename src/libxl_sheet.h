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

using namespace v8;

class LibxlSheet : public node::ObjectWrap {
  public:
    static void Initialize(Handle<Object>);
    static Handle<Value> NewInstance(unsigned, Local<Value>*);
    static Handle<Value> NewInstance(libxl::Sheet*);

    libxl::Sheet* getSheet();
  private:
    static Persistent<Function> constructor;

    static Handle<Value> New(const Arguments&);
    static Handle<Value> GetName(const Arguments&);
    static Handle<Value> SetName(const Arguments&);

    libxl::Sheet* sheet;

    LibxlSheet(libxl::Sheet*);
    ~LibxlSheet();
};

#endif