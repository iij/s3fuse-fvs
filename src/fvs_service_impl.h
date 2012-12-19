/*
 * fvs_service_impl.h
 * -------------------------------------------------------------------------
 * Service implementation for IIJGIO FV/S Services.
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

#ifndef IIJGIO_FVS_SERVICE_IMPL_H
#define IIJGIO_FVS_SERVICE_IMPL_H

#include "service_impl.h"

namespace s3
{
  class request;

  class fvs_service_impl : public service_impl
  {
  public:
    fvs_service_impl();

    virtual const std::string & get_header_prefix();
    virtual const std::string & get_url_prefix();
    virtual const std::string & get_xml_namespace();

    virtual bool is_multipart_download_supported();
    virtual bool is_multipart_upload_supported();
    virtual bool is_next_marker_supported();

    virtual void sign(request *req, bool last_sign_failed);

  private:
    std::string _key, _secret, _endpoint;
  };
}

#endif
