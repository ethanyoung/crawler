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

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

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
  string content = "";
  CURL *curl;
  //FILE *fp;
  CURLcode res;
  char *url = "https://www.messagexchange.com";
  //char outfilename[FILENAME_MAX] = "content.txt";
  curl = curl_easy_init();
  if (curl) {
      //fp = fopen(outfilename,"wb");
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
      res = curl_easy_perform(curl);

      curl_easy_cleanup(curl);
      //fclose(fp);
  }
  return content;
}

vector<string> getLinks(string html, int depth) {
  vector<string> links;

  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);

  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();

  for (; it != end; ++it) {
    if (it->tagName() == "a") {
      it->parseAttributes();
      string link = it->attribute("href").second;
      cout << link << endl;
      links.push_back(link);
    }
  }

  return links;
}

int main(void) {
  int n = 10;
  string html = getPageContent();
  //cout << html << endl;
  getLinks(html, n);
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
