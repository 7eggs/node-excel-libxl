node-excel-libxl
================

[libxl](http://www.libxl.com/) bindings for Node.js. libxl is a library for working with Excel files.

Installation
============

```bash
npm install excel-libxl
```

Running
=======

For example you have simple `app.js`:

```javascript
var libxl = require('excel-libxl')
  , book = libxl.createBook();

book.load('./my-excel-file.xls', function(err) {
  book.getSheet(0).setName('Sheet #1 new name');
  book.save('./my-excel-file.xls', function(err) {
    process.exit(0);
  });
});
```

If `libxl.so` is not located in one of the default library paths (e.g. `/usr/lib`) you need to set `LD_LIBRARY_PATH` environment variable to start Node.js app correctly:

```bash
LD_LIBRARY_PATH="/path/to/libxl.so/" node app.js
```

API
===
You can open libxl [documentation](http://www.libxl.com/documentation.html) and use it now with following restrictions:
* Instead of `libxl` namespace you use `var libxl = require('excel-libxl')` as namespace, so `Book` class is available as `libxl.Book`, etc.
* All the enums are added to module, so you can find `COLOR_GRAY40` at `libxl.COLOR_GRAY40`

Thus I have in plans to add some kind of Helper/BaseApi class, I also will generate documentation someday.


TODO
====

* API covering:
  * [libxl::Book](http://www.libxl.com/workbook.html)
  * [libxl::Sheet](http://www.libxl.com/spreadsheet.html)
  * [libxl::Format](http://www.libxl.com/format.html)
  * ~~[libxl::Font](http://www.libxl.com/font.html)~~
* Windows support
* OS X support
* Tests. I suppose [vows](http://vowsjs.org) will be used
* Cleanup, refactor code

Disclaimer
==========

The sharks of C++ may find my code awful. My apologies, guys. I'm only learning C++. And thus addon is expected to be serious one I won't transfer ownership. But I promise to merge all the helpful pull requests and react on issues fast.
