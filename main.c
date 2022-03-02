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



void * create_main(GtkWidget * stack);
GtkWidget * Login_page(GtkWidget * stack);
GtkWidget * Register_page(GtkWidget * stack);
void create_hubby(GtkWidget * stack);
GtkWidget * choice_menu(GtkWidget * stack);
GtkWidget * time_menu(GtkWidget * stack);
void start_box_transition(GtkWidget * w);
static gboolean label_update(gpointer data);
void time_application_quit();
void quit_time_app_transition(GtkWidget * w);
void start_box_del(GtkWidget *w);
void start_box_delete();
void del_sys();



int block_variable = 0;
static int sec_expired = 0;

GtkWidget * object;

GtkWidget * window_hubby;
GtkWidget * window_app_time;
GtkWidget * window_enable_data;

void verification_add_data(GtkWidget * w);
void start_box(void);
void create_time_app();

int terminal();

GtkWidget * entry_username;
GtkWidget * entry_password;

GtkWidget * entry_username2;
GtkWidget * entry_password2;

GtkWidget * entry_title;
GtkWidget * entry_email;
GtkWidget * entry_mdp;

  GtkWidget * del_entry_title;

static gboolean continue_timer = FALSE;
static gboolean start_timer = FALSE;


void verification_login(GtkButton * button, GtkStack * stack, gpointer data);
void verification_register(GtkButton * button, GtkStack * stack, gpointer data);

static GtkWidget * pLabel;


