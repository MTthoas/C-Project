#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h> 

#include "curlPages.h"


void fonction_curl(char *site){


printf("yeees");

CURL *curl = curl_easy_init();
 
    if (!curl)
    {
        fprintf(stderr,"[-] Failed Initializing Curl\n");
        exit(-1);
    }
 
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, site);
    res = curl_easy_perform(curl);
     
    if (res != CURLE_OK)
    {
        fprintf(stderr,"[-] Could Not Fetch Webpage\n[+] Error : %s\n",curl_easy_strerror(res));
        exit(-2);
    }
 
    curl_easy_cleanup(curl);

}

int main(); 


