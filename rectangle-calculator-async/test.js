var assert = require('assert');
var myRectangleAsync = require('./build/Release/myrectangle');

myRectangleAsync.calculateArea(3, 4, function(err, area) {
    assert.equal(null, err);
    console.log('async myRectangle.calculateArea(3, 4) =', area);
});
