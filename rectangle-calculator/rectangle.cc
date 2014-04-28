#include <node.h>
#include <v8.h>
#include <iostream>

using namespace std;
using namespace v8;

class Rectangle {
  int width, height;

  public:
    Rectangle (int,int);
    int area () {
      return (width * height);
    }
};

Rectangle::Rectangle (int a, int b) {
  width = a;
  height = b;
}

Handle<Value> Method(const Arguments& args) {
  // Call to rectangle logic
  int a = args[0]->IntegerValue();
  int b = args[1]->IntegerValue();
  Rectangle myRectangle (a, b);
  cout << "Rectangle area: " << myRectangle.area() << endl;

  // Return result
  HandleScope scope;
  return scope.Close(Integer::New(myRectangle.area()));
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "calculateArea", Method);
}

NODE_MODULE(myrectangle, init);
