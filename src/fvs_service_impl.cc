/*
 * fvs_service_impl.cc
 * -------------------------------------------------------------------------
 * Definitions for FVS service implementation.
 * -------------------------------------------------------------------------
 *
 * Copyright (c) 2012, Hiroyuki Kakine
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

#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "fvs_service_impl.h"
#include "config.h"
#include "logger.h"
#include "request.h"
#include "util.h"

using namespace boost;
using namespace std;

using namespace s3;

namespace
{
  const string FVS_HEADER_PREFIX = "x-iijgio-";
  const string FVS_XML_NAMESPACE;
  const string DEFAULT_ENDPOINT = "gss.iijgio.com";

  const string EMPTY = "";

  const string & safe_find(const header_map &map, const char *key)
  {
    header_map::const_iterator itor = map.find(key);

    return (itor == map.end()) ? EMPTY : itor->second;
  }
}

fvs_service_impl::fvs_service_impl()
{
  ifstream f;
  string line;
  vector<string> fields;

  open_private_file(config::get_auth_data(), &f);
  getline(f, line);

  split(fields, line, is_any_of(string(" \t")), token_compress_on);

  if (fields.size() != 2) {
    S3_LOG(
      LOG_ERR, 
      "fvs_service_impl::fvs_service_impl", 
      "expected 2 fields for auth_data, found %i.\n",
      fields.size());

    throw runtime_error("error while parsing auth data for FVS.");
  }

  _key = fields[0];
  _secret = fields[1];

  if (config::get_aws_service_endpoint() == "") {
    _endpoint = config::get_aws_service_endpoint_scheme()  + DEFAULT_ENDPOINT;
  } else {
    _endpoint = config::get_aws_service_endpoint_scheme()  + config::get_aws_service_endpoint();
  }
}

const string & fvs_service_impl::get_header_prefix()
{
  return FVS_HEADER_PREFIX;
}

const string & fvs_service_impl::get_url_prefix()
{
  return _endpoint;
}

const string & fvs_service_impl::get_xml_namespace()
{
  return FVS_XML_NAMESPACE;
}

bool fvs_service_impl::is_multipart_download_supported()
{
  return false;
}

bool fvs_service_impl::is_multipart_upload_supported()
{
  return false;
}

bool fvs_service_impl::is_next_marker_supported()
{
  return false;
}

void fvs_service_impl::sign(request *req, bool last_sign_failed)
{
  const header_map &headers = req->get_headers();
  string to_sign = 
    req->get_method() + "\n" + 
    safe_find(headers, "Content-MD5") + "\n" + 
    safe_find(headers, "Content-Type") + "\n" + 
    safe_find(headers, "Date") + "\n";

  for (header_map::const_iterator itor = headers.begin(); itor != headers.end(); ++itor)
    if (!itor->second.empty() && itor->first.substr(0, FVS_HEADER_PREFIX.size()) == FVS_HEADER_PREFIX)
      to_sign += itor->first + ":" + itor->second + "\n";

  to_sign += req->get_url();
  req->set_header("Authorization", string("IIJGIO ") + _key + ":" + util::sign(_secret, to_sign));

  if (last_sign_failed)
    S3_LOG(LOG_DEBUG, "fvs_service_impl::sign", "last sign failed. string to sign: [%s].\n", to_sign.c_str());
}
