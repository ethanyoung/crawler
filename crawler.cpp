#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <queue>
#include <set>
#include <curl/curl.h>

using namespace std;

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

string getPageContent(string url) {
  stirng content = "";
  return content;
}

Vextor<string> getLinks(string content) {
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "http://www.google.com";
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
    return 0;
}
