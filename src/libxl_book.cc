/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include "libxl_book.h"
#include "libxl_sheet.h"
#include "libxl_format.h"
#include "libxl_font.h"

using namespace v8;


Persistent<Function> LibxlBook::constructor;




LibxlBook::LibxlBook(int type) {
  if (type == BOOK_TYPE_XLS) {
    book = xlCreateBook();
  } else if (type == BOOK_TYPE_XLSX) {
    book = xlCreateXMLBook();
  }
}




LibxlBook::~LibxlBook() {
  book->release();
}




Handle<Value> LibxlBook::CreateBookFactory(HandleScope& scope, int type) {
  const unsigned argc = 1;
  Handle<Value> argv[argc] = { Integer::New(type) };
  Local<Object> instance = constructor->NewInstance(argc, argv);
  return scope.Close(instance);
}




Handle<Value> LibxlBook::CreateBook(const Arguments& args) {
  HandleScope scope;
  return CreateBookFactory(scope, BOOK_TYPE_XLS);
}




Handle<Value> LibxlBook::CreateXMLBook(const Arguments& args) {
  HandleScope scope;
  return CreateBookFactory(scope, BOOK_TYPE_XLSX);
}




/**
 * Constructor
 *
 * @constructor
 * @param {int} book_type
 *    Type of book: BOOK_TYPE_XLS, BOOK_TYPE_XLSX
 */
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




/**
 * Load book from given path
 *
 * @param {String} path
 *    Path of Excel file to load
 * @param {Function} cb
 *    Callback taking error as the only argument
 */
Handle<Value> LibxlBook::Load(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, path);
  REQ_FUNC_ARG(1, cb);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  const unsigned argc = 1;
  Local<Value> argv[argc];

  if (!obj->book->load(path)) {
    argv[0] = V8EXC(obj->book->errorMessage());
  } else {
    argv[0] = Local<Value>::New(Null());
  }
  cb->Call(Context::GetCurrent()->Global(), argc, argv);

  return scope.Close(Undefined());
}




/**
 * Load book from given path (sync)
 *
 * @param {String} path
 *    Path of Excel file to load
 */
Handle<Value> LibxlBook::LoadSync(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, path);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  if (!obj->book->load(path)) {
    return THREXC(obj->book->errorMessage());
  }

  return scope.Close(Undefined());
}




/**
 * Save book to given path
 *
 * @param {String} path
 *    Path to save book file
 * @param {Function} cb
 *    Callback taking error as the only argument
 */
Handle<Value> LibxlBook::Save(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, path);
  REQ_FUNC_ARG(1, cb);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  const unsigned argc = 1;
  Local<Value> argv[argc];

  if (!obj->book->save(path)) {
    argv[0] = V8EXC(obj->book->errorMessage());
  } else {
    argv[0] = Local<Value>::New(Null());
  }
  cb->Call(Context::GetCurrent()->Global(), argc, argv);

  return scope.Close(Undefined());
}




/**
 * Save book to given path (sync)
 *
 * @param {String} path
 *    Path to save book file
 */
Handle<Value> LibxlBook::SaveSync(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, path);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  if (!obj->book->save(path)) {
    return THREXC(obj->book->errorMessage());
  }

  return scope.Close(Undefined());
}




/**
 * Release book memory
 */
Handle<Value> LibxlBook::Release(const Arguments& args) {
  HandleScope scope;

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  obj->book->release();

  return scope.Close(Undefined());
}




/**
 * Set license key
 *
 * @param {String} name
 *    Customer name
 * @param {String} key
 *    License key
 */
Handle<Value> LibxlBook::SetKey(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, name);
  REQ_STR_ARG(1, key);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  obj->book->setKey(name, key);

  return scope.Close(Undefined());
}




/**
 * Get sheet from arguments
 *
 * @param {Arguments} args
 *    Arguments of some function call
 * @param {int} idx
 *    Index at which we should get sheet
 */
Sheet* LibxlBook::getSheetFromArguments(const Arguments& args, int idx) {
  Sheet* sheet;

  if (args.Length() > idx) {
    LibxlSheet* sheetObj = ObjectWrap::Unwrap<LibxlSheet>(args[idx]->ToObject());
    sheet = sheetObj->getSheet();
  } else {
    sheet = 0;
  }

  return sheet;
}




