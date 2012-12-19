/*
 * xml.cc
 * -------------------------------------------------------------------------
 * Implements s3::xml using libxml++.
 * -------------------------------------------------------------------------
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
#include <cstring>

#include <errno.h>
#include <libxml/tree.h>

#include <stdexcept>
#include <libxml++/libxml++.h>
#include <boost/algorithm/string/replace.hpp>

#include "logger.h"
#include "xml.h"

using namespace boost;
using namespace std;
using namespace xmlpp;

using namespace s3;

namespace
{
  Node::PrefixNsMap s_ns_map;
  bool valid_ns;
}

void xml::init(const string &ns)
{
  xmlInitParser();
  LIBXML_TEST_VERSION;

  if (!ns.empty()) {
    valid_ns = true;
    s_ns_map["s3"] = ns;
  } else {
    valid_ns = false;
  }
}

char *xml::fixup_xpath(char *new_xpath, size_t max_xpath_len, const char *xpath)
{
  if (valid_ns) {
    string s = string(xpath);
    algorithm::replace_all(s, "/", "/s3:");
    if (s.length() >= max_xpath_len)
      throw runtime_error("can not fixup xpath.");
    std::strncpy(new_xpath, s.c_str(), max_xpath_len - 1);
  } else {
    if (std::strlen(xpath) >= max_xpath_len)
      throw runtime_error("can not fixup xpath.");
    std::strncpy(new_xpath, xpath, max_xpath_len - 1);
  }
  new_xpath[max_xpath_len] = '\0';
  return new_xpath; 
}

xml::document xml::parse(const string &data)
{
  try {
    document doc(new DomParser());

    doc->parse_memory(data);

    if (!doc)
      throw runtime_error("error while parsing xml.");

    if (!doc->get_document())
      throw runtime_error("parser does not contain a document.");

    if (!doc->get_document()->get_root_node())
      throw runtime_error("document does not contain a root node.");

    return doc;

  } catch (const std::exception &e) {
    S3_LOG(LOG_WARNING, "xml::parse", "caught exception: %s\n", e.what());

  } catch (...) {
    S3_LOG(LOG_WARNING, "xml::parse", "caught unknown exception.");
  }

  return document();
}

int xml::find(const xml::document &doc, const char *xpath, string *element)
{
  try {
    NodeSet nodes;
    TextNode *text;
    char new_xpath[MAX_XPATH_LEN];

    if (!doc)
      throw runtime_error("got null document pointer.");

    if (valid_ns) {
      nodes = doc->get_document()->get_root_node()->find(xml::fixup_xpath(new_xpath, sizeof(new_xpath), xpath), s_ns_map);
    } else {
      nodes = doc->get_document()->get_root_node()->find(xpath);
    }

    if (nodes.empty())
      throw runtime_error("no matching nodes.");

    text = dynamic_cast<Element *>(nodes[0])->get_child_text();

    if (!text)
      throw runtime_error("node does not contain a text child.");

    *element = text->get_content();
    return 0;

  } catch (const std::exception &e) {
    S3_LOG(LOG_WARNING, "xml::find", "caught exception while finding [%s](%d): %s\n", xpath, valid_ns, e.what());

  } catch (...) {
    S3_LOG(LOG_WARNING, "xml::find", "caught unknown exception while finding [%s](%d).\n", xpath, valid_ns);
  }

  return -EIO;
}

int xml::find(const xml::document &doc, const char *xpath, xml::element_list *list)
{
  try {
    NodeSet nodes;
    char new_xpath[MAX_XPATH_LEN];

    if (!doc)
      throw runtime_error("got null document pointer.");

    if (valid_ns) {
      nodes = doc->get_document()->get_root_node()->find(xml::fixup_xpath(new_xpath, sizeof(new_xpath), xpath), s_ns_map);
    } else {
      nodes = doc->get_document()->get_root_node()->find(xpath, s_ns_map);
    }

    for (NodeSet::const_iterator itor = nodes.begin(); itor != nodes.end(); ++itor) {
      TextNode *text = dynamic_cast<Element *>(*itor)->get_child_text();

      if (text)
        list->push_back(text->get_content());
    }

    return 0;

  } catch (const std::exception &e) {
    S3_LOG(LOG_WARNING, "xml::find", "caught exception while finding [%s](%d): %s\n", xpath, valid_ns, e.what());

  } catch (...) {
    S3_LOG(LOG_WARNING, "xml::find", "caught unknown exception while finding [%s](%d).\n", xpath, valid_ns);
  }

  return -EIO;
}
