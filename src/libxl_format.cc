/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include "libxl_format.h"

using namespace v8;
using namespace libxl;

Persistent<Function> LibxlFormat::constructor;





Handle<Value> LibxlFormat::NewInstance(Book* book, Format* format) {
  const unsigned argc = 2;
  Local<Value> argv[argc] = {
    External::Wrap((void*) book),
    External::Wrap((void*) format)
  };
  return constructor->NewInstance(argc, argv);
}




Handle<Value> LibxlFormat::NewInstance(unsigned argc, Local<Value>* argv) {
  return constructor->NewInstance(argc, argv);
}




LibxlFormat::LibxlFormat(Book* book, Format* format) {
  this->book = book;
  this->format = format;
}




LibxlFormat::~LibxlFormat() {
  this->format = NULL;
  this->book = NULL;
}




/**
 * Getter for real format instance
 */
Format* LibxlFormat::getFormat() {
  return format;
}




/**
 * Create new Format instance
 *
 * @constructor
 * @param {Book} book
 *    Book instance (wrapped into v8::External)
 * @param {Format} format
 *    Format instance (wrapped into v8::External)
 */
Handle<Value> LibxlFormat::New(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    return THREXC("No format object specified for Format constructor");
  } else {
    Book* book = (Book*) External::Unwrap(args[0]);
    Format* format = (Format*) External::Unwrap(args[1]);

    LibxlFormat* obj = new LibxlFormat(book, format);
    obj->Wrap(args.This());
    return args.This();
  }
}




void LibxlFormat::Initialize(Handle<Object> target) {
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->SetClassName(String::NewSymbol("Format"));
  t->InstanceTemplate()->SetInternalFieldCount(1);

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Format"), constructor);
}