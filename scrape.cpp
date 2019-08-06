#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string doCurl(string curlURL)
{
  string readBuffer;
  CURL * curlhandle = curl_easy_init();
  if(curlhandle) {
    curl_easy_setopt(curlhandle, CURLOPT_URL, curlURL.c_str());
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0);
    curl_easy_setopt(curlhandle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_perform(curlhandle);
    curl_easy_cleanup(curlhandle);
  }
  return readBuffer;
}

void writeToFile(string curlOut, string filename)
{
  ofstream outfile;
  if (filename == "") {
    outfile.open ("rr.html");
  } else {
    outfile.open (filename);
  }
  outfile << curlOut;
  outfile.close();
}

string getFictionId()
{
  string fictionId;
  string urlPrefix = "http://www.royalroad.com/fiction/";
  cout << "Enter Fiction ID: ";
  cin >> fictionId;
  string fictionUrl = urlPrefix + fictionId;
  return fictionUrl;
}

int main(void)
{
  string fictionUrl = getFictionId();
  cout << "Scraping..." << endl;
  string curlOut = doCurl(fictionUrl);
  string filename;

  /*// Gives custom filenames
  cout << "Please enter name of file to save to here: ";
  cin >> filename;
  */

  cout << "Writing File..." << endl;
  writeToFile(curlOut, filename);
  system("./stringWizard.sh");

  return 0;
}
