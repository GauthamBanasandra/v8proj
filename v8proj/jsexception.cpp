//
//  jsexpection.cpp
//  v8proj
//
//  Created by Gautham Banasandra on 23/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#include "jsexception.hpp"

JsException::JsException(std::string code_name, std::string desc_name,
                         v8::Isolate *isolate)
    : isolate(isolate), code_str(code_name), desc_str(desc_name) {
  this->code_name.Reset(isolate,
                        v8::String::NewFromUtf8(isolate, code_name.c_str()));
  this->desc_name.Reset(isolate,
                        v8::String::NewFromUtf8(isolate, desc_name.c_str()));
  this->exception.Reset(isolate, v8::ObjectTemplate::New());
}

JsException::JsException(const JsException &exc_obj) {
  isolate = exc_obj.isolate;
  code_str = exc_obj.code_str;
  desc_str = exc_obj.desc_str;

  code_name.Reset(isolate, v8::String::NewFromUtf8(isolate, code_str.c_str()));
  desc_name.Reset(isolate, v8::String::NewFromUtf8(isolate, desc_str.c_str()));
  exception.Reset(isolate, v8::ObjectTemplate::New());
}

void JsException::Throw(int code, std::string desc) {
  v8::HandleScope handle_scope(isolate);

  auto code_value = v8::Number::New(isolate, code);
  auto desc_value = v8::String::NewFromUtf8(isolate, desc.c_str());

  auto exception = this->exception.Get(isolate);
  auto code_name = this->code_name.Get(isolate);
  auto desc_name = this->desc_name.Get(isolate);

  exception->Set(code_name, code_value);
  exception->Set(desc_name, desc_value);
  exception->NewInstance();
}

void JsException::ThrowNoLeak(int code, std::string desc) {
  v8::HandleScope handle_scope(isolate);
  
  auto code_value = v8::Number::New(isolate, code);
  auto desc_value = v8::String::NewFromUtf8(isolate, desc.c_str());
  
  auto code_name = this->code_name.Get(isolate);
  auto desc_name = this->desc_name.Get(isolate);
  
  auto exception = v8::Object::New(isolate);
  exception->Set(code_name, code_value);
  exception->Set(desc_name, desc_value);
}

JsException::~JsException() {
  this->code_name.Reset();
  this->desc_name.Reset();
  this->exception.Reset();
}
