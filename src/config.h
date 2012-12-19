/*
 * config.h
 * -------------------------------------------------------------------------
 * Methods to get cached configuration values.  Mostly auto-generated with
 * configuration keys in config.inc.
 * -------------------------------------------------------------------------
 *
 * Copyright (c) 2011, Tarick Bedeir.
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

#ifndef S3_CONFIG_H
#define S3_CONFIG_H

#include <unistd.h>

#include <string>
#include <limits>

namespace s3
{
  #if !defined(UID_MAX)
    const uid_t UID_MAX = std::numeric_limits<uid_t>::max();
  #endif

  #if !defined(GID_MAX)
    const gid_t GID_MAX = std::numeric_limits<gid_t>::max();
  #endif

  class config
  {
  public:
    static int init(const std::string &file = "");

    #define CONFIG(type, name, def) \
      private: \
        static type s_ ## name; \
      \
      public: \
        static inline const type & get_ ## name () { return s_ ## name; }

    #define CONFIG_REQUIRED(type, name, def) CONFIG(type, name, def)

    #include "config.inc"

    #undef CONFIG
    #undef CONFIG_REQUIRED
  };
}

#endif
