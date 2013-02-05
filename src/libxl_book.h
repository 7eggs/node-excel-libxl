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
    static libxl::Sheet* getSheetFromArguments(const Arguments&, int);
    static libxl::Format* getFormatFromArguments(const Arguments&, int);
    static libxl::Font* getFontFromArguments(const Arguments&, int);

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

    static Handle<Value> AddSheet(const Arguments&);
    static Handle<Value> InsertSheet(const Arguments&);
    static Handle<Value> GetSheet(const Arguments&);
    static Handle<Value> DeleteSheet(const Arguments&);
    static Handle<Value> SheetCount(const Arguments&);

    static Handle<Value> AddFormat(const Arguments&);
    static Handle<Value> Format(const Arguments&);
    static Handle<Value> FormatSize(const Arguments&);
    static Handle<Value> AddCustomNumFormat(const Arguments&);
    static Handle<Value> CustomNumFormat(const Arguments&);

    static Handle<Value> AddFont(const Arguments&);
    static Handle<Value> Font(const Arguments&);
    static Handle<Value> FontSize(const Arguments&);

    libxl::Book* book;

    LibxlBook(int);
    ~LibxlBook();
};

#endif
