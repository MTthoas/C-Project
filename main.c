#include <stdio.h>

#include <curl/curl.h>

#include <stdlib.h>

#include <string.h>

#include <gtk-3.0/gtk/gtk.h>

#include <unistd.h>

#include <mysql.h>

#include <crypt.h>

#include <stddef.h>

#include "curlPages.h"

#include <stdbool.h>
#include <threads.h>



void * create_main(GtkWidget * stack);
GtkWidget * Login_page(GtkWidget * stack);
GtkWidget * Register_page(GtkWidget * stack);
void create_hubby(GtkWidget * stack);
GtkWidget * choice_menu(GtkWidget * stack);
GtkWidget * time_menu(GtkWidget * stack);
void quit_time_app(GtkWidget *w);
void start_link(GtkButton * button);
bool Exit = false;

int CalculTime();
char ExistingFile();
int threadMain(void * needed);

GtkWidget * object;

 GtkWidget *window_hubby;
 GtkWidget *window_app_time;
GtkWidget *window_enable_data;

char buffer[100];


unsigned char * fetch_database_data(int proc,const gchar * user, const gchar * password);
// int data_entry_hubby(const gint * userID, const gchar * title, const gchar * email, const gchar * mdp);

int database(int proc,const gchar * user,const gchar * password,const gchar * email, const gchar * title);
// unsigned char * fetch_data(const gchar *userID);


void verification_add_data(GtkWidget *w);
void start_box_clbk(GtkWidget *w);
void login_clbk(GtkButton * button, GtkStack * stack);
void main_clbk(GtkButton * button, GtkStack * stack);
void register_clbk(GtkButton * button, GtkStack * stack);
void hubby_clbk(GtkButton * button, GtkStack * stack);
void time_clbk(GtkButton * button, GtkStack * stack);
void choice_clbk(GtkButton * button, GtkStack * stack);
void start_box(void);
void create_time_app();

void clicked_clbk(GtkButton * button, GtkStack * stack);
void quit_clbk(void);

int terminal();

GtkWidget * entry_username;
GtkWidget * entry_password;

GtkWidget * entry_username2;
GtkWidget * entry_password2;

    GtkWidget * entry_title;
    GtkWidget * entry_email;
    GtkWidget * entry_mdp;


void verification_login(GtkButton * button, GtkStack * stack, gpointer data);
void verification_register(GtkButton * button, GtkStack * stack, gpointer data);

static GtkWidget *pLabel;



unsigned int mysql_result_nb = 0;

int ConfigSetup(){
    
    
    
    FILE * f = NULL;

    f = fopen("config.txt","r");
    int tab[3]; 
    char str1[3]="",str2[3]="",str3[3]="",str4[3]="";
    if(f != NULL) {
        fscanf(f, "%s %s", str1, str2);
        tab[1]=atoi(str2);
        tab[2]= atoi(str4);
        
        fclose(f);

    } else {
        printf("Impossible de lire le fichier");
    }
    
    if (tab[1] == 1){
        g_print("test");
        return 0;
    } else if(tab[1] == 0){
        terminal();
        return EXIT_SUCCESS;
            }
    // Graphique

    // Crash app
    // Nom de l'app
}


int main(void) {

    // system("firefox http://google.fr");
    

    GtkWidget * window;
    GtkWidget * main;
    GtkWidget * login_grid;
    GtkWidget * register_grid;
    GtkWidget * stack;
    GtkWidget * box;
    GtkWidget * hubby_grid;
    GtkWidget * choice_grid;
    GtkWidget * time_grid;


    ConfigSetup();

    
    // Initialisation

    gtk_init(NULL, NULL);

    // CREATION FENETRE


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // TITRE DE LA FENETRE

    gtk_window_set_title(GTK_WINDOW(window), "HUBBY");
    g_signal_connect(window, "destroy", gtk_main_quit, window);

    // PARAMETRES DE LA FENETRE 

    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    /// *** Create the Box

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    /// *** Create a Stack

    stack = gtk_stack_new();
    gtk_widget_set_halign(stack, GTK_ALIGN_CENTER);
    gtk_box_set_center_widget(GTK_BOX(box), stack);

    gtk_container_add(GTK_CONTAINER(window), box);

    /// ***

    main = create_main(stack);
    login_grid = Login_page(stack);
    register_grid = Register_page(stack);
    // hubby_grid    = create_hubby  ( stack );
    choice_grid = choice_menu(stack);
    time_grid = time_menu(stack);

    /// **
    gtk_stack_add_named(GTK_STACK(stack), main, "Main");
    gtk_stack_add_named(GTK_STACK(stack), login_grid, "Login");
    gtk_stack_add_named(GTK_STACK(stack), register_grid, "Register");
    // gtk_stack_add_named  ( GTK_STACK ( stack ), hubby_grid,    "HUBBY"    );
    gtk_stack_add_named(GTK_STACK(stack), choice_grid, "CHOICE");
    gtk_stack_add_named(GTK_STACK(stack), time_grid, "TIME");

    /// ***
    gtk_widget_show_all(window);
    gtk_main();
}

