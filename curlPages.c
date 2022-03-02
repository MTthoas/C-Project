#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h> 

#include <gtk-3.0/gtk/gtk.h>

#include "curlPages.h"


int fonction_curl(char * site){


CURL *curl = curl_easy_init();
CURLcode response;
 
    if (!curl)
    {
        // fprintf(stderr,"[-] Failed Initializing Curl\n");
    }

    // printf("%s\n",site);

    g_print("%s\n",site);
   

    curl_easy_setopt(curl, CURLOPT_URL, site);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    response = curl_easy_perform(curl);
 
    curl_easy_cleanup(curl);

    return(response == CURLE_OK) ? 1 : 0;

}


