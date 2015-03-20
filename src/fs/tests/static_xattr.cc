#include <iostream>

#include "fs/static_xattr.h"

using std::cout;
using std::endl;
using std::string;

using s3::fs::static_xattr;
using s3::fs::xattr;

void test(const xattr::ptr &p)
{
  string hk, hv;

  p->to_header(&hk, &hv);

  cout << 
    p->get_key() << ": " << 
    (p->is_writable() ? "(writable) " : "") << 
    (p->is_serializable() ? "(serializable) " : "") << 
    (p->is_visible() ? "(visible) " : "") <<
    (p->is_removable() ? "(removable) " : "") <<
    hk << ": " <<
    hv << endl;
}

int main(int argc, char **argv)
{
  const int LEN = 1024;
  char buf[LEN], buf_out[LEN];
  string hk, hv;
  xattr::ptr p;

  srand(time(NULL));

  for (int i = 0; i < LEN; i++)
    buf[i] = rand();

  test(static_xattr::from_string("x1", "abcdef", xattr::XM_VISIBLE));
  test(static_xattr::create("x2", xattr::XM_VISIBLE));
  test(static_xattr::create("x3", xattr::XM_WRITABLE));
  test(static_xattr::from_string("x4", "blah", xattr::XM_WRITABLE | xattr::XM_SERIALIZABLE));
  test(static_xattr::from_string("AN_UPPERCASE_KEY", "value", xattr::XM_SERIALIZABLE));

  p = static_xattr::create("should_be_AN_INVALID_KEY", xattr::XM_WRITABLE | xattr::XM_SERIALIZABLE);

  p->set_value(buf, LEN);
  test(p);

  p->to_header(&hk, &hv);

  p = static_xattr::from_header(hk, hv, xattr::XM_VISIBLE);
  test(p);

  cout << "get_value: " << p->get_value(buf_out, LEN) << endl;

  for (int i = 0; i < LEN; i++) {
    if (buf[i] != buf_out[i]) {
      cout << "values do not match at position " << i << endl;
      break;
    }
  }

  cout << "values match" << endl;

  return 0;
}
