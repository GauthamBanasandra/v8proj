//
//  bucket.hpp
//  v8proj
//
//  Created by Gautham Banasandra on 20/11/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#ifndef bucket_hpp
#define bucket_hpp

#include <v8.h>

void BucketGet(v8::Local<v8::Name> name,
               const v8::PropertyCallbackInfo<v8::Value> &info);
void BucketSet(v8::Local<v8::Name> name, v8::Local<v8::Value> value_obj,
               const v8::PropertyCallbackInfo<v8::Value> &info);
void BucketDelete(v8::Local<v8::Name> name,
                  const v8::PropertyCallbackInfo<v8::Boolean> &info);
v8::Local<v8::ObjectTemplate> MakeBucketMapTemplate(v8::Isolate *isolate);
v8::Local<v8::Object> WrapBucketMap(v8::Isolate *isolate);
void InstallMaps(v8::Isolate *isolate,
                 const std::vector<std::string> &bucket_names);
void Bucket();

#endif /* bucket_hpp */
