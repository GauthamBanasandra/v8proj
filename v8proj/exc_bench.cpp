//
//  exc_bench.cpp
//  v8proj
//
//  Created by Gautham Banasandra on 24/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#include <iostream>

#include "exc_bench.hpp"

#define SIZE 1000000
#define ITERS 100

void RunJSON(v8::Isolate *isolate) {
  for (unsigned long long i = 0; i < SIZE; ++i) {
    std::string exception_str = "{\"code\":" + std::to_string(i) +
    ", \"desc\":\"exception message" +
    std::to_string(i) + "\"}";
    auto exception_v8str =
    v8::String::NewFromUtf8(isolate, exception_str.c_str());
    v8::JSON::Parse(exception_v8str);
  }
}

void RunObj(JsException exception) {
  for (unsigned long long i = 0; i < SIZE; ++i) {
    std::string desc = "exception message" + std::to_string(i);
    exception.ThrowNoLeak(static_cast<int>(i), desc);
  }
}

void ExceptionBenchmark(v8::Isolate *isolate) {
  Timer t1;
  RunJSON(isolate);
  std::cout << "JSON:\t" << t1.elapsed() << std::endl;
  
  JsException exception("code", "desc", isolate);
  Timer t2;
  RunObj(exception);
  std::cout << "Object:\t" << t2.elapsed() << std::endl;
}
