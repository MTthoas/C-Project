#include <stdio.h>                                                              
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <time.h>
#include <unistd.h>

// char MozillaTime(const char *MYIDTXT){};


bool ExistingFile(const char *MYIDTXT){

  FILE *p;

  if( access (MYIDTXT, F_OK) != -1){

    return true;

  }else{


    p = fopen(MYIDTXT, "w");
                    
    fprintf(p,"Durée = 0");

    fclose(p);

return false;
  }

return 0;

}


char MozillaTime(const char *MYIDTXT){

  FILE *p;
  char ligne[1024];
  char data[1024];
  double time_diff;
  int index = 0;
  char *needed = "/usr/lib/firefox-esr/firefox-esr";
  int i;
  bool block = false;
  bool block_time = false;
  int index_time;
  
  bool exist_file_for_this_id;
  double data_from_file;

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

               if(strstr(ligne, needed) != NULL ){


                 if(block_time == false){
                     debut = time(NULL);
                 }
          
                   index_time = 0;
                   block_time = true;
                   

               }else{

                    if(index_time == 0){

                      end = time(NULL);

        
                      time_diff = difftime(end,debut);
                  
                    printf("OUUUUUUUUUUUUUUUUI");

                    // Fetch some data..

                      p = fopen(MYIDTXT, "r");

                      while(fgets(data, sizeof data, p)){

                        sscanf(data, "Durée = %lf", &data_from_file);
                        printf("%s", data_from_file);

                      }

                      fclose(p);

                      
                      time_diff = time_diff + data_from_file;

                      // INSERT TO MYIDTXT

                    p = fopen(MYIDTXT, "w");
                    
                    fprintf(p,"Durée = %lf",time_diff);

                    fclose(p);
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






  
};


int main(void) {
  
      char *MYIDTXT = "3000.txt";

    ExistingFile(MYIDTXT);

    MozillaTime(MYIDTXT);
  

}