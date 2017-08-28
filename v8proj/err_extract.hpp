//
//  err_extract.hpp
//  v8proj
//
//  Created by Gautham Banasandra on 24/08/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#ifndef err_extract_hpp
#define err_extract_hpp

#include <include/v8.h>

void ExtractError(v8::Isolate *isolate);
void ExtractErrorMsg(const char *metadata, v8::Isolate *isolate);

#endif /* err_extract_hpp */
