var fs = require('fs'),
    http = require('http'),
    os = require('os'),
    path = require('path'),
    spawn = require('child_process').spawn;

var isWin = !!os.platform().match(/^win/),
    isX64 = !!os.arch().match(/64$/),
    dependencyDir = 'deps',
    libxlDir = path.join(dependencyDir, 'libxl'),
    archiveUrl = 'http://www.libxl.com/download/libxl' + (isWin ? '.zip' : '.tar.gz'),
    archiveFile = path.join(dependencyDir, path.basename(archiveUrl));

var download = function(url, file, callback) {
  var writer = fs.createWriteStream(file);
  http.get(url, function(response) {
    response.pipe(writer);
    response.on('end', function() {
      callback();
    });
  });
};
var execute = function(cmd, args, callback) {
  spawn(cmd, args).on('close', function(code) {
    if (0 === code) {
      callback();
    } else {
      process.exit(1);
    }
  });
};
var extractor = function(file, target, callback) {
  if (isWin) {
    execute(path.join('tools', '7zip', '7za.exe'), ['x', archiveFile, '-o' + dependencyDir], callback);
  } else {
    execute('tar', ['-C', dependencyDir, '-zxf', archiveFile], callback);
  }
};
var finder = function(dir, pattern) {
  var files = fs.readdirSync(dir),
      i,
      file;
  for (i = 0; i < files.length; i++) {
    file = files[i];
    if (file.match(pattern)) {
      return path.join(dir, file);
    }
  }
  return null;
};
var register = function() {
  var sharedObject = path.join(
        libxlDir,
        (isWin ? 'bin' : 'lib') + ((!isWin && isX64) ? '64' : ''),
        'libxl' + (isWin ? '.dll' : '.so')
      );

  if (!isWin) {
    execute('sudo cp', [sharedObject, '/usr/lib']);
  }
};

if (fs.existsSync(libxlDir)) {
  process.exit(0);
}

if (!fs.existsSync(dependencyDir)) {
  fs.mkdirSync(dependencyDir);
}

download(archiveUrl, archiveFile, function() {
  extractor(archiveFile, dependencyDir, function() {
    fs.unlinkSync(archiveFile);
    fs.renameSync(finder(dependencyDir, /^libxl/), libxlDir);
    register();
  });
});
