var binding;
try {
	binding = require(__dirname + '/../build/Debug/libxl_bindings');
} catch(e) {
	binding = require(__dirname + '/../build/Release/libxl_bindings');
}
module.exports = binding;