void * create_main(GtkWidget * stack) {


    GtkWidget * box;
    GtkWidget * login_button;
    GtkWidget * register_button;
    GtkWidget * close_button;

    /// *** Create the Box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  
    /// *** Create the Buttons
    login_button = gtk_button_new_with_label("Login");
    register_button = gtk_button_new_with_label("Register");

    /// *** Add them to the Box
    gtk_box_pack_start(GTK_BOX(box), login_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), register_button, TRUE, TRUE, 0);


    /// ***
    g_signal_connect(login_button, "clicked", G_CALLBACK(login_clbk), stack);
    g_signal_connect(register_button, "clicked", G_CALLBACK(register_clbk), stack);

    /// *** Return the Box
    return box;
}

GtkWidget * Login_page(GtkWidget * stack) {
    GtkWidget * box;

    GtkWidget * login_button;
    GtkWidget * back_button;

    GtkWidget * label_username2;
    GtkWidget * label_password2;


    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);


    label_username2 = gtk_label_new("Username:");
    gtk_box_pack_start(GTK_BOX(box), label_username2, TRUE, FALSE, 0);

    entry_username = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_username, TRUE, FALSE, 0);



    label_password2 = gtk_label_new("Password:");
    gtk_box_pack_start(GTK_BOX(box), label_password2, TRUE, FALSE, 0);

    entry_password = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_password, TRUE, FALSE, 0);

    login_button = gtk_button_new_with_label("Login");
    gtk_box_pack_start(GTK_BOX(box), login_button, TRUE, FALSE, 0);


    back_button = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);

    /// ***
    // login_button = gtk_button_new_with_label ( "Login" );
    // back_button  = gtk_button_new_with_label ( "Retour" );

    /// ***


    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(verification_login), stack);


    g_signal_connect(back_button, "clicked", G_CALLBACK(main_clbk), stack);

    /// ***
    return box;
}

GtkWidget * choice_menu(GtkWidget * stack) {


    static GtkWidget *window;

    GtkWidget * box;
    GtkWidget * hubby_button;
    GtkWidget * time_apps_button;
    GtkWidget * close_button;
    GtkWidget * back_button;

    /// *** Create the Box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    /// *** Create the Buttons
    hubby_button = gtk_button_new_with_label("HUBBY");
    time_apps_button = gtk_button_new_with_label("TIME SPENT ON APPS");

    /// *** Add them to the Box
    gtk_box_pack_start(GTK_BOX(box), hubby_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), time_apps_button, TRUE, TRUE, 0);

    /// ***
    g_signal_connect(hubby_button, "clicked", G_CALLBACK(create_hubby), stack);
    g_signal_connect(time_apps_button, "clicked", G_CALLBACK(create_time_app), NULL);



    back_button = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);

    g_signal_connect(back_button, "clicked", G_CALLBACK(main_clbk), stack);


    gtk_widget_set_size_request(back_button, 10, 4);

    /// *** Return the Box
    return box;



}

GtkWidget * time_menu(GtkWidget * stack) {

    GtkWidget * box;


    /// *** Create the Box
   box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget * back_button;

 


    back_button = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);

    g_signal_connect(back_button, "clicked", G_CALLBACK(choice_clbk), stack);


   return box;



 }

