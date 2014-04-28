var assert = require('assert');
var binding = require('./build/Release/mybinding');
assert.equal('world', binding.hello());
console.log('binding.hello() =', binding.hello());
