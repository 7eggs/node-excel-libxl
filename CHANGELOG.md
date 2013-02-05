# Changelog

Revision history for node-excel-libxl

## Version 0.0.5
* Fully covered libxl::Font API
* Added enums: script styles (`SCRIPT_*`), underline styles (`UNDERLINE_*`), colors (`COLOR_*`)
* Added this changelog

## Version 0.0.4
* Added classes: `Format` (libxl::Format), `Font` (libxl::Font)
* Extended `Book` API:
  * `sheetCount()` gives number of sheets in the workbook
  * `addFormat(initFormat)` adds new format
  * `format(idx)` returns format defined under given index
  * `formatSize()` returns number of formats defined in the book
  * Similar with fonts: `addFont(initFont` / `font(idx)` / `fontSize()`
* Removed 'Sync' suffix for methods which have only synchronous version
* Fixed bug with `Sheet::cellType()` - was throwing error if cell has error type

## Version 0.0.3
* Extended `Sheet` API:
  * `cellType(row, col)`
  * `readString(row, col)`
  * `writeString(row, col, string)`
* Added cell type enums (`CELLTYPE_*`)

## Version 0.0.2
* Added `Sheet` class (libxl::Sheet):
  * `getName()`
  * `setName(name)`
* Extended `Book` API:
  * `load(path, cb)` / `loadSync(path)`
  * `save(path, cb)` / `saveSync(path)`
  * `setKey(customerName, customerKey)` sets license key
  * `release()` - release all the book memory, does `libxl::Book::release()`
  * `addSheetSync(name, initSheet)`
  * `insertSheetSync(idx, name, initSheet)`
  * `getSheet(idx)`
  * `deleteSheet(idx)`

## Version 0.0.1
* Added `Book` class (libxl::Book)
* Added Book factories:
  * `createBook()` is equivalent to `xlCreateBook()`
  * `createXMLBook()` is equivalent to `xlCreateXMLBook()`
* Also `Book` can be instantiated via constructor: `new Book(type)` where `type` is one of the constants: 
`BOOK_TYPE_XLS`, `BOOK_TYPE_XLSX`