void create_hubby(GtkWidget * stack) {

    GtkWidget * grid;
    GtkWidget * label_description;
    GtkWidget * box;
    GtkWidget * box2;
    GtkWidget * box3;


    GtkWidget * back_button;
    GtkWidget * add_button;
    // GtkWidget * start_link;

        char tempo[20];
    GtkWidget * label_id[20];
    GtkWidget * label_title[50];
    GtkWidget * label_email[50];
    GtkWidget * label_mdp[50];
    GtkWidget * Separator[50];
    GtkWidget * label_state[50];
    GtkWidget * label_title_gchar[50];


    MYSQL * mysql;
    MYSQL_RES * result = NULL;
    MYSQL_ROW row;

    int index = 0;
      unsigned int i = 1;

    char * Server = "blindly.fr";
    char * Utilisateur = "matthias"; // yuki
    char * MotDePasse = "azerty"; // azerty
    char * BaseDeDonnee = "projet"; // projet
    char requete[300];

    mysql = mysql_init(NULL);
    /*Connexion a la base de donnée*/

 if (!mysql_real_connect(mysql, Server, Utilisateur, MotDePasse, BaseDeDonnee, 0, NULL, 0)) {
        g_print("Connexion error : %s", mysql_error(mysql));
    } else {

    window_hubby = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_hubby), "HUBBY");
    gtk_window_set_default_size(GTK_WINDOW(window_hubby), 300, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window_hubby), 30);
    gtk_window_set_resizable(GTK_WINDOW(window_hubby), FALSE);


    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    gtk_container_add(GTK_CONTAINER(window_hubby), box);

    label_description = gtk_label_new("GESTIONNAIRE DE MOT DE PASSE");



    unsigned char * fetch_id;
    const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
    fetch_id = fetch_database_data(0,user , pass);

    sprintf(requete, "select Id,UserID,title,email, AES_DECRYPT(mdp, 'clefsecrete') as `mdp` from data_huuby_v2 WHERE UserID = '%s'", fetch_id);
    mysql_query(mysql, requete);
    result = mysql_use_result(mysql);

    mysql_result_nb = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result))) {

        unsigned long * lengths;

        lengths = mysql_fetch_lengths(result);


        for (int i = 0; i < mysql_result_nb; i++) {

            Separator[index] = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

            label_title[index] = gtk_button_new_with_label(row[2]);
            


      if(i == 1){

            int checking_curl = fonction_curl(row[2]);

            if(checking_curl == 1)
            {
                label_state[index] = gtk_label_new("Site ON");

            }else{

                label_state[index] = gtk_label_new("Site OFF");
            }

    }

            label_email[index] = gtk_label_new(row[3]);
            label_mdp[index] = gtk_label_new(row[4]);   


        }


        gtk_box_pack_start(GTK_BOX(box3), Separator[index], TRUE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box3), label_title[index], TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(box3), label_state[index], TRUE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box3), label_email[index], TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(box3), label_mdp[index], TRUE, TRUE, 0);

        g_signal_connect(G_OBJECT(label_title[index]), "clicked", G_CALLBACK(start_link), label_title[index]);
        // g_signal_connect_swapped (G_OBJECT(label_title[index]), "clicked", G_CALLBACK(quit_time_app), window_hubby);
           

        index++;
        printf("J = %d\n", index); 




    

    }

   

       

    mysql_free_result(result);
    mysql_close(mysql);

    // label_three = gtk_label_new("U.GG");

    gtk_box_pack_start(GTK_BOX(box), label_description, TRUE, TRUE, 0);

    GtkWidget * scrolled_window;

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);


    gtk_container_add(GTK_CONTAINER(scrolled_window), box2);

    gtk_box_pack_start(GTK_BOX(box2), box3, TRUE, TRUE, 0);

    add_button = gtk_button_new_with_label("Ajout");
    gtk_box_pack_start(GTK_BOX(box), add_button, TRUE, FALSE, 0);

    g_signal_connect_swapped (add_button, "clicked", G_CALLBACK(start_box_clbk), window_hubby);

    // back_button = gtk_button_new_with_label ( "Retour" );
    // gtk_box_pack_start(GTK_BOX(box),  back_button , TRUE, FALSE, 0);

    // g_signal_connect ( back_button, "clicked", G_CALLBACK ( choice_clbk ), stack );


    gtk_widget_show_all(window_hubby);


    }
}

void start_link(GtkButton * button){

     const gchar* text;

     gchar* firefox = "firefox ";


     text = gtk_button_get_label(button);

  char* result = (char*) malloc((strlen(text)+ strlen(firefox))*sizeof(char));

  strcpy(result, firefox);
  strcat(result, text);
    system(result);
    // system("firefox google.fr");

    // free(result);
}