int ConfigSetup() {


    FILE * f = NULL;

    f = fopen("config.txt", "r");
    int tab[3];
    char str1[3] = "", str2[3] = "", str3[3] = "", str4[3] = "";
    if (f != NULL) {
        fscanf(f, "%s %s", str1, str2);
        tab[1] = atoi(str2);
        tab[2] = atoi(str4);

        fclose(f);

    } else {
        printf("Impossible de lire le fichier");
    }

    if (tab[1] == 1) {
        g_print("test");
        return 0;
    } else if (tab[1] == 0) {
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

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
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
    // gtk_stack_add_named(GTK_STACK(stack), time_grid, "TIME");

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
    g_signal_connect(login_button, "clicked", G_CALLBACK(login_transition), stack);
    g_signal_connect(register_button, "clicked", G_CALLBACK(register_transition), stack);

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


    g_signal_connect(back_button, "clicked", G_CALLBACK(main_transition), stack);

    /// ***
    return box;
}

GtkWidget * choice_menu(GtkWidget * stack) {


    static GtkWidget * window;

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

    g_signal_connect(back_button, "clicked", G_CALLBACK(main_transition), stack);


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

    g_signal_connect(back_button, "clicked", G_CALLBACK(choice_transition), stack);


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
    GtkWidget * delete_button;
    // GtkWidget * start_link_transition;

    char tempo[20];
    GtkWidget * label_id[20];
    GtkWidget * label_title[50];
    GtkWidget * label_email[50];
    GtkWidget * label_mdp[50];
    GtkWidget * Separator[50];
    GtkWidget * label_state[50];
    GtkWidget * label_title_gchar[50];
    

    unsigned int mysql_result_nb = 0;


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
        gtk_window_set_default_size(GTK_WINDOW(window_hubby), 300, 800);
        gtk_container_set_border_width(GTK_CONTAINER(window_hubby), 30);
        gtk_window_set_resizable(GTK_WINDOW(window_hubby), FALSE);


        box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

        gtk_container_add(GTK_CONTAINER(window_hubby), box);

        label_description = gtk_label_new("GESTIONNAIRE DE MOT DE PASSE");



        unsigned char * fetch_id;
        const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
        const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
        fetch_id = fetch_database_data(0, user, pass);

       sprintf(requete, "select Id,UserID,title,email, AES_DECRYPT(mdp, 'clefsecrete') as `mdp` from data_hubby WHERE UserID = '%s'", fetch_id);
        mysql_query(mysql, requete);
        result = mysql_use_result(mysql);

        mysql_result_nb = mysql_num_fields(result);

        while ((row = mysql_fetch_row(result))) {

            unsigned long * lengths;

            lengths = mysql_fetch_lengths(result);


            for (int i = 0; i < mysql_result_nb; i++) {

                Separator[index] = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

                label_title[index] = gtk_button_new_with_label(row[2]);



                if (i == 1) {

                    int checking_curl = fonction_curl(row[2]);

                    if (checking_curl == 1) {
                        label_state[index] = gtk_label_new("Site ON");

                    } else {

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

            g_signal_connect(G_OBJECT(label_title[index]), "clicked", G_CALLBACK(start_link_transition), label_title[index]);
            // g_signal_connect_swapped (G_OBJECT(label_title[index]), "clicked", G_CALLBACK(quit_time_app_transition), window_hubby);


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

        delete_button = gtk_button_new_with_label("Supprimer");
        gtk_box_pack_start(GTK_BOX(box),delete_button, TRUE, FALSE, 0);

        g_signal_connect_swapped(add_button, "clicked", G_CALLBACK(start_box_transition), window_hubby);
        g_signal_connect_swapped (delete_button, "clicked", G_CALLBACK(start_box_del), window_hubby);

        // back_button = gtk_button_new_with_label ( "Retour" );
        // gtk_box_pack_start(GTK_BOX(box),  back_button , TRUE, FALSE, 0);

        // g_signal_connect ( back_button, "clicked", G_CALLBACK ( choice_transition ), stack );


        gtk_widget_show_all(window_hubby);


    }
}


void quit_time_app_transition(GtkWidget * w) {

    gtk_widget_destroy(w);
    puts("HAS LEAVE");
    continue_timer = FALSE;
}


static gboolean label_update(gpointer data) {


    unsigned char * fetch_id;
    char * qq;
    FILE * p;
    char ligne[1024];
    char data_index[1024];
    double time_diff_mozilla;
    double time_diff_game;
    double time_diff;
    int index = 0;
    int i;
    bool block = false;
    bool block_time = false;
    int index_time = 0;
    char * MYIDTXT = "./txt/3100.txt";
    char * Environnement;
    void * needed = "/usr/lib/firefox-esr/firefox-esr";

    bool app_detected;
    bool start_chrono = true;

    int has_MOZILLA = 0, has_VSCODE = 0;

    bool exist_file_for_this_id;

    double data_from_mozilla;
    double data_from_game;

    time_t debut;
    time_t end;

    GtkLabel * label = (GtkLabel * ) data;
    char buf[256];
    memset( & buf, 0x0, 256);
    snprintf(buf, 255, "Mozilla: %d seconde(s)", ++sec_expired);
    gtk_label_set_label(label, buf);


    if (block_variable == 0) {

        unsigned char * fetch_id;
        const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
        const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
        fetch_id = fetch_database_data(0, user, pass);

        const char * q1 = "./txt/";
        const char * q3 = ".txt";

        char * MYIDTXT = (char * ) malloc((strlen(q1) + strlen(fetch_id) + strlen(q3)) * sizeof(char));
        strcpy(MYIDTXT, q1);
        strcpy(MYIDTXT, fetch_id);
        strcat(MYIDTXT, q3);

        printf("%s\n", qq);


        if (access(MYIDTXT, F_OK) != -1) {

        } else {

            p = fopen(MYIDTXT, "w");

            fprintf(p, "MOZILLA : Durée = 0\n");

            fclose(p);

        }

    }

    block_variable++;

    p = popen("ps aux | grep firefox | tee ./txt/processes.txt", "r");

    if (!p) {
        exit(-1);
    }

    fgets(ligne, sizeof(ligne), p);

    index++;

    printf("%s", ligne);


    if (strstr(ligne, needed) != NULL) {

        // L'application a été detecte

        // On démarre le chronomètre une seule fois et on informe au système que l'app a été detecté

        if (start_chrono == true) {

            debut = time(NULL);
            printf("yes\n");
            app_detected = true;

        }

        start_chrono = false;


    } else {

        // On sait que l'appli a été fermé et que l'app a été detecté
        // Donc on affiche le temps d'utilisation


        if (app_detected == true) {

            end = time(NULL);

            time_diff = difftime(end, debut);

            // Récupération d'anciennes données

            p = fopen(MYIDTXT, "r");

            fgets(data_index, sizeof data_index, p);

            sscanf(data_index, "MOZILLA : Durée = %lf\n", & data_from_mozilla);


            fclose(p);

            p = fopen(MYIDTXT, "w");

            if (Environnement == "Mozilla") {

                double time_calculate = time_diff + data_from_mozilla;
                fprintf(p, "Mozilla : Durée = %lf \n", time_calculate);

                gchar * display;

                display = g_strdup_printf("%lf", time_calculate);
                gtk_label_set_text(label, display);
                g_free(display);

            }



            fclose(p);
            printf("\n");


            app_detected = false;


        }


    };

}

void start_box_del(GtkWidget *w){

    gtk_widget_destroy(w);
    start_box_delete();
}

void start_box_delete(){

    GtkWidget * box;
    

    window_enable_data = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // TITRE DE LA FENETRE

    gtk_window_set_title(GTK_WINDOW(window_enable_data), "HUBBY");

    // PARAMETRES DE LA FENETRE 

    gtk_window_set_default_size(GTK_WINDOW(window_enable_data), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window_enable_data), 30);
    gtk_window_set_resizable(GTK_WINDOW(window_enable_data), FALSE);


    GtkWidget * del_button;
    GtkWidget * label_title;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

gtk_container_add(GTK_CONTAINER(window_enable_data), box);

    label_title = gtk_label_new("Titre :");
    gtk_box_pack_start(GTK_BOX(box), label_title, TRUE, FALSE, 0);

    del_entry_title = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), del_entry_title, TRUE, FALSE, 0);


    del_button = gtk_button_new_with_label("Supprimer");
    gtk_box_pack_start(GTK_BOX(box), del_button, TRUE, FALSE, 0);

    
    
    unsigned char * fetch_id;


    g_signal_connect_swapped (del_button, "clicked", G_CALLBACK(del_sys), window_enable_data);
    gtk_widget_show_all(window_enable_data);
}

void del_sys(){
    unsigned char * fetch_id;
    const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
    const gchar * title =  gtk_entry_get_text(GTK_ENTRY(del_entry_title ));
    fetch_id = fetch_database_data(0,user , pass);
    int verif = database(6, fetch_id, NULL, NULL, title);
    if(verif == 1 ){
        g_print("Bien supprimer");
    }
}

void create_time_app() {

    GtkWidget * box;
    GtkWidget * box2;

    GtkWidget * label_description;
    GtkWidget * Firefox;
    GtkWidget * back_button;
    GtkWidget * label;

    window_app_time = gtk_window_new(GTK_WINDOW_TOPLEVEL);;


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
    label = gtk_label_new("Mozilla :");


    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);



    GtkWidget * scrolled_window;

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);


    gtk_container_add(GTK_CONTAINER(scrolled_window), box2);

    back_button = gtk_button_new_with_label("Quitter");
    gtk_box_pack_start(GTK_BOX(box), back_button, TRUE, FALSE, 0);

    // g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer) window);

    gtk_widget_show_all(window_app_time);
    g_signal_connect_swapped(back_button, "clicked", G_CALLBACK(quit_time_app_transition), window_app_time);
    g_signal_connect(window_app_time, "destroy", G_CALLBACK(quit_time_app_transition), window_app_time);


    g_timeout_add_seconds(1, label_update, label);
    start_timer = TRUE;
    continue_timer = TRUE;

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
    fetch_id = fetch_database_data(0, user, pass);

    // int enter = database(5, fetch_id, title, email, mdp);


    int verif_index = 0;


    g_signal_connect_swapped(add_button, "clicked", G_CALLBACK(verification_add_data), window_enable_data);

    printf("%d", verif_index);

    // g_signal_connect(back_button, "clicked", G_CALLBACK(main_transition), stack);

    /// ***
    // return box;

    gtk_widget_show_all(window_enable_data);

}

