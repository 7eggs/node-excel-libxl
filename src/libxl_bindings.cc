/*
 * Copyright by Alexander Makarenko
 *
 * See license text in LICENSE file
 */

#include <node.h>
#include "libxl_book.h"
#include "libxl_sheet.h"
#include "libxl_format.h"
#include "libxl_font.h"

using namespace v8;

void InitExcelLibxl(Handle<Object> target) {
  LibxlBook::Initialize(target);
  LibxlSheet::Initialize(target);
  LibxlFormat::Initialize(target);
  LibxlFont::Initialize(target);
}

NODE_MODULE(libxl_bindings, InitExcelLibxl)
