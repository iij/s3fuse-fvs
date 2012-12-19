/*
 * config.inc
 *
 * Copyright (c) 2011-2012, Tarick Bedeir or Hiroyuki Kakine.
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

// this file is used to generate config.h, config.cc, and s3fuse.conf
//
// format is:
// CONFIG(type, name, default-value); or CONFIG_REQUIRED(type, name, default-value);
//
// notes:
//   - a semicolon must follow CONFIG() or CONFIG_REQUIRED().
//   - a description can follow.  if it does, it must follow the semicolon and be preceded by " // ".
//   - build-config.sh does not preprocess this file, so there's not much room for variation in formatting

CONFIG(int, default_uid, UID_MAX); // UID for files in S3 that don't have a UID set (defaults to process effective UID)
CONFIG(int, default_gid, GID_MAX); // GID for files in S3 that don't have a GID set (defaults to process effective GID)
CONFIG(int, default_mode, 0755); // mode for files in S3 that don't have a mode set

CONFIG(int, cache_expiry_in_s, 3 * 60); // time in seconds before objects in stats cache expire
CONFIG(bool, cache_directories, false); // cache directory listings ("true"/"yes" or "false"/"no")
CONFIG(bool, precache_on_readdir, true); // pre-cache metadata for the contents of a directory when readdir() is called ("true"/"yes" or "false"/"no")

CONFIG(std::string, default_content_type, "binary/octet-stream"); // MIME type for newly-created objects
CONFIG(bool, auto_content_type, false); // auto select content type from /etc/mime.types
CONFIG(size_t, download_chunk_size, 128 * 1024); // download chunk size, in bytes
CONFIG(size_t, upload_chunk_size, 5 * 1024 * 1024); // upload chunk size, in bytes (5 MB is the S3 minimum)
CONFIG(int, max_transfer_retries, 5); // maximum number of times a chunk transfer will be retried before failing
CONFIG(int, transfer_timeout_in_s, 5 * 60); // transfer timeout in seconds, should be long enough to transfer download_chunk_size/upload_chunk_size

CONFIG(bool, verbose_requests, false); // set CURLOPT_VERBOSE (enable verbosity in libcurl)
CONFIG(int, request_timeout_in_s, 30); // request timeout in seconds (for all HTTP requests besides transfers)

CONFIG(std::string, aws_service_endpoint, ""); // service endpoint for Amazon AWS (change to "s3-eu-west-1.amazonaws.com" for EU buckets)
CONFIG(std::string, aws_service_endpoint_scheme, "https://"); // service endpoint scheme for Amazon AWS (change to "http://")

CONFIG(std::string, xattr_prefix, ""); // if set, prefixes all extended attributes (may have to be set to "user." for compatibility with getfattr)

CONFIG(bool, use_expect_header, true); // include "Expect: 100 continue" header in POST and PUT method. if exist this header, proxy may return status code 417.

CONFIG_REQUIRED(std::string, service, ""); // service -- must be "aws" or "google-storage" or "fvs"
CONFIG_REQUIRED(std::string, auth_data, ""); // service-specific authentication details (see documentation)
CONFIG_REQUIRED(std::string, bucket_name, ""); // bucket name

