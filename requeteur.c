#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int database(int *proc, char *user, char *password){
    

    MYSQL *mysql;
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    
    char *Server = "blindly.fr";
    char *Utilisateur = "matthias"; // yuki
    char *MotDePasse = "azerty"; // azerty
    char *BaseDeDonnee = "projet"; // projet
    char requete[300];
    int temp;
    int chose;
    int *id;

    char website[200];
    char mail[200];
    char nocrypt[200];
    char *passwordCrypt[200];
    unsigned int i = 1;
    unsigned int num_champs = 0;

    mysql = mysql_init(NULL);
    /*Connexion a la base de donnée*/
    
    if(!mysql_real_connect(mysql,Server,Utilisateur,MotDePasse,BaseDeDonnee,0,NULL,0)){
        printf("Connexion error : %s" , mysql_error(mysql));
    } else{
        printf("Good");
    }


}