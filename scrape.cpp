#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string doCurl(std::string curlURL)
{
  std::string readBuffer;
  CURL * curlhandle = curl_easy_init();
  if(curlhandle) {
    curl_easy_setopt(curlhandle, CURLOPT_URL, curlURL.c_str());
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1);
    curl_easy_setopt(curlhandle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_perform(curlhandle);
    curl_easy_cleanup(curlhandle);
  }
  return readBuffer;
}

int main(void)
{
  std::string curlLoc = "http://www.royalroad.com/fiction/11209/";
  std::cout << doCurl(curlLoc) << '\n';
}
