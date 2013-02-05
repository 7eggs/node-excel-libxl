/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include "libxl_font.h"

using namespace v8;
using namespace libxl;

Persistent<Function> LibxlFont::constructor;





Handle<Value> LibxlFont::NewInstance(Book* book, Font* font) {
  const unsigned argc = 2;
  Local<Value> argv[argc] = {
    External::Wrap((void*) book),
    External::Wrap((void*) font)
  };
  return constructor->NewInstance(argc, argv);
}




Handle<Value> LibxlFont::NewInstance(unsigned argc, Local<Value>* argv) {
  return constructor->NewInstance(argc, argv);
}




LibxlFont::LibxlFont(Book* book, Font* font) {
  this->book = book;
  this->font = font;
}




LibxlFont::~LibxlFont() {
  this->font = NULL;
  this->book = NULL;
}




/**
 * Getter for real font instance
 */
Font* LibxlFont::getFont() {
  return font;
}




/**
 * Create new Font instance
 *
 * @constructor
 * @param {Book} book
 *    Book instance (wrapped into v8::External)
 * @param {Font} font
 *    Font instance (wrapped into v8::External)
 */
Handle<Value> LibxlFont::New(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    return THREXC("No font object specified for Font constructor");
  } else {
    Book* book = (Book*) External::Unwrap(args[0]);
    Font* font = (Font*) External::Unwrap(args[1]);

    LibxlFont* obj = new LibxlFont(book, font);
    obj->Wrap(args.This());
    return args.This();
  }
}




void LibxlFont::Initialize(Handle<Object> target) {
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->SetClassName(String::NewSymbol("Font"));
  t->InstanceTemplate()->SetInternalFieldCount(1);

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Font"), constructor);
}