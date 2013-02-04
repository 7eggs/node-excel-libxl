/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include "libxl_sheet.h"

using namespace v8;

Persistent<Function> LibxlSheet::constructor;




LibxlSheet::LibxlSheet(libxl::Sheet* sheet) {
  this->sheet = sheet;
}




LibxlSheet::~LibxlSheet() {
  delete[] sheet;
}

libxl::Sheet* LibxlSheet::getSheet() {
  return sheet;
}




Handle<Value> LibxlSheet::New(const Arguments& args) {
  HandleScope scope;

  if (args.Length() == 0) {
    return THREXC("No sheet object specified for Sheet constructor");
  } else {
    libxl::Sheet* sheet = (libxl::Sheet*) External::Unwrap(args[0]);
    LibxlSheet* sheetObj = new LibxlSheet(sheet);
    sheetObj->Wrap(args.This());
    return args.This();
  }
}




Handle<Value> LibxlSheet::GetName(const Arguments& args) {
  HandleScope scope;

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());
  const CHAR* name = obj->sheet->name();

  return scope.Close(stov8s(name));
}




Handle<Value> LibxlSheet::SetName(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, newName);

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());
  obj->sheet->setName(newName);

  return scope.Close(Undefined());
}




Handle<Value> LibxlSheet::NewInstance(libxl::Sheet* sheet) {
  const unsigned argc = 1;
  Local<Value> argv[argc] = { External::Wrap((void*) sheet) };
  return constructor->NewInstance(argc, argv);
}




Handle<Value> LibxlSheet::NewInstance(unsigned argc, Local<Value>* argv) {
  return constructor->NewInstance(argc, argv);
}




void LibxlSheet::Initialize(Handle<Object> target) {
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->SetClassName(String::NewSymbol("Sheet"));
  t->InstanceTemplate()->SetInternalFieldCount(1);

  t->PrototypeTemplate()->Set(
    String::NewSymbol("getName"),
    FunctionTemplate::New(GetName)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setName"),
    FunctionTemplate::New(SetName)->GetFunction()
  );

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Sheet"), constructor);
}