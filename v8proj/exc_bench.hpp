//
//  exc_bench.hpp
//  v8proj
//
//  Created by Gautham Banasandra on 24/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#ifndef exc_bench_hpp
#define exc_bench_hpp

#include <chrono>
#include "jsexception.hpp"

class Timer {
public:
  Timer() : beg_(clock_::now()) {}
  void reset() { beg_ = clock_::now(); }
  double elapsed() const {
    return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
  }
  
private:
  typedef std::chrono::high_resolution_clock clock_;
  typedef std::chrono::duration<double, std::ratio<1>> second_;
  std::chrono::time_point<clock_> beg_;
};

void RunJSON(v8::Isolate *isolate);
void RunObj(JsException exception);
void ExceptionBenchmark(v8::Isolate *isolate);

#endif /* exc_bench_hpp */