void create_time_app(){

    GtkWidget * box;
    GtkWidget * box2;

    GtkWidget * label_description;
    GtkWidget * Firefox;
    GtkWidget * back_button;

    window_app_time = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    ;


    gtk_window_set_title(GTK_WINDOW(window_app_time), "TIMMY");
    gtk_window_set_default_size(GTK_WINDOW(window_app_time), 300, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window_app_time), 30);
    gtk_window_set_resizable(GTK_WINDOW(window_app_time), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


    gtk_container_add(GTK_CONTAINER(window_app_time), box);

    label_description = gtk_label_new("Temps passé sur les applications");
    gtk_box_pack_start(GTK_BOX(box), label_description, TRUE, TRUE, 0);
    
   // Zone de texte.
    
    Firefox = gtk_label_new("Firefox");



    GtkWidget * scrolled_window;

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);


    gtk_container_add(GTK_CONTAINER(scrolled_window), box2);

    back_button = gtk_button_new_with_label("Quitter");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);



    // g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer) window);


    gtk_widget_show_all(window_app_time);
    g_signal_connect_swapped (back_button, "clicked", G_CALLBACK(quit_time_app), window_app_time);
    
}

void quit_time_app(GtkWidget *w){

     gtk_widget_destroy(w);

}

void start_box_clbk(GtkWidget *w){

    gtk_widget_destroy(w);
    start_box();



}

void start_box(void) {


    GtkWidget * box;

    window_enable_data = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // TITRE DE LA FENETRE

    gtk_window_set_title(GTK_WINDOW(window_enable_data), "HUBBY");

    // PARAMETRES DE LA FENETRE 

    gtk_window_set_default_size(GTK_WINDOW(window_enable_data), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window_enable_data), 30);
    gtk_window_set_resizable(GTK_WINDOW(window_enable_data), FALSE);



    GtkWidget * add_button;
    GtkWidget * back_button;

    GtkWidget * label_title;
    GtkWidget * label_email;
    GtkWidget * label_mdp;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

     gtk_container_add(GTK_CONTAINER(window_enable_data), box);


    label_title = gtk_label_new("Titre :");
    gtk_box_pack_start(GTK_BOX(box), label_title, TRUE, FALSE, 0);
    entry_title = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_title, TRUE, FALSE, 0);


    label_email = gtk_label_new("Email / Username :");
    gtk_box_pack_start(GTK_BOX(box), label_email, TRUE, FALSE, 0);

    entry_email = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_email, TRUE, FALSE, 0);

    
    label_mdp = gtk_label_new("Mot de passe :");
    gtk_box_pack_start(GTK_BOX(box), label_mdp, TRUE, FALSE, 0);


    entry_mdp = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_mdp, TRUE, FALSE, 0);


    add_button = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box), add_button, TRUE, FALSE, 0);

    back_button = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);


    unsigned char * fetch_id;
    const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
    fetch_id = fetch_database_data(0,user , pass);

    // int enter = database(5, fetch_id, title, email, mdp);


    int verif_index = 0;


    g_signal_connect_swapped (add_button, "clicked", G_CALLBACK(verification_add_data), window_enable_data);

    printf("%d",verif_index);

    // g_signal_connect(back_button, "clicked", G_CALLBACK(main_clbk), stack);

    /// ***
    // return box;

       gtk_widget_show_all(window_enable_data);

}

void verification_add_data(GtkWidget *w){

    const gchar * title = gtk_entry_get_text(GTK_ENTRY(entry_title));
    const gchar * email = gtk_entry_get_text(GTK_ENTRY(entry_email));
    const gchar * mdp = gtk_entry_get_text(GTK_ENTRY(entry_mdp));

    fflush(stdin);


    int length_email = strlen(email);
    int length_mdp = strlen(mdp);


    if(title[0] != '\0' && email[0] != '\0' && mdp[0] != '\0'){

        if( title[0] != ' ' && email[0] != ' ' && mdp[0] != ' ' ){

            if(length_email > 5 && length_mdp > 5){


        unsigned char * fetch_id;
    const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
    fetch_id = fetch_database_data(0,user , pass);
        int enter2 = database(5, fetch_id, mdp, email, title);
         

        gtk_widget_destroy(w);
        create_hubby(NULL);

                }

               
            }

    }else{
        puts("Error on insertion, + de 6 insertions pour email & mdp");
    }



}

