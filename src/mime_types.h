/*
 * mime_types.h
 * -------------------------------------------------------------------------
 * Provides mime type.
 * -------------------------------------------------------------------------
 *
 * Copyright (c) 2012, Hiroyuki Kakine.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef S3_MIME_TYPES_H
#define S3_MIME_TYPES_H

#ifndef MIME_TYPES_FILE
#define MIME_TYPES_FILE "/etc/mime.types"
#endif

#include <string> 
#include <boost/unordered_map.hpp> 

namespace s3
{
  class mime_types
  {
  public:
    static int init(void);
    static boost::unordered_map<const std::string, const std::string> create_map() {
      boost::unordered_map<const std::string, const std::string> m;
      return m;
    }
    static const std::string &get_mime_type(const std::string ext);
  private:
    static boost::unordered_map<const std::string, const std::string> ext_mime;
  };
}

#endif
