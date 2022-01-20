#include <mysql/mysql.h>
#include <stddef.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void database(int proc, char *user, char *password);

void connexion (){
    char user[20];
    char password[20];
    int temp;
    unsigned long longueur_USER = 0;
    unsigned long longueur_PWD = 0;
    int i = 0;
    int c = 0;
    char verifUser[30];
    char verifPassword[30];
    
    
    
    while(i<1){
        fflush(stdin);
        printf("Veuillez renseignez votre utilisateur\n");
        scanf("%d",&temp);
        scanf("%[^\n]",user);
        
        longueur_USER = strlen(user);
        if(longueur_USER > 1){
            i = 1;
            printf("Votre nom d'utilisateur est %s\n",user);
        }
    }
    
    while(c<1){
        fflush(stdin);
        printf("Veuillez renseignez votre mot de passe\n");
        scanf("%[^\n]",password);
        longueur_PWD = strlen(password);
        if(longueur_PWD > 1){
            c = 1;
            printf("Votre mot de passe est %s\n",password);
        }
    }
    
    
    
    
}

void inscription(){
    char user[20];
    char password[20];
    int temp;
    unsigned long longueur_USER = 0;
    unsigned long longueur_PWD = 0;
    int i = 0;
    int c = 0;
    char *passwordCryp;


    while(i<1){
        fflush(stdin);
        printf("Veuillez renseignez votre utilisateur\n");
        scanf("%d",&temp);
        scanf("%[^\n]",user);
        
        longueur_USER = strlen(user);
        if(longueur_USER > 1){
            i = 1;
            printf("Votre nom d'utilisateur est %s\n",user);
        }
    }
    
    while(c<1){
        fflush(stdin);
        printf("Veuillez renseignez votre mot de passe\n");
        scanf("%[^\n]",password);
        longueur_PWD = strlen(password);
        if(longueur_PWD > 1){
            c = 1;
            printf("Votre mot de passe est %s\n",password);
        }
    }
    
    // passwordCryp = crypt(password,"AAA");
    // database(1, &user[0], &passwordCryp[0]);
    
}

void database(int proc, char *user, char *password)
{
    MYSQL *mysql;
    
    char *Server = "blindly.fr";
    char *Utilisateur = "yuki";
    char *MotDePasse = "azerty";
    char *BaseDeDonnee = "projet";
    
    mysql = mysql_init(NULL);
    
    if(!mysql_real_connect(mysql,Server,Utilisateur,MotDePasse,BaseDeDonnee,0,NULL,0)){
        printf("Connexion error");
    } else{
        switch (proc){
            case 0:
                printf("Aucune commande a réaliser");
                break;
            case 1:
                printf("Exectution\n");
                printf("%s %s\n", user , password);
                char requete[300];
                sprintf(requete, "INSERT INTO User(pseudo,password)VALUES('%s','%s')",user,password);
                mysql_query(mysql, requete);
        	
                break;
            case 2:
                break;
        }
        
    }
    
}


int main(int argc, const char **argv){
    int val;
    printf("-- Accueil --\n");
    printf("1- Inscription\n2- Connexion\n3- Ping Database\n");
    scanf("%d", &val);
    switch(val){
        case 1:
            inscription();
            break;
        case 2:
            connexion();
            break;
            
        case 3:
           // database();
            break;
    }
    return 0;
}
