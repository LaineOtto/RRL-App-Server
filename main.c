#include <stdio.h>
#include <stdlib.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/uri.h>
#include <curl/curl.h>
#include "functions.h"

int main(int argc, char const *argv[]) {
  const char* handler = getenv("_HANDLER");
  const char* taskRoot = getenv("LAMBDA_TASK_ROOT");
  const char* runtimeAPI = getenv("AWS_LAMBDA_RUNTIME_API");

  while (true) {
    eventData =
  }

  return 0;
}
