#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;


// Todo: Figure out how/why this works and what it does
// Things I Know:
//    It breaks the program if I remove it
//    It breaks the program if I remove the call to it
//    It interacts with CURLOPT_WRITEDATA somehow
//      ^ involves the last argument
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


// If you pass 1 to second arg, won't cleanup connection.
// Probably useful to not cleanup when scraping,
//    to make things less intesive for everyone.
string doCurl(string curlURL, int doCleanup = 0) {
  string readBuffer;
  CURL * curlhandle = curl_easy_init();
  if(curlhandle) {
    curl_easy_setopt(curlhandle, CURLOPT_URL, curlURL.c_str());
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0);
    curl_easy_setopt(curlhandle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_perform(curlhandle);
    if (doCleanup == 0) {
      curl_easy_cleanup(curlhandle);
    }

  }
  return readBuffer;
}


// Probably a better way to do this, but whatever
void writeToFile(string curlOut) {
  ofstream outfile;
  outfile.open ("rr.html");
  outfile << curlOut;
  outfile.close();
}

// Todo: Make this a CLI argument
string getFictionId() {
  string fictionId;
  string urlPrefix = "http://www.royalroad.com/fiction/";
  cout << "Enter Fiction ID: ";
  cin >> fictionId;
  string fictionUrl = urlPrefix + fictionId;
  return fictionUrl;
}

int main(void) {
  cout << "Scraping fiction page..." << endl;
  string fictionUrl = getFictionId();
  string curlOut = doCurl(fictionUrl);

  cout << "Writing File..." << endl;
  writeToFile(curlOut);

  cout << "String Wizardry!" << endl;
  system("./stringWizard.sh");

  return 0;
}
