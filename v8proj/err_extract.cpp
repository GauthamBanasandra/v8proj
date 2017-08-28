//
//  err_extract.cpp
//  v8proj
//
//  Created by Gautham Banasandra on 24/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#include <string>
#include <iostream>

#include "err_extract.hpp"

void ExtractError(v8::Isolate *isolate) {
  std::string metadata_raw = R"({"requestID": "f8c21185-9a1a-4e75-b91d-0ed6ab2f5332","errors": [{"code": 12003,"msg": "Keyspace not found keyspace travel-sample - cause: No bucket named travel-sample"}],"status": "fatal","metrics": {"elapsedTime": "57.817618ms","executionTime": "57.784571ms","resultCount": 0,"resultSize": 0,"errorCount": 1}}
  )";
  ExtractErrorMsg(metadata_raw.c_str(), isolate);
}

void ExtractErrorMsg(const char *metadata, v8::Isolate *isolate) {
  v8::HandleScope handle_scope(isolate);

  auto metadata_v8str = v8::String::NewFromUtf8(isolate, metadata);
  auto metadata_obj = v8::JSON::Parse(metadata_v8str).As<v8::Object>();
  
  if (!metadata_obj.IsEmpty()) {
    auto errors_v8val = metadata_obj->Get(v8::String::NewFromUtf8(isolate, "errors"));
    auto errors_v8arr = errors_v8val.As<v8::Array>();
    for (uint32_t i = 0; i < errors_v8arr->Length(); ++i) {
      auto error = errors_v8arr->Get(i).As<v8::Object>();
      auto msg_v8str = error->Get(v8::String::NewFromUtf8(isolate, "msg"));
      v8::String::Utf8Value msg(msg_v8str);
      std::cout << "Error message:\t" << *msg << std::endl;
    }
  } else {
    std::cout << "Invalid JSON" << std::endl;
  }
}
