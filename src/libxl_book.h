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

enum {
  BOOK_TYPE_XLS,
  BOOK_TYPE_XLSX
};

class LibxlBook : public node::ObjectWrap {
  public:
    static void Initialize(Handle<Object>);

  private:
    static Persistent<Function> constructor;

    static Handle<Value> CreateBookFactory(HandleScope&, int);
    static Handle<Value> CreateBook(const Arguments&);
    static Handle<Value> CreateXMLBook(const Arguments&);

    static Handle<Value> New(const Arguments&);
    static Handle<Value> Load(const Arguments&);
    static Handle<Value> LoadSync(const Arguments&);
    static Handle<Value> Save(const Arguments&);
    static Handle<Value> SaveSync(const Arguments&);
    static Handle<Value> Release(const Arguments&);
    static Handle<Value> SetKey(const Arguments&);

    static libxl::Sheet* getSheetFromArguments(const Arguments&, int);
    static Handle<Value> AddSheetSync(const Arguments&);
    static Handle<Value> InsertSheetSync(const Arguments&);
    static Handle<Value> GetSheetSync(const Arguments&);
    static Handle<Value> DeleteSheetSync(const Arguments&);
    static Handle<Value> SheetCountSync(const Arguments&);

    libxl::Book* book;

    LibxlBook(int);
    ~LibxlBook();
};

#endif
