#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h> 

#include "curlPages.h"


int fonction_curl(char * site){


CURL *curl = curl_easy_init();
CURLcode response;
 
    if (!curl)
    {
        // fprintf(stderr,"[-] Failed Initializing Curl\n");
    }
 
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, site);
    res = curl_easy_perform(curl);
     
    if (res != CURLE_OK)
    {
        // fprintf(stderr,"[-] Could Not Fetch Webpage\n[+] Error : %s\n",curl_easy_strerror(res));
    }
 
    curl_easy_cleanup(curl);

    return(response == CURLE_OK) ? 1 : 0;

}


