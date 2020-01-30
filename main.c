#include <stdio.h>
#include <stdlib.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/uri.h>
#include <curl/curl.h>
#include "functions.h"

CURL *makeHandle(char *url) {
  CURL *handle = curl_easy_init();

  curl_easy_setopt(handle, CURLOPT_URL, url);
  curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(handle, CURLOPT_USE_SSL, CURLUSESSL_TRY);
  curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(handle, CURLOPT_USERAGENT, "App-Scraper");

  return handle;
}

int main(int argc, char const *argv[]) {
  //Grab env variables
  const char *handler = getenv("_HANDLER");
  const char *taskRoot = getenv("LAMBDA_TASK_ROOT");
  const char *runtimeAPI = getenv("AWS_LAMBDA_RUNTIME_API");

  //An intentional infinite loop
  for (;;) {
    // char *eventData =;
  }

  return 0;
}
