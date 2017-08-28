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
  const char *metadata =
      "{"
      "requestID\": \"2812a4de-0dff-46f8-8b1d-13bf1494ba9d\","
      "errors\": [{\"code\":12003,\"msg\":\"Keyspace not found keyspace "
      "travel-sample - cause: No bucket named travel-sample\"}],"
      "status\": \"fatal\","
      "metrics\": {\"elapsedTime\": \"53.044954ms\",\"executionTime\": "
      "\"53.011543ms\",\"resultCount\": 0,\"resultSize\": 0,\"errorCount\": 1}"
      "}";
  ExtractErrorMsg(metadata, isolate);
}

void ExtractErrorMsg(const char *metadata, v8::Isolate *isolate) {
  v8::HandleScope handle_scope(isolate);

  auto metadata_v8str = v8::String::NewFromUtf8(isolate, metadata);
  auto metadata_obj = v8::JSON::Parse(metadata_v8str).As<v8::Object>();
  auto errors_v8arr =
      metadata_obj->Get(v8::String::NewFromUtf8(isolate, "errors"))
          .As<v8::Array>();
  
  std::cout << "errors length:\t" << errors_v8arr->Length() << std::endl;
}
