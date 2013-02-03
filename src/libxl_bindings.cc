/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include <node.h>
#include "libxl_book.h"

using namespace v8;

void InitExcelLibxl(Handle<Object> target) {
  LibxlBook::Initialize(target);
}

NODE_MODULE(libxl_bindings, InitExcelLibxl)
