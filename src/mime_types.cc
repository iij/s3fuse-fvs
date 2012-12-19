/*
 * mime_types.cc
 * -------------------------------------------------------------------------
 * Detect mime type.
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

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp> 

#include "config.h"
#include "mime_types.h"

using namespace boost;
using namespace std;

using namespace s3;

boost::unordered_map<const std::string, const std::string> mime_types::ext_mime = mime_types::create_map();

int mime_types::init(void)
{
  ifstream ifs(MIME_TYPES_FILE);
  int line_number = 0;

  if (ifs.fail()) {
    return 0;
  }

  while (ifs.good()) {
    string line, key, value;
    vector<string> exts;
    size_t pos;

    getline(ifs, line);
    line_number++;
    pos = line.find('#');

    if (pos != string::npos)
      line = line.substr(0, pos);

    if (line.empty())
      continue;

    pos = line.find_first_of('\t');
    if (pos == string::npos)
      pos = line.find_first_of(' ');
      if (pos == string::npos)
        continue;

    key = line.substr(0, pos);
    value = line.substr(pos + 1);

    algorithm::trim(key);
    algorithm::trim(value);

    if (key.empty() || value.empty())
      continue;

    algorithm::split(exts, value, boost::is_any_of(" "));

    for (int i =  0; i < (int)exts.size(); i++) {
      const string ext = string("." + exts[i]);
      const string mime = string(key);
      ext_mime.insert(make_pair(ext, mime));
    }
  }

  return 0;
}

const string &mime_types::get_mime_type(const string ext)
{
  unordered_map<const string, const string>::iterator iter;
 
  iter = ext_mime.find(ext);
  if (iter != ext_mime.end())
    return iter->second;
  else
    return config::get_default_content_type();
}
