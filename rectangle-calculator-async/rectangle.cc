#include <node.h>
#include <v8.h>
#include <uv.h>
#include <iostream>
#include <unistd.h>

using namespace node;
using namespace v8;
using namespace std;

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

struct async_req {
  uv_work_t req;
  int inputA;
  int inputB;
  int output;
  Persistent<Function> callback;
};

void CalculateAreaAsync (uv_work_t *r) {
  async_req *req = reinterpret_cast<async_req *>(r->data);
  sleep(1); // simulate CPU intensive process...

  int area = Rectangle(req->inputA, req->inputB).area();
  cout << "Rectangle area: " << area << endl;

  req->output = area;
}

void AfterAsync (uv_work_t *r) {

  HandleScope scope;
  async_req *req = reinterpret_cast<async_req *>(r->data);

  Handle<Value> argv[2] = { Null(), Integer::New(req->output) };

  TryCatch try_catch;

  req->callback->Call(Context::GetCurrent()->Global(), 2, argv);

  // cleanup
  req->callback.Dispose();
  delete req;

  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
}

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;

  async_req *req = new async_req;
  req->req.data = req;

  req->inputA = args[0]->IntegerValue();
  req->inputB = args[1]->IntegerValue();
  req->output = 0;

  Local<Function> callback = Local<Function>::Cast(args[2]);
  req->callback = Persistent<Function>::New(callback);

  uv_queue_work(uv_default_loop(),
                &req->req,
                CalculateAreaAsync,
                (uv_after_work_cb)AfterAsync);

  return scope.Close(Undefined());
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "calculateArea", Method);
}

NODE_MODULE(myrectangle, init);
