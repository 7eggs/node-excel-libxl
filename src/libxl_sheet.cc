/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include "libxl_sheet.h"

using namespace v8;
using namespace libxl;

Persistent<Function> LibxlSheet::constructor;





Handle<Value> LibxlSheet::NewInstance(Book* book, Sheet* sheet) {
  const unsigned argc = 2;
  Local<Value> argv[argc] = {
    External::Wrap((void*) book),
    External::Wrap((void*) sheet)
  };
  return constructor->NewInstance(argc, argv);
}




Handle<Value> LibxlSheet::NewInstance(unsigned argc, Local<Value>* argv) {
  return constructor->NewInstance(argc, argv);
}




LibxlSheet::LibxlSheet(Book* book, Sheet* sheet) {
  this->book = book;
  this->sheet = sheet;
}




LibxlSheet::~LibxlSheet() {
  this->sheet = NULL;
  this->book = NULL;
}




/**
 * Getter for real sheet instance
 */
Sheet* LibxlSheet::getSheet() {
  return sheet;
}




/**
 * Create new Sheet instance
 *
 * @constructor
 * @param {Book} book
 *    Book instance (wrapped into v8::External)
 * @param {Sheet} sheet
 *    Sheet instance (wrapped into v8::External)
 */
Handle<Value> LibxlSheet::New(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    return THREXC("No sheet object specified for Sheet constructor");
  } else {
    Book* book = (Book*) External::Unwrap(args[0]);
    Sheet* sheet = (Sheet*) External::Unwrap(args[1]);

    LibxlSheet* obj = new LibxlSheet(book, sheet);
    obj->Wrap(args.This());
    return args.This();
  }
}




/**
 * Get name of sheet
 *
 * @return {String}
 */
Handle<Value> LibxlSheet::GetName(const Arguments& args) {
  HandleScope scope;

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());
  const CHAR* name = obj->sheet->name();

  return scope.Close(stov8s(name));
}




/**
 * Set name of sheet
 *
 * @param {String} newName
 *    New name of sheet
 */
Handle<Value> LibxlSheet::SetName(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, newName);

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());
  obj->sheet->setName(newName);

  return scope.Close(Undefined());
}




/**
 * Get type of cell at given position
 *
 * @param {int} row
 *    Cell row number
 * @param {int} col
 *    Cell column number
 * @return {int} Type of cell
 */
Handle<Value> LibxlSheet::CellType(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, row);
  REQ_INT_ARG(1, col);

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());

  int type = obj->sheet->cellType(row, col);
  return scope.Close(Integer::New(type));
}




Handle<Value> LibxlSheet::ReadString(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, row);
  REQ_INT_ARG(1, col);

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());

  // TODO update when Format API implemented
  const CHAR* data = obj->sheet->readStr(row, col, 0);
  if (data == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  // __strdup is done because documentation says that data can be lost when
  // book->release() is done
  return scope.Close(stov8s(__strdup(data)));
}




Handle<Value> LibxlSheet::WriteString(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, row);
  REQ_INT_ARG(1, col);
  REQ_STR_ARG(2, str);

  LibxlSheet* obj = ObjectWrap::Unwrap<LibxlSheet>(args.This());

  // TODO update when Format API implemented
  if (!obj->sheet->writeStr(row, col, str, 0)) {
    return THREXC(obj->book->errorMessage());
  }

  return scope.Close(Undefined());
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

  // cells
  t->PrototypeTemplate()->Set(
    String::NewSymbol("cellType"),
    FunctionTemplate::New(CellType)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("readString"),
    FunctionTemplate::New(ReadString)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("writeString"),
    FunctionTemplate::New(WriteString)->GetFunction()
  );

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Sheet"), constructor);

  NODE_DEFINE_CONSTANT(target, CELLTYPE_EMPTY);
  NODE_DEFINE_CONSTANT(target, CELLTYPE_NUMBER);
  NODE_DEFINE_CONSTANT(target, CELLTYPE_STRING);
  NODE_DEFINE_CONSTANT(target, CELLTYPE_BOOLEAN);
  NODE_DEFINE_CONSTANT(target, CELLTYPE_BLANK);
  NODE_DEFINE_CONSTANT(target, CELLTYPE_ERROR);
}