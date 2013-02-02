try {
	module.exports = require('../build/Release/libxl_bindings');
} catch(e) {
	module.exports = require('../build/Debug/libxl_bindings');
}