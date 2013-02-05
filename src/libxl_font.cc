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




/**
 * Get size of font
 *
 * @return {int}
 *    Size in points
 */
Handle<Value> LibxlFont::Size(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Integer::New(obj->font->size()));
}




/**
 * Set size of font
 *
 * @param {int} size
 *    Size in points
 */
Handle<Value> LibxlFont::SetSize(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, size);
  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setSize(size);
  return scope.Close(Undefined());
}




/**
 * Get state of italic
 *
 * @return {boolean}
 *    State of italic
 */
Handle<Value> LibxlFont::Italic(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Boolean::New(obj->font->italic()));
}




/**
 * Set state of italic
 *
 * @param {boolean} italic
 *    State
 */
Handle<Value> LibxlFont::SetItalic(const Arguments& args) {
  HandleScope scope;

  REQ_BOOL_ARG(0, italic);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setItalic(italic);
  return scope.Close(Undefined());
}




/**
 * Get state of strikeout
 *
 * @return {boolean}
 *    State of strikeout
 */
Handle<Value> LibxlFont::StrikeOut(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Boolean::New(obj->font->strikeOut()));
}




/**
 * Set state of strikeout
 *
 * @param {boolean} strikeout
 *    State
 */
Handle<Value> LibxlFont::SetStrikeOut(const Arguments& args) {
  HandleScope scope;

  REQ_BOOL_ARG(0, strikeout);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setStrikeOut(strikeout);
  return scope.Close(Undefined());
}




/**
 * Get color of font
 *
 * @return {int}
 *    Color as integer
 */
Handle<Value> LibxlFont::Color(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Integer::New(obj->font->color()));
}




/**
 * Set color of font
 *
 * @param {int} color
 *    Color as int
 */
Handle<Value> LibxlFont::SetColor(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, color);
  COLOR_IS_VALID(color);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setColor((libxl::Color) color);
  return scope.Close(Undefined());
}




/**
 * Get state of bold
 *
 * @return {boolean}
 *    State of bold
 */
Handle<Value> LibxlFont::Bold(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Boolean::New(obj->font->bold()));
}




/**
 * Set state of bold
 *
 * @param {boolean} bold
 *    State
 */
Handle<Value> LibxlFont::SetBold(const Arguments& args) {
  HandleScope scope;

  REQ_BOOL_ARG(0, bold);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setBold(bold);
  return scope.Close(Undefined());
}




/**
 * Get script style of font
 *
 * @return {int}
 *    Script style
 */
Handle<Value> LibxlFont::Script(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Integer::New(obj->font->script()));
}




/**
 * Set script style of font
 *
 * @param {int} script
 *    Script style as int
 */
Handle<Value> LibxlFont::SetScript(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, script);
  SCRIPT_IS_VALID(script);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setScript((libxl::Script) script);
  return scope.Close(Undefined());
}




/**
 * Get underline style of font
 *
 * @return {int}
 *    Underline style
 */
Handle<Value> LibxlFont::Underline(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  return scope.Close(Integer::New(obj->font->underline()));
}




/**
 * Set underline style of font
 *
 * @param {int} ul
 *    Underline style as int
 */
Handle<Value> LibxlFont::SetUnderline(const Arguments& args) {
  HandleScope scope;

  REQ_INT_ARG(0, ul);
  UNDERLINE_IS_VALID(ul);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setUnderline((libxl::Underline) ul);
  return scope.Close(Undefined());
}




/**
 * Get name of font
 *
 * @return {String}
 */
Handle<Value> LibxlFont::Name(const Arguments& args) {
  HandleScope scope;

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  const CHAR* name = obj->font->name();

  return scope.Close(stov8s(name));
}




/**
 * Set name of font
 *
 * @param {String} newName
 *    New name of font
 */
Handle<Value> LibxlFont::SetName(const Arguments& args) {
  HandleScope scope;

  REQ_STR_ARG(0, newName);

  LibxlFont* obj = ObjectWrap::Unwrap<LibxlFont>(args.This());
  obj->font->setName(newName);

  return scope.Close(Undefined());
}




