node-gyp-examples
=================

Some examples of C++ modules called by node.js.

Some of the examples have been taken from Joyent node.js git repository, from [test/addons](https://github.com/joyent/node/tree/v0.10.26/test/addons) folder.

To compile a module, two commands must be run:

```
node-gyp configure
node-gyp build
```

`package.json` file is not necessary for compiling and running the examples, but previous commands are called implicitly by default when calling `npm install` (can however be explicitly specified in `script` section), so a `package.json` file could be helpful.
