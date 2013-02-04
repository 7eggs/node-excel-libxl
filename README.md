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

Nearest roadmap
===============

* Extend Sheet API to be able get data from cells or set it
* Mac OS X support

TODO
====

* Finish up covering of Book and Sheet API
* Add Format API
* Add Font API
* Tests. I suppose [vows](http://vowsjs.org) will be used
* Cleanup, refactor code

Disclaimer
==========

The sharks of C++ may find my code awful. My apologies, guys. I'm only learning C++. And thus addon is expected to be serious one I won't transfer ownership. But I promise to merge all the helpful pull requests.