GtkWidget * Register_page(GtkWidget * stack) {
    GtkWidget * box;

    GtkWidget * label_username2;

    GtkWidget * label_password2;

    GtkWidget * register_button;
    GtkWidget * back_button;

    GtkWidget * label_email2;
    GtkWidget * entry_email2;


    /// *** Create the BOX
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);


    // FOR USERNAME 


    label_username2 = gtk_label_new("Username:");
    gtk_box_pack_start(GTK_BOX(box), label_username2, TRUE, FALSE, 0);

    entry_username2 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_username2, TRUE, FALSE, 0);





    // FOR PASSWORD

    label_password2 = gtk_label_new("Password:");
    gtk_box_pack_start(GTK_BOX(box), label_password2, TRUE, FALSE, 0);

    entry_password2 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry_password2, TRUE, FALSE, 0);

    // FOR REGISTER

    register_button = gtk_button_new_with_label("S'inscrire");
    gtk_box_pack_start(GTK_BOX(box), register_button, TRUE, FALSE, 0);

    // FOR RETOUR

    back_button = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);

    /// ***

    g_signal_connect(G_OBJECT(register_button), "clicked", G_CALLBACK(verification_register), stack);
    g_signal_connect(back_button, "clicked", G_CALLBACK(main_clbk), stack);

    /// ***
    return box;
}

