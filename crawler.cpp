#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <queue>
#include <set>

#include <curl/curl.h>
#include <htmlcxx/html/ParserDom.h>

using namespace std;
using namespace htmlcxx;

/*
class WebPage {
  list<string> urls;
  string body;
  string[] getUniqWords() {
    set<string> uniqueWords;
    // string[] words = body.split(" ");
    for(int i = 0; i < words.length; i++) {
      uniqueWords.insert(words[i]);
    }
  }

  int countUniqWords() {
    return getUniqWords().size();
  }
}
*/

string getPageContent() {
  stirng content = "";
  CURL *curl;
  FILE *fp;
  CURLcode res;
  char *url = "https://www.messagexchange.com";
  char outfilename[FILENAME_MAX] = "content.txt";
  curl = curl_easy_init();
  if (curl) {
      fp = fopen(outfilename,"wb");
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
      res = curl_easy_perform(curl);

      curl_easy_cleanup(curl);
      fclose(fp);
  }
  return content;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
  int n = 10;
  string html = getPageContent();
  //getLinks(html);
  // if queue.size() < 10
  // for each links
  // visit 
  // get body
  // body.split.getUniqWords.size()
  //
  // for each links
  // visit
  // get body
  // body.split getUniqWords
  // total.insert uniqueWords
  // total.size()
  return 0;
}
