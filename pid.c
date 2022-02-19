#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

#include <threads.h>
#include <string.h>
#include <stdbool.h> 
#include <time.h>
#include <unistd.h>

bool Exit = false;

char ExistingFile(){

  FILE *p;  
  char *MYIDTXT = "3100.txt";

  if( access (MYIDTXT, F_OK) != -1){

    return true;

  }else{


    p = fopen(MYIDTXT, "w");
                    
    fprintf(p,"MOZILLA : Durée = 0\n");
    fprintf(p,"2048 : Durée = 0\n");

    fclose(p);

return false;
  }

  return 0;

}


int threadMain(void * needed) {


    FILE * p;
    char ligne[1024];
    char data[1024];
    double time_diff_mozilla;
    double time_diff_game;
    double time_diff;
    int index = 0;
    int i;
    bool block = false;
    bool block_time = false;
    int index_time = 0;
    char *MYIDTXT = "3100.txt";
    char *Environnement;


    bool app_detected;
    bool start_chrono = true;

    int has_MOZILLA = 0, has_VSCODE = 0;

    bool exist_file_for_this_id;

    double data_from_mozilla;
    double data_from_game;

    time_t debut;
    time_t end;



    while (!Exit) {

            if(needed == "/usr/lib/firefox-esr/firefox-esr" ){

                p = popen("ps aux | grep firefox | tee processes.txt", "r");
                Environnement = "Mozilla";
            }

            if(needed == "gnome-2048"){

                p = popen("ps aux | grep 2048 | tee processes2048.txt", "r");
                Environnement = "2048";
                
            }


            if (!p) {
                exit(-1);
            }

            while (fgets(ligne, sizeof(ligne), p)) {

                index++;

                if(index == 1){
            

                 if (strstr(ligne, needed) != NULL) {

                     // L'application a été detecte

                    // On démarre le chronomètre une seule fois et on informe au système que l'app a été detecté

                    if(start_chrono == true){

                         debut = time(NULL);
                         printf("yes\n");
                         app_detected = true;

                    }

                    start_chrono = false;
          

                 }else{

                    // On sait que l'appli a été fermé et que l'app a été detecté
                    // Donc on affiche le temps d'utilisation


                     if(app_detected == true){

                         end = time(NULL);

                        time_diff = difftime(end, debut);

                        // Récupération d'anciennes données

                          p = fopen(MYIDTXT, "r");

                            while (fgets(data, sizeof data, p)) {

                                sscanf(data, "MOZILLA : Durée = %lf\n", &data_from_mozilla);

                                sscanf(data, "2048 : Durée = %lf\n", &data_from_game);

                            }

                            fclose(p);

                            p = fopen(MYIDTXT, "w");

                            if(Environnement == "Mozilla"){
                                  fprintf(p,"Mozilla : Durée = %lf \n", time_diff + data_from_mozilla);
                                  fprintf(p,"2048 : Durée = %lf \n ", data_from_game);
                            }
                            
                            if(Environnement == "2048"){
                                fprintf(p,"Mozilla : Durée = %lf \n", data_from_mozilla);
                                fprintf(p,"2048 : Durée = %lf \n ", time_diff + data_from_game);
                            }


                            fclose(p);
                            printf("\n");


                        app_detected = false;


                     }
                 }
    
            }

    
        }

            
        index = 0;

    }

    
    printf("%s terminé !\n", data);
    return thrd_success;
}


int main() {

    ExistingFile();
    // On crée un premier thread.
    thrd_t thread1;

    // Pid of Mozilla
    void * MozillaFirefox = (void * )
    "/usr/lib/firefox-esr/firefox-esr";

    if (thrd_create( &thread1, threadMain, MozillaFirefox) != thrd_success) {
        fprintf(stderr, "Impossible de créer le premier thread\n");
        return EXIT_FAILURE;
    }

    // On crée un second thread.
    thrd_t thread2;

    // Pid of 2048
    void * threadName2 = (void * )
    "gnome-2048";

    if (thrd_create( &thread2, threadMain, threadName2) != thrd_success) {
        fprintf(stderr, "Impossible de créer le second thread\n");
        return EXIT_FAILURE;
    }

    char ch;
    scanf("%c", & ch);


    Exit = true;

    printf("Le thread initial/principal s'arrête.\n");
    return EXIT_SUCCESS;
}