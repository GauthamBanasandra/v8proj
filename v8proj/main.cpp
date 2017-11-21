//
//  main.cpp
//  v8proj
//
//  Created by Gautham Banasandra on 23/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"

#include "bucket.hpp"
#include "err_extract.hpp"
#include "exc_bench.hpp"

#define PROJECT_ROOT "/Users/gautham/projects/xcode/v8proj/v8proj/"
#define SOURCE_PATH PROJECT_ROOT "input1.js"

using namespace v8;

inline std::string ReadFile(std::string path) {
  std::string line, content;
  std::ifstream file(path);
  if (file.is_open()) {
    while (getline(file, line)) {
      content += line + "\n";
    }

    file.close();
  } else {
    std::cout << "Unable to open file:\t" << path << std::endl;
  }

  return content;
}

int main(int argc, char *argv[]) {
  // Initialize V8.
  V8::InitializeICUDefaultLocation(argv[0]);
  V8::InitializeExternalStartupData(argv[0]);
  Platform *platform = platform::CreateDefaultPlatform();
  V8::InitializePlatform(platform);
  V8::Initialize();

  // Create a new Isolate and make it the current one.
  Isolate::CreateParams create_params;
  create_params.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  Isolate *isolate = Isolate::New(create_params);
  {
    Isolate::Scope isolate_scope(isolate);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Create a new context.
    Local<Context> context = Context::New(isolate);

    // Enter the context for compiling and running the hello world script.
    Context::Scope context_scope(context);

    Bucket();
    std::cout << ReadFile(SOURCE_PATH) << std::endl;

    // Create a string containing the JavaScript source code.
    Local<String> source =
        String::NewFromUtf8(isolate, ReadFile(SOURCE_PATH).c_str(),
                            NewStringType::kNormal)
            .ToLocalChecked();

    // Compile the source code.
    Local<Script> script = Script::Compile(context, source).ToLocalChecked();

    // Run the script to get the result.
    Local<Value> result = script->Run(context).ToLocalChecked();

    // Convert the result to an UTF8 string and print it.
    String::Utf8Value utf8(result);
    printf("%s\n", *utf8);
  }

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  V8::Dispose();
  V8::ShutdownPlatform();
  delete platform;
  delete create_params.array_buffer_allocator;
  return 0;
}
