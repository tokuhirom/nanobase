#include "../nanobase.h"
#include <nanotap/nanotap.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
  char buf[5];
  nb_base64_encode((unsigned char*)"foo", strlen("foo"), (unsigned char*)buf);
  ok(strcmp(buf, "Zm9v") == 0, "base64");
  done_testing();
  return 0;
}