/**
 * Add new sheet
 *
 * @param {String} name
 *    Name of sheet
 * @param {Sheet} [initSheet]
 *    Initial sheet (i.e. existing)
 */
Handle<Value> LibxlBook::AddSheet(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, name);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  Sheet* initSheet = getSheetFromArguments(args, 1);
  Sheet* sheet = obj->book->addSheet(name, initSheet);

  if (sheet == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> sheetObj = LibxlSheet::NewInstance(obj->book, sheet);
  return scope.Close(sheetObj);
}




/**
 * Insert new sheet at specified index
 *
 * @param {int} idx
 *    Index to insert new sheet at
 * @param {String} name
 *    Name of sheet
 * @param {Sheet} [initSheet]
 *    Initial sheet (i.e. existing)
 */
Handle<Value> LibxlBook::InsertSheet(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, idx)
  REQ_STR_ARG(1, name);

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  Sheet* initSheet = getSheetFromArguments(args, 2);
  Sheet* sheet = obj->book->insertSheet(idx, name, initSheet);

  if (sheet == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> sheetObj = LibxlSheet::NewInstance(obj->book, sheet);
  return scope.Close(sheetObj);
}




/**
 * Get sheet at specified index
 *
 * @param {int} idx
 *    Index of sheet
 */
Handle<Value> LibxlBook::GetSheet(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, idx)

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  if (idx >= obj->book->sheetCount()) {
    return THREXC("Specified index is out of range");
  }

  Sheet* sheet = obj->book->getSheet(idx);
  if (sheet == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> sheetObj = LibxlSheet::NewInstance(obj->book, sheet);
  return scope.Close(sheetObj);
}




/**
 * Delete sheet
 *
 * @param {int}
 *    Index of sheet
 */
Handle<Value> LibxlBook::DeleteSheet(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, idx)

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());

  if (!obj->book->delSheet(idx)) {
    return THREXC(obj->book->errorMessage());
  }

  return scope.Close(Undefined());
}




/**
 * Get count of sheets in a book
 */
Handle<Value> LibxlBook::SheetCount(const Arguments& args) {
  HandleScope scope;

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  return scope.Close(Integer::New(obj->book->sheetCount()));
}




/**
 * Get format from arguments
 *
 * @param {Arguments} args
 *    Arguments of some function call
 * @param {int} idx
 *    Index at which we should get format
 */
libxl::Format* LibxlBook::getFormatFromArguments(const Arguments& args, int idx) {
  libxl::Format* format;

  if (args.Length() > idx) {
    LibxlFormat* formatObj = ObjectWrap::Unwrap<LibxlFormat>(args[idx]->ToObject());
    format = formatObj->getFormat();
  } else {
    format = 0;
  }

  return format;
}




/**
 * Add new format
 *
 * @param {Format} [initFormat]
 *    Initial format (i.e. existing)
 * @return {LibxlFormat}
 *    Format wrapper instance
 */
