#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/uri.h>
#include <curl/curl.h>
#include "functions.h"

CURLcode doRequest(char *url) {
  CURL *handle = curl_easy_init();

  curl_easy_setopt(handle, CURLOPT_URL, url);
  curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(handle, CURLOPT_USE_SSL, CURLUSESSL_TRY);
  curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(handle, CURLOPT_USERAGENT, "App-Scraper");

  CURLcode result = curl_easy_perform(handle);
  return result;
}

int main(int argc, char const *argv[]) {
  //Grab env variables
  const char *handler = getenv("_HANDLER");
  const char *taskRoot = getenv("LAMBDA_TASK_ROOT");
  const char *runtimeAPI = getenv("AWS_LAMBDA_RUNTIME_API");

  // char *url = "http://" + AWS_LAMBDA_RUNTIME_API + "/2018-06-01/runtime/invocation/next";
  printf("PreUrl\n", );
  char *url = "http://";
  strcat(url, "example.com");
  printf("PostUrl\n");
  CURLcode result = doRequest(url);


  //An intentional infinite loop
  // for (;;) {
    // char *eventData = curl_easy_preform(url);
  // }

  return 0;
}