void LibxlFont::Initialize(Handle<Object> target) {
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->SetClassName(String::NewSymbol("Font"));
  t->InstanceTemplate()->SetInternalFieldCount(1);

  t->PrototypeTemplate()->Set(
    String::NewSymbol("size"),
    FunctionTemplate::New(Size)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setSize"),
    FunctionTemplate::New(SetSize)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("italic"),
    FunctionTemplate::New(Italic)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setItalic"),
    FunctionTemplate::New(SetItalic)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("strikeOut"),
    FunctionTemplate::New(StrikeOut)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setStrikeOut"),
    FunctionTemplate::New(SetStrikeOut)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("color"),
    FunctionTemplate::New(Color)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setColor"),
    FunctionTemplate::New(SetColor)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("bold"),
    FunctionTemplate::New(Bold)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setBold"),
    FunctionTemplate::New(SetBold)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("script"),
    FunctionTemplate::New(Script)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setScript"),
    FunctionTemplate::New(SetScript)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("underline"),
    FunctionTemplate::New(Underline)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setUnderline"),
    FunctionTemplate::New(SetUnderline)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("name"),
    FunctionTemplate::New(Name)->GetFunction()
  );

  t->PrototypeTemplate()->Set(
    String::NewSymbol("setName"),
    FunctionTemplate::New(SetName)->GetFunction()
  );

  constructor = Persistent<Function>::New(t->GetFunction());
  target->Set(String::NewSymbol("Font"), constructor);

  // colors
  NODE_DEFINE_CONSTANT(target, COLOR_BLACK);
  NODE_DEFINE_CONSTANT(target, COLOR_WHITE);
  NODE_DEFINE_CONSTANT(target, COLOR_RED);
  NODE_DEFINE_CONSTANT(target, COLOR_BRIGHTGREEN);
  NODE_DEFINE_CONSTANT(target, COLOR_BLUE);
  NODE_DEFINE_CONSTANT(target, COLOR_YELLOW);
  NODE_DEFINE_CONSTANT(target, COLOR_PINK);
  NODE_DEFINE_CONSTANT(target, COLOR_TURQUOISE);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKRED);
  NODE_DEFINE_CONSTANT(target, COLOR_GREEN);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKBLUE);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKYELLOW);
  NODE_DEFINE_CONSTANT(target, COLOR_VIOLET);
  NODE_DEFINE_CONSTANT(target, COLOR_TEAL);
  NODE_DEFINE_CONSTANT(target, COLOR_GRAY25);
  NODE_DEFINE_CONSTANT(target, COLOR_GRAY50);
  NODE_DEFINE_CONSTANT(target, COLOR_PERIWINKLE_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_PLUM_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_IVORY_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_LIGHTTURQUOISE_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKPURPLE_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_CORAL_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_OCEANBLUE_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_ICEBLUE_CF);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKBLUE_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_PINK_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_YELLOW_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_TURQUOISE_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_VIOLET_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKRED_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_TEAL_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_BLUE_CL);
  NODE_DEFINE_CONSTANT(target, COLOR_SKYBLUE);
  NODE_DEFINE_CONSTANT(target, COLOR_LIGHTTURQUOISE);
  NODE_DEFINE_CONSTANT(target, COLOR_LIGHTGREEN);
  NODE_DEFINE_CONSTANT(target, COLOR_LIGHTYELLOW);
  NODE_DEFINE_CONSTANT(target, COLOR_PALEBLUE);
  NODE_DEFINE_CONSTANT(target, COLOR_ROSE);
  NODE_DEFINE_CONSTANT(target, COLOR_LAVENDER);
  NODE_DEFINE_CONSTANT(target, COLOR_TAN);
  NODE_DEFINE_CONSTANT(target, COLOR_LIGHTBLUE);
  NODE_DEFINE_CONSTANT(target, COLOR_AQUA);
  NODE_DEFINE_CONSTANT(target, COLOR_LIME);
  NODE_DEFINE_CONSTANT(target, COLOR_GOLD);
  NODE_DEFINE_CONSTANT(target, COLOR_LIGHTORANGE);
  NODE_DEFINE_CONSTANT(target, COLOR_ORANGE);
  NODE_DEFINE_CONSTANT(target, COLOR_BLUEGRAY);
  NODE_DEFINE_CONSTANT(target, COLOR_GRAY40);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKTEAL);
  NODE_DEFINE_CONSTANT(target, COLOR_SEAGREEN);
  NODE_DEFINE_CONSTANT(target, COLOR_DARKGREEN);
  NODE_DEFINE_CONSTANT(target, COLOR_OLIVEGREEN);
  NODE_DEFINE_CONSTANT(target, COLOR_BROWN);
  NODE_DEFINE_CONSTANT(target, COLOR_PLUM);
  NODE_DEFINE_CONSTANT(target, COLOR_INDIGO);
  NODE_DEFINE_CONSTANT(target, COLOR_GRAY80);
  NODE_DEFINE_CONSTANT(target, COLOR_DEFAULT_FOREGROUND);
  NODE_DEFINE_CONSTANT(target, COLOR_DEFAULT_BACKGROUND);
  NODE_DEFINE_CONSTANT(target, COLOR_TOOLTIP);
  NODE_DEFINE_CONSTANT(target, COLOR_AUTO);

  // script
  NODE_DEFINE_CONSTANT(target, SCRIPT_NORMAL);
  NODE_DEFINE_CONSTANT(target, SCRIPT_SUPER);
  NODE_DEFINE_CONSTANT(target, SCRIPT_SUB);

  // underline
  NODE_DEFINE_CONSTANT(target, UNDERLINE_NONE);
  NODE_DEFINE_CONSTANT(target, UNDERLINE_SINGLE);
  NODE_DEFINE_CONSTANT(target, UNDERLINE_DOUBLE);
  NODE_DEFINE_CONSTANT(target, UNDERLINE_SINGLEACC);
  NODE_DEFINE_CONSTANT(target, UNDERLINE_DOUBLEACC);
}