void verification_register(GtkButton * button, GtkStack * stack, gpointer data) {

    int enter;
    const gchar * userR = gtk_entry_get_text(GTK_ENTRY(entry_username2));
    const gchar * passR = gtk_entry_get_text(GTK_ENTRY(entry_password2));
    
    enter = database(1, userR, passR, "NULL", "NULL");

    fflush(stdin);


    if (enter == 1) {
        gtk_stack_set_visible_child_full(stack, "CHOICE", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
    } else if (enter == 0) {
        printf("Champ vide ou pas assez long");

    } else if (enter == 3) {
        //Entrer invalide
        printf("Mot de passe incorrecte");

    }
}

void verification_login(GtkButton * button, GtkStack * stack, gpointer data) {


    int enter2;

    const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
    fflush(stdin);
    enter2 = database(2, user, pass, "NULL", "NULL");
    g_print("%d \n", enter2);
    g_print("user : %s \n", user);
    g_print("password :%s \n", pass);

    if (enter2 == 1) {
        gtk_stack_set_visible_child_full(stack, "CHOICE", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
    } else if (enter2 == 0) {
        printf("User/Mot de passe incorrecte");
    }


}

void hubby_clbk(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "HUBBY", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

}

void main_clbk(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "Main", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void login_clbk(GtkButton * button, GtkStack * stack) {



    gtk_stack_set_visible_child_full(stack, "Login", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void register_clbk(GtkButton * button, GtkStack * stack) {


    gtk_stack_set_visible_child_full(stack, "Register", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void choice_clbk(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "CHOICE", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void time_clbk(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "TIME", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

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
                
                sprintf(requete, "select id,pseudo, AES_DECRYPT(password,'clefsecrete') as `password` from User_v2 where pseudo = '%s' AND password = AES_ENCRYPT('%s','clefsecrete');", user, password);
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

                sprintf(requete, "SELECT Id,UserID,email,AES_DECRYPT(mdp, 'clefsecrete') as `mdp` FROM data_huuby_v2 WHERE UserID = '%s'", user);
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
                sprintf(requete, "select id,pseudo, AES_DECRYPT(password,'clefsecrete') as `password` from User_v2 where pseudo = '%s' AND password = AES_ENCRYPT('%s','clefsecrete');", user, password);
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


                sprintf(requete, "INSERT INTO data_huuby_v2(UserID,title,email,mdp)VALUES('%s','%s','%s',AES_ENCRYPT('%s', 'clefsecrete'));", user, website, mail, passwordCrypt[0]);
                mysql_query(mysql, requete);

                mysql_close(mysql);

                // home(user, password);
                break;


            case 5:

                sprintf(requete, "INSERT INTO data_huuby_v2(UserID,title,email,mdp)VALUES('%s','%s','%s',AES_ENCRYPT('%s', 'clefsecrete'));", user, title, email, password);
                mysql_query(mysql, requete);
                mysql_close(mysql);
                return good;

                break;

            case 99:
                printf("Connexion réussi");
        }



    }
}




/* Déclaration des function*/
void databaseT(int proc, char *user, char *password);
int home(char *user, char *password);

/* ---- Connexion ----*/


void connexion (){
    char user[20];
    char password[20];
    int temp;
    unsigned long longueur_USER = 0;
    unsigned long longueur_PWD = 0;
    int i = 0;
    int c = 0;


    printf("--Connexion--\n");
    
    /* Vérification que le user / mot de passe est bien renseigner */
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
        scanf("%d", &temp);
        scanf("%[^\n]",password);
        // Vérification de la longueur
        longueur_PWD = strlen(password);
        if(longueur_PWD > 1){
            c = 1;
            printf("Votre mot de passe est %s\n",password);
        }
    }
    /* Cryptage du mot de passe sous format AAA. */
  //  passwordCryp = crypt(password,"AAA");
    
    /* Appel de la base de donnée, avec 3 arguement */
    databaseT(2, &user[0], &password[0]);
}

/* Fonction inscription, ressemble a connexion */


/* Inscription */


void inscription(){
    char user[20];
    char password[20];
    int temp;
    unsigned long longueur_USER = 0;
    unsigned long longueur_PWD = 0;
    int i = 0;
    int c = 0;


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
        scanf("%d", &temp);
        scanf("%[^\n]",password);
        longueur_PWD = strlen(password);
        if(longueur_PWD > 1){
            c = 1;
            printf("Votre mot de passe est %s\n",password);
        }
    }
    
  //  passwordCryp = crypt(password,"AAA");
    databaseT(1, &user[0], &password[0]);
    
}

/* Fonction qui permet de lier le programme a la base de donnée. Il y a 3 arguement.
 "proc" vas permettre de définir quel requete nous allons executer
 "user / password" Liée a la connexion et a l'inscription de l'utilisateur */

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
                sprintf(requete, "insert into User_v2(pseudo, password) Values('%s', AES_ENCRYPT('%s','clefsecrete'))",user,password);
                mysql_query(mysql, requete);
                home(user, password);
                break;

            case 2: /*Connexion*/
                sprintf(requete, "select id,pseudo, AES_DECRYPT(password,'clefsecrete') as `password` from User_v2 where pseudo = '%s' AND password = AES_ENCRYPT('%s','clefsecrete');",user, password);
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
                                home(user, password);
                            }
                        }
                    
                    
                    
                    
                    }
                break;
            case 3: /*List des mot de passe*/
        
                
                
                

                sprintf(requete, "SELECT Id,UserID,email,AES_DECRYPT(mdp, 'clefsecrete') as `mdp` FROM data_huuby_v2 WHERE UserID = '%s';", fetch_id);
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
                home(user, password);
                
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
                                
                
                sprintf(requete, "INSERT INTO data_huuby_v2(UserID,title,email,mdp)VALUES('%s','%s','%s',AES_ENCRYPT('%s', 'clefsecrete'))",fetch_id , title, email, pword);
                mysql_query(mysql, requete);
            
                home(user, password);
                break;
            case 99:
                printf("Connexion réussi");
                }
    
                
        
        }
}
    
/* Accueil de l'utilisateur une fois connecter */

int home(char *name, char *password){
    int val;
    printf("-- HUBBY --\n");
    printf("Que souhaitez vous faires ? \n1-Voir vos mot de passe \n2-Ajoutez un mot de passe\n");
    scanf("%d", &val);
    switch(val){
        case 1:
            printf("Vos mot de passe\n");
            databaseT(3, name, password);
            break;
        case 2:
            databaseT(4, name, password);
            break;
    }
    return 0;
}

/* Accueil des utilisateur non connecter*/
int terminal(){
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
           databaseT(1, NULL , NULL);
            break;
    return 0;
}



}

int CalculTime();
char ExistingFile();
int threadMain(void * needed);


char ExistingFile(){

  FILE *p;  
  char *MYIDTXT = "./txt/3100.txt";

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
    char *MYIDTXT = "./txt/3100.txt";
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

                p = popen("ps aux | grep firefox | tee ./txt/processes.txt", "r");
                Environnement = "Mozilla";
            }

            if(needed == "gnome-2048"){

                p = popen("ps aux | grep 2048 | tee ./txt/processes2048.txt", "r");
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


int CalculTime(){

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

};

