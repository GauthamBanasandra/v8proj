//
//  jsexception.hpp
//  v8proj
//
//  Created by Gautham Banasandra on 23/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#ifndef jsexception_hpp
#define jsexception_hpp

#include <string>
#include <include/v8.h>

class JsException {
private:
  std::string code_str;
  std::string desc_str;

  v8::Isolate *isolate;
  v8::Persistent<v8::String> code_name;
  v8::Persistent<v8::String> desc_name;
  v8::Persistent<v8::ObjectTemplate> exception;

public:
  JsException(std::string code_name, std::string desc_name,
              v8::Isolate *isolate);
  JsException(const JsException &);
  void Throw(int code_value, std::string desc_value);
  void ThrowNoLeak(int code_value, std::string desc_value);
  ~JsException();
};

#endif /* jsexception_hpp */
