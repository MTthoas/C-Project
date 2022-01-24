#include <stdio.h>                                                              
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <time.h>

int main() {
  FILE *p;
  char ligne[1024];
  int index = 0;
  char *needed = "/usr/lib/firefox-esr/firefox-esr";
  int i;
  bool block = false;
  bool block_time = false;
  int index_time = 0;
  int myID = 3200;

    time_t debut;
    time_t end;


  for(i=0; block == false; i++ ){

   p = popen("ps aux | grep firefox | tee processes.txt", "r");


  if (!p) {
    exit(-1);
  }
   
   while( fgets(ligne, sizeof(ligne), p) ) {
       index++;

       if(index == 1){

               printf("%s",ligne);

               if(strstr(ligne, needed) != NULL ){


                 if(block_time == false){
                     debut = time(NULL);
                 }
          
                   index_time = 0;
                   block_time = true;
                   


               }else{

                    if(index_time == 0){

                      end = time(NULL);
                    double time_diff = difftime(end,debut);

                    printf("Durée = %lf s\n",time_diff);
                    // printf("End of program");

                    // block = true;
                         index_time++;
                         block_time = false;
                    }
               }
       }
   }

   index = 0;
  pclose(p);


  }

}