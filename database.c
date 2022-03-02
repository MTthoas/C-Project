#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <gtk-3.0/gtk/gtk.h>

#include <unistd.h>

#include <mysql.h>

#include <crypt.h>

#include <stddef.h>
#include "curlPages.h"
#include "transition.h"
#include "database.h"
#include <stdbool.h>
#include <threads.h>

int database(int proc, const gchar * user, const gchar * password, const gchar * email, const gchar * title) {



    MYSQL * mysql;
    MYSQL_RES * result = NULL;
    MYSQL_ROW row;

    char * Server = "blindly.fr";
    char * Utilisateur = "matthias"; // yuki
    char * MotDePasse = "azerty"; // azerty
    char * BaseDeDonnee = "projet"; // projet
    char requete[300];

    int temp;
    int chose;
    int * id;
    int good = 1;
    int error = 0;
    char website[200];
    char mail[200];
    char nocrypt[200];
    char * passwordCrypt[200];
    unsigned int i = 1;
    unsigned int num_champs = 0;
     int valeur;

    char resultat_table[20][20];

    mysql = mysql_init(NULL);
    /*Connexion a la base de donnée*/

    if (!mysql_real_connect(mysql, Server, Utilisateur, MotDePasse, BaseDeDonnee, 0, NULL, 0)) {
        g_print("Connexion error : %s", mysql_error(mysql));
    } else {
        /* Utilisation du proc pour définir quel requete*/
        switch (proc) {

            case 0: // Aucune requete
                printf("Ping");
                break;
            case 1:
                /* Inscription */
                printf("inscription");
                if (strlen(user) > 5 && strlen(password) > 5) {
                    sprintf(requete, "INSERT INTO User(pseudo,password)VALUES('%s','%s');", user, password);
                    mysql_query(mysql, requete);
                    return good;
                } else {
                    return error;
                }
                break;

            case 2:
                /*Connexion*/
                sprintf(requete, "SELECT* FROM User WHERE pseudo = '%s' AND password = '%s';", user, password);
                mysql_query(mysql, requete);
                result = mysql_use_result(mysql);
                num_champs = mysql_num_fields(result);
                while ((row = mysql_fetch_row(result))) {
                    unsigned long * lengths;
                    lengths = mysql_fetch_lengths(result);
                    for (i = 2; i < num_champs; i++) {
                        if (row[i] != NULL) {
                            printf("It's good\n");
                            return good;
                        } else {}
                    }


                    lengths = mysql_fetch_lengths(result);
                    for (i = 0; i < num_champs; i++) {
                        if (row[i] != NULL) {

                            printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");

                        }
                    }
                    printf("\n");
                }
                mysql_free_result(result);

                if (chose == 1) { // Choix du mot de passe a décrypter
                    printf("Quel est le numéro ? ");
                    scanf("%s", id);
                    sprintf(requete, "SELECT * FROM Compte WHERE id = '%s' AND pseudo = '%s';", id, user);
                    mysql_query(mysql, requete);
                    result = mysql_use_result(mysql);


                } else {

                }


                break;
            case 4:
                /* Ajout d'un mot de passe */
                fflush(stdin);
                printf("Veuillez renseigner le nom du sites\n");
                scanf("%s", & website[0]);
                printf("Veuillez renseigner votre mail\n");
                scanf("%s", & mail[0]);
                printf("Et votre mot de passe\n");
                scanf("%d", & temp);
                scanf("%s", & nocrypt[0]);
                // passwordCrypt[0] = crypt(nocrypt, "AAA");


                sprintf(requete, "INSERT INTO Compte(pseudo,nameWeb,mail,passwordsite)VALUES('%s','%s','%s','%s');", user, website, mail, passwordCrypt[0]);
                mysql_query(mysql, requete);

                mysql_close(mysql);

                // home(user, password);
                break;


            case 5:

                sprintf(requete, "INSERT INTO data_hubby(UserID,title,email,mdp)VALUES('%s','%s','%s','%s');", user, title, email, password);
                mysql_query(mysql, requete);
                mysql_close(mysql);
                return good;

            break;

            case 6:

                sprintf(requete, "INSERT INTO data_time(UserID,title,email,mdp)VALUES('%s','%s','%s','%s');", user, title, email, password);
                mysql_query(mysql, requete);
                mysql_close(mysql);


            break;

            case 99:
                printf("Connexion réussi");
        }



    }
}

