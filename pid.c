#include <stdio.h>                                                              
#include <stdlib.h>

int main() {
  char ligne[1024];
  int index = 0;

   FILE *p = popen("ps aux | grep firefox | tee processes.txt", "r");


  if (!p) {
    exit(-1);
  }

   
   
   while( fgets(ligne, sizeof(ligne), p) ) {
       index++;

       if(index == 1){

               printf("%s",ligne);
       }


   }


  pclose(p);
}