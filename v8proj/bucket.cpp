//
//  bucket.cpp
//  v8proj
//
//  Created by Gautham Banasandra on 20/11/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#include "bucket.hpp"
#include <iostream>
#include <string>
#include <vector>

void Bucket() {
  std::vector<std::string> bucket_names{"src", "dst"};
  auto isolate = v8::Isolate::GetCurrent();
  InstallMaps(isolate, bucket_names);
}

void InstallMaps(v8::Isolate *isolate,
                 const std::vector<std::string> &bucket_names) {
  v8::HandleScope handle_scope(isolate);
  auto context = isolate->GetCurrentContext();

  for (const auto &name : bucket_names) {
    auto bucket_name = v8::String::NewFromUtf8(isolate, name.c_str());
    auto bucket_obj = WrapBucketMap(isolate);
    context->Global()->Set(bucket_name, bucket_obj);
  }
}

v8::Local<v8::Object> WrapBucketMap(v8::Isolate *isolate) {
  v8::EscapableHandleScope handle_scope(isolate);
  v8::Global<v8::ObjectTemplate> bucket_map_template;

  if (bucket_map_template.IsEmpty()) {
    auto raw_template = MakeBucketMapTemplate(isolate);
    bucket_map_template.Reset(isolate, raw_template);
  }

  auto templ = v8::Local<v8::ObjectTemplate>::New(isolate, bucket_map_template);
  auto obj = templ->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();

  return handle_scope.Escape(obj);
}

v8::Local<v8::ObjectTemplate> MakeBucketMapTemplate(v8::Isolate *isolate) {
  v8::EscapableHandleScope handle_scope(isolate);

  auto obj_templ = v8::ObjectTemplate::New(isolate);
  obj_templ->SetHandler(v8::NamedPropertyHandlerConfiguration(
      BucketGet, BucketSet, nullptr, BucketDelete));
  obj_templ->SetIndexedPropertyHandler(
      v8::IndexedPropertyGetterCallback(BucketGet),
      v8::IndexedPropertySetterCallback(BucketSet), nullptr,
      v8::IndexedPropertyDeleterCallback(BucketDelete));
  return handle_scope.Escape(obj_templ);
}

void BucketGet(v8::Local<v8::Name> name,
               const v8::PropertyCallbackInfo<v8::Value> &info) {
  std::cout << "Called bucket get" << std::endl;
}

void BucketSet(v8::Local<v8::Name> name, v8::Local<v8::Value> value_obj,
               const v8::PropertyCallbackInfo<v8::Value> &info) {
  std::cout << "Called bucket set" << std::endl;
}

void BucketDelete(v8::Local<v8::Name> name,
                  const v8::PropertyCallbackInfo<v8::Boolean> &info) {
  std::cout << "Called bucket delete" << std::endl;
}