unsigned char * fetch_database_data(int proc, const gchar * user,  const gchar * password) {

    MYSQL * mysql;
    MYSQL_RES * result = NULL;
    MYSQL_ROW row;

    char * Server = "blindly.fr";
    char * Utilisateur = "matthias"; // yuki
    char * MotDePasse = "azerty"; // azerty
    char * BaseDeDonnee = "projet"; // projet
    char requete[300];

    int temp;
    int chose;
    int * id;
    int good = 1;
    int error = 0;
    unsigned int mysql_result_nb = 0;

    char website[200];
    char mail[200];
    char nocrypt[200];
    char * passwordCrypt[200];
    unsigned int i = 1;
    unsigned int num_champs = 0;

    unsigned char * valeur;
    unsigned char * fetch_userID;
    unsigned char * fetch_data;
    unsigned char * fetch_email;
    unsigned char * fetch_mdp;


    unsigned char valeur_original;
    unsigned char fetch_userID_original;
    unsigned char fetch_data_original;
    unsigned char fetch_email_original;
    unsigned char fetch_mdp_original;

    char * result_table[20];
    int index = 0;
    char array[100][100];

    mysql = mysql_init(NULL);
    /*Connexion a la base de donnée*/

    if (!mysql_real_connect(mysql, Server, Utilisateur, MotDePasse, BaseDeDonnee, 0, NULL, 0)) {
        g_print("Connexion error : %s", mysql_error(mysql));
    } else {

        switch (proc) {

            case 0:

                // ---------- //
                //  FETCH ID  //
                // ---------- //
                
                sprintf(requete, "SELECT id FROM User WHERE pseudo = '%s' AND password = '%s';", user, password);
                mysql_query(mysql, requete);
                result = mysql_use_result(mysql);

                //On récupère le nombre de champs
                num_champs = mysql_num_fields(result);

                //Tant qu'il y a encore un résultat ...
                while ((row = mysql_fetch_row(result))) {
                    //On déclare un pointeur long non signé pour y stocker la taille des valeurs
                    unsigned long * lengths;

                    //On stocke ces tailles dans le pointeur
                    lengths = mysql_fetch_lengths(result);

                    //On fait une boucle pour avoir la valeur de chaque champs
                    for (i = 0; i < num_champs; i++) {
                        //On ecrit toutes les valeurs
                        // printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
                        return valeur = row[i];

                    }
                    printf("\n");

                }


                mysql_free_result(result);
                mysql_close(mysql);

                break;

            case 1:

                // ---------- //
                // FETCH data //
                // ---------- //

                sprintf(requete, "SELECT * FROM data_hubby WHERE UserID = '%s'", user);
                mysql_query(mysql, requete);
                result = mysql_use_result(mysql);

                mysql_result_nb = mysql_num_fields(result);

                // char *data[20] = malloc(sizeof(char) * 400);
                char ** data = malloc(sizeof(char * ) * 5);

                if (data == NULL) {
                    puts("data null");
                    exit(1);
                }



                for (int c = 0; c < 5; c++) {

                    data[c] = malloc(sizeof(char) * 51);

                    if (data[c] == NULL) {
                        puts("exemple null");
                        exit(1);

                    }

                }


                while ((row = mysql_fetch_row(result))) {

                    unsigned long * lengths;

                    lengths = mysql_fetch_lengths(result);


                    for (i = 0; i < mysql_result_nb; i++) {

                        // printf("[%.*s] ", (int) lengths[i],row[i] ? row[i] : "NULL");

                        sprintf( & array[0][index], "%s", row[i]);


                        // strcpy(&data[j][0],row[i]);


                        // strcpy(data[i], row[i]);                     

                    }

                    // puts(result_table[0]);

                    index++;
                    // printf("\n");
                    printf("J = %d\n", index);
                }



                for (int k = 0; k < ( * result).row_count; k++) {
                    printf("%s\n", array[k]);
                }

                mysql_free_result(result);
                mysql_close(mysql);


                // return (unsigned char*) data;


                // for (int i = 0; i <5; i++)
                // {
                //     printf("%s\n", result_table[i]);
                // }



                // char* arrayReturnData = malloc(sizeof(int)*size);



                // strcpy(result_table,result_table_returned);







                break;

        }

    }
}

void databaseT(int proc, char *user, char *password)
{
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

    char title[200];
    char email[200];
    char pword[200];
    char *passwordCrypt[200];
    unsigned int i = 1;
    unsigned int num_champs = 0;
    unsigned char * fetch_id; 
   
    
    fetch_id = fetch_database_data(0,user, password);
    
    mysql = mysql_init(NULL);
    /*Connexion a la base de donnée*/
    
    if(!mysql_real_connect(mysql,Server,Utilisateur,MotDePasse,BaseDeDonnee,0,NULL,0)){
        printf("Connexion error : %s" , mysql_error(mysql));
    } else{
        /* Utilisation du proc pour définir quel requete*/
        switch (proc){
            case 0: // Aucune requete
                printf("Aucune commande a réaliser");
                break;

            case 1: /* Inscription */
                printf("inscripton");
                sprintf(requete, "INSERT INTO User(pseudo,password)VALUES('%s','%s');",user,password);
                mysql_query(mysql, requete);
                break;

            case 2: /*Connexion*/
                sprintf(requete, "SELECT* FROM User WHERE pseudo = '%s' AND password = '%s';", user, password);
                mysql_query(mysql, requete);
                result = mysql_use_result(mysql);
                num_champs = mysql_num_fields(result);
                while((row = mysql_fetch_row(result)))
                {
                    unsigned long *lengths;
                    lengths = mysql_fetch_lengths(result);
                    for(i = 2; i < num_champs; i++)
                        {
                            if(row[i] != NULL){
                            }
                        }
                    
                    
                    
                    
                    }
                break;
            case 3: /*List des mot de passe*/
        
                
                
                

                sprintf(requete, "SELECT * FROM data_hubby WHERE UserID = '%s';", fetch_id);
                mysql_query(mysql, requete);
                result = mysql_use_result(mysql);
                num_champs = mysql_num_fields(result);
                while((row = mysql_fetch_row(result)))
                {
                    unsigned long *lengths;
                    lengths = mysql_fetch_lengths(result);
                    for(i = 0; i < num_champs; i++)
                        {
                            if(row[i] != NULL){
                                printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
                                
                                
                            }
                        }
                    printf("\n");
                }
                mysql_free_result(result);
                
                break;
            case 4: /* Ajout d'un mot de passe */
            
                fflush(stdin);
                printf("Veuillez renseigner le nom du sites\n");
                scanf("%s",&title[0]);
                printf("Veuillez renseigner votre mail\n");
                scanf("%s",&email[0]);
                printf("Votre mot de passe\n");
                scanf("%d",&temp);
                scanf("%s",&pword[0]);
                                
                
                sprintf(requete, "INSERT INTO data_hubby(UserID,title,email,mdp)VALUES('%s','%s','%s','%s');",fetch_id , title, email, pword);
                mysql_query(mysql, requete);
            
                break;
            case 99:
                printf("Connexion réussi");
                }
    
                
        
        }
}