void start_box_transition(GtkWidget * w) {

    gtk_widget_destroy(w);
    start_box();
}


void verification_add_data(GtkWidget * w) {

    const gchar * title = gtk_entry_get_text(GTK_ENTRY(entry_title));
    const gchar * email = gtk_entry_get_text(GTK_ENTRY(entry_email));
    const gchar * mdp = gtk_entry_get_text(GTK_ENTRY(entry_mdp));

    fflush(stdin);


    int length_email = strlen(email);
    int length_mdp = strlen(mdp);


    if (title[0] != '\0' && email[0] != '\0' && mdp[0] != '\0') {

        if (title[0] != ' ' && email[0] != ' ' && mdp[0] != ' ') {

            if (length_email > 5 && length_mdp > 5) {


                unsigned char * fetch_id;
                const gchar * user = gtk_entry_get_text(GTK_ENTRY(entry_username));
                const gchar * pass = gtk_entry_get_text(GTK_ENTRY(entry_password));
                fetch_id = fetch_database_data(0, user, pass);
                int enter2 = database(5, fetch_id, mdp, email, title);


                gtk_widget_destroy(w);
                create_hubby(NULL);

            }


        }

    } else {
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
    g_signal_connect(back_button, "clicked", G_CALLBACK(main_transition), stack);

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


void connexion() {

    char user[20];
    char password[20];
    int temp;
    unsigned long longueur_USER = 0;
    unsigned long longueur_PWD = 0;
    int i = 0;
    int c = 0;


    printf("--Connexion--\n");

    /* Vérification que le user / mot de passe est bien renseigner */
    while (i < 1) {
        fflush(stdin);
        printf("Veuillez renseignez votre utilisateur\n");
        scanf("%d", & temp);
        scanf("%[^\n]", user);

        longueur_USER = strlen(user);
        if (longueur_USER > 1) {
            i = 1;
            printf("Votre nom d'utilisateur est %s\n", user);
        }
    }

    while (c < 1) {
        fflush(stdin);
        printf("Veuillez renseignez votre mot de passe\n");
        scanf("%d", & temp);
        scanf("%[^\n]", password);
        // Vérification de la longueur
        longueur_PWD = strlen(password);
        if (longueur_PWD > 1) {
            c = 1;
            printf("Votre mot de passe est %s\n", password);
        }
    }
    /* Cryptage du mot de passe sous format AAA. */
    //  passwordCryp = crypt(password,"AAA");

    /* Appel de la base de donnée, avec 3 arguement */
    databaseT(2, & user[0], & password[0]);
}

/* Fonction inscription, ressemble a connexion */


/* Inscription */


void inscription() {
    char user[20];
    char password[20];
    int temp;
    unsigned long longueur_USER = 0;
    unsigned long longueur_PWD = 0;
    int i = 0;
    int c = 0;


    while (i < 1) {
        fflush(stdin);
        printf("Veuillez renseignez votre utilisateur\n");
        scanf("%d", & temp);
        scanf("%[^\n]", user);

        longueur_USER = strlen(user);
        if (longueur_USER > 1) {
            i = 1;
            printf("Votre nom d'utilisateur est %s\n", user);
        }
    }

    while (c < 1) {
        fflush(stdin);
        printf("Veuillez renseignez votre mot de passe\n");
        scanf("%d", & temp);
        scanf("%[^\n]", password);
        longueur_PWD = strlen(password);
        if (longueur_PWD > 1) {
            c = 1;
            printf("Votre mot de passe est %s\n", password);
        }
    }

    //  passwordCryp = crypt(password,"AAA");
    databaseT(1, & user[0], & password[0]);

}

/* Fonction qui permet de lier le programme a la base de donnée. Il y a 3 arguement.
 "proc" vas permettre de définir quel requete nous allons executer
 "user / password" Liée a la connexion et a l'inscription de l'utilisateur */

/* Accueil de l'utilisateur une fois connecter */

int home(char * name, char * password) {
    int val;
    printf("-- HUBBY --\n");
    printf("Que souhaitez vous faires ? \n1-Voir vos mot de passe \n2-Ajoutez un mot de passe\n");
    scanf("%d", & val);
    switch (val) {
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
int terminal() {
    int val;
    printf("-- Accueil --\n");
    printf("1- Inscription\n2- Connexion\n3- Ping Database\n");
    scanf("%d", & val);
    switch (val) {
        case 1:
            inscription();
            break;
        case 2:
            connexion();
            break;

        case 3:
            databaseT(1, NULL, NULL);
            break;
            return 0;
    }



}