Handle<Value> LibxlBook::AddFormat(const Arguments& args) {
  HandleScope scope;

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  libxl::Format* initFormat = getFormatFromArguments(args, 0);
  libxl::Format* format = obj->book->addFormat(initFormat);

  if (format == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> formatObj = LibxlFormat::NewInstance(obj->book, format);
  return scope.Close(formatObj);
}




/**
 * Get format by index
 *
 * @param {int}
 *    Index of format
 * @return {LibxlFormat}
 *    Format wrapper instance
 */
Handle<Value> LibxlBook::Format(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, idx)

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  if (idx >= obj->book->formatSize()) {
    return THREXC("Specified index is out of range");
  }

  libxl::Format* format = obj->book->format(idx);
  if (format == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> formatObj = LibxlFormat::NewInstance(obj->book, format);
  return scope.Close(formatObj);
}




/**
 * Get count of formats in a book
 *
 * @return {int}
 *    Number of formats
 */
Handle<Value> LibxlBook::FormatSize(const Arguments& args) {
  HandleScope scope;

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  return scope.Close(Integer::New(obj->book->formatSize()));
}




/**
 * Get font from arguments
 *
 * @param {Arguments} args
 *    Arguments of some function call
 * @param {int} idx
 *    Index at which we should get font
 */
libxl::Font* LibxlBook::getFontFromArguments(const Arguments& args, int idx) {
  libxl::Font* font;

  if (args.Length() > idx) {
    LibxlFont* fontObj = ObjectWrap::Unwrap<LibxlFont>(args[idx]->ToObject());
    font = fontObj->getFont();
  } else {
    font = 0;
  }

  return font;
}




/**
 * Add new font
 *
 * @param {Font} [initFont]
 *    Initial font (i.e. existing)
 * @return {LibxlFont}
 *    Font wrapper instance
 */
Handle<Value> LibxlBook::AddFont(const Arguments& args) {
  HandleScope scope;

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  libxl::Font* initFont = getFontFromArguments(args, 0);
  libxl::Font* font = obj->book->addFont(initFont);

  if (font == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> fontObj = LibxlFont::NewInstance(obj->book, font);
  return scope.Close(fontObj);
}




/**
 * Get font by index
 *
 * @param {int}
 *    Index of font
 * @return {LibxlFont}
 *    Font wrapper instance
 */
Handle<Value> LibxlBook::Font(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, idx)

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  if (idx >= obj->book->fontSize()) {
    return THREXC("Specified index is out of range");
  }

  libxl::Font* font = obj->book->font(idx);
  if (font == NULL) {
    return THREXC(obj->book->errorMessage());
  }

  Handle<Value> fontObj = LibxlFont::NewInstance(obj->book, font);
  return scope.Close(fontObj);
}




/**
 * Get count of fonts in a book
 *
 * @return {int}
 *    Number of fonts
 */
Handle<Value> LibxlBook::FontSize(const Arguments& args) {
  HandleScope scope;

  LibxlBook* obj = ObjectWrap::Unwrap<LibxlBook>(args.This());
  return scope.Close(Integer::New(obj->book->fontSize()));
}




void LibxlBook::Initialize(Handle<Object> target) {
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->SetClassName(String::NewSymbol("Book"));
  t->InstanceTemplate()->SetInternalFieldCount(1);

  // base
  t->PrototypeTemplate()->Set(
    String::NewSymbol("load"),
    FunctionTemplate::New(Load)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("loadSync"),
    FunctionTemplate::New(LoadSync)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("save"),
    FunctionTemplate::New(Save)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("saveSync"),
    FunctionTemplate::New(SaveSync)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("release"),
    FunctionTemplate::New(Release)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setKey"),
    FunctionTemplate::New(SetKey)->GetFunction()
  );

  // Sheets
  t->PrototypeTemplate()->Set(
    String::NewSymbol("addSheet"),
    FunctionTemplate::New(AddSheet)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("insertSheet"),
    FunctionTemplate::New(InsertSheet)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("insertSheet"),
    FunctionTemplate::New(InsertSheet)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("getSheet"),
    FunctionTemplate::New(GetSheet)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("deleteSheet"),
    FunctionTemplate::New(DeleteSheet)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("sheetCount"),
    FunctionTemplate::New(SheetCount)->GetFunction()
  );

  // formats
  t->PrototypeTemplate()->Set(
    String::NewSymbol("addFormat"),
    FunctionTemplate::New(AddFormat)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("format"),
    FunctionTemplate::New(Format)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("formatSize"),
    FunctionTemplate::New(FormatSize)->GetFunction()
  );

  // fonts
  t->PrototypeTemplate()->Set(
    String::NewSymbol("addFont"),
    FunctionTemplate::New(AddFont)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("font"),
    FunctionTemplate::New(Font)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("fontSize"),
    FunctionTemplate::New(FontSize)->GetFunction()
  );

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Book"), constructor);

  Local<FunctionTemplate> createBook = FunctionTemplate::New(CreateBook);
  target->Set(String::NewSymbol("createBook"), createBook->GetFunction());

  Local<FunctionTemplate> createXMLBook = FunctionTemplate::New(CreateXMLBook);
  target->Set(String::NewSymbol("createXMLBook"), createXMLBook->GetFunction());

  NODE_DEFINE_CONSTANT(target, BOOK_TYPE_XLS);
  NODE_DEFINE_CONSTANT(target, BOOK_TYPE_XLSX);
}