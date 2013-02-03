/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include <node.h>
#include "libxl_book.h"

using namespace v8;

enum {
  BOOK_TYPE_XLS,
  BOOK_TYPE_XLSX
};


Persistent<Function> LibxlBook::constructor;


Handle<Value> LibxlBook::CreateBookFactory(HandleScope& scope, int type) {
  const unsigned argc = 1;
  Handle<Value> argv[argc] = { Integer::New(type) };
  Local<Object> instance = constructor->NewInstance(argc, argv);
  return scope.Close(instance);
}


LibxlBook::LibxlBook(int type) {
  if (type == BOOK_TYPE_XLS) {
    book = xlCreateBook();
  } else if (type == BOOK_TYPE_XLSX) {
    book = xlCreateXMLBook();
  }
}


LibxlBook::~LibxlBook() {
  book->release();
  delete[] book;
}


Handle<Value> LibxlBook::New(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, book_type);

  if (book_type != BOOK_TYPE_XLS && book_type != BOOK_TYPE_XLSX) {
    return THREXC("Unknown book type");
  }

  LibxlBook* bookObject = new LibxlBook(book_type);
  bookObject->Wrap(args.This());
  return args.This();
}


Handle<Value> LibxlBook::CreateBook(const Arguments& args) {
  HandleScope scope;
  return CreateBookFactory(scope, BOOK_TYPE_XLS);
}


Handle<Value> LibxlBook::CreateXMLBook(const Arguments& args) {
  HandleScope scope;
  return CreateBookFactory(scope, BOOK_TYPE_XLSX);
}


void LibxlBook::Initialize(Handle<Object> target) {
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->SetClassName(String::NewSymbol("Book"));
  t->InstanceTemplate()->SetInternalFieldCount(1);

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Book"), constructor);

  Local<FunctionTemplate> createBook = FunctionTemplate::New(CreateBook);
  target->Set(String::NewSymbol("createBook"), createBook->GetFunction());

  Local<FunctionTemplate> createXMLBook = FunctionTemplate::New(CreateXMLBook);
  target->Set(String::NewSymbol("createXMLBook"), createXMLBook->GetFunction());

  NODE_DEFINE_CONSTANT(target, BOOK_TYPE_XLS);
  NODE_DEFINE_CONSTANT(target, BOOK_TYPE_XLSX);
}