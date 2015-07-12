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
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
*/

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}


class Page {
public: 
  string body;
  Page (string b) {
    body = b;
  }
  /*
  set<string> getUniqWords() {
    set<string> uniqueWords;
    // string[] words = body.split(" ");
    for(int i = 0; i < words.length; i++) {
      uniqueWords.insert(words[i]);
    }
  }

  int countUniqWords() {
    return getUniqWords().size();
  }
  */
};

string getPageContent(string url) {
  string content = "";
  CURL *curl;
  //FILE *fp;
  CURLcode res;
  //char outfilename[FILENAME_MAX] = "content.txt";
  curl = curl_easy_init();
  if (curl) {
      //fp = fopen(outfilename,"wb");
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
      res = curl_easy_perform(curl);

      curl_easy_cleanup(curl);
      //fclose(fp);
  }
  return content;
}

set<string> getLinks(string html) {
  set<string> links;

  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);

  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();

  for (; it != end; ++it) {
    if (it->tagName() == "a") {
      it->parseAttributes();
      string link = it->attribute("href").second;
      links.insert(link);
    }
  }

  return links;
}
/*
string getBody(string html) {
  string body;
  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);

  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();

  for (; it != end; ++it) {
    if (it->tagName() == "body") {
      
      cout << it->text() << endl;
      body = it->text();
      break;
    }
  }
  return body;
}
*/
list<Page> crawl(string startUrl, int depth) {
  list<Page> pages;
  queue<string> unvisited;
  unvisited.push(startUrl);

  while (!unvisited.empty()) {
    string link = unvisited.front();
    unvisited.pop();
    string html = getPageContent(link);
    if (unvisited.size() < depth){
      set<string> links = getLinks(html);
      set<string>::iterator it = links.begin();
      set<string>::iterator end = links.end();
      for (; it != end; ++it) {
        unvisited.push(*it);
      }
    }
    string body = html;
    Page *page = new Page(body);
    pages.push_back(*page);
    if(pages.size() >= depth) {
      break;
    }

  }
  return pages;
}

int main(void) {
  int n = 10;
  string url = "https://www.messagexchange.com";
  list<Page> pages = crawl(url, n);
  list<Page>::iterator it = pages.begin();
  list<Page>::iterator end = pages.end();
  for (; it != end; ++it) {
    cout << it->body <<endl;
  }
  
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
