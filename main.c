#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-3.0/gtk/gtk.h>
#include <unistd.h>

GtkWidget *create_main      ( GtkWidget *stack );
GtkWidget *Login_page       ( GtkWidget *stack );
GtkWidget *Register_page    ( GtkWidget *stack );
GtkWidget *create_hubby ( GtkWidget *stack );
GtkWidget *object;

void login_clbk    ( GtkButton *button, GtkStack *stack );
void main_clbk     ( GtkButton *button, GtkStack *stack );
void register_clbk ( GtkButton *button, GtkStack *stack );

void database       (int proc, char *user, char *password);
void clicked_clbk   ( GtkButton *button, GtkStack *stack );
void quit_clbk      ( void );


GtkWidget *entry_username;
GtkWidget *entry_password;

void verification_login(GtkButton *button,GtkStack *stack, gpointer data);


int main ( void )
{
    // system("firefox http://google.fr");

    GtkWidget *window;
    GtkWidget *main;
    GtkWidget *login_grid;
    GtkWidget *register_grid;
    GtkWidget *stack;
    GtkWidget *box;
    GtkWidget *hubby_grid;

    // Initialisation

        gtk_init ( NULL, NULL );

    // CREATION FENETRE

        window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
    
    // TITRE DE LA FENETRE

        gtk_window_set_title ( GTK_WINDOW ( window ), "HUBBY" );
        g_signal_connect ( window, "destroy", gtk_main_quit, window );

    // PARAMETRES DE LA FENETRE 

        gtk_window_set_default_size ( GTK_WINDOW ( window ), 300, 300 );
        gtk_container_set_border_width ( GTK_CONTAINER ( window ), 50 );
        gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    /// *** Create the Box
    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 5 );

    /// *** Create a Stack
    stack = gtk_stack_new ();
    gtk_widget_set_halign ( stack, GTK_ALIGN_CENTER );
    gtk_box_set_center_widget ( GTK_BOX ( box ), stack );

    gtk_container_add ( GTK_CONTAINER ( window ), box );

    /// ***
    main  = create_main  ( stack );
    login_grid    = Login_page  ( stack );
    register_grid = Register_page ( stack );
    hubby_grid = create_hubby ( stack );

    /// **
    gtk_stack_add_named  ( GTK_STACK ( stack ), main,     "Main" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), login_grid,    "Login" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), register_grid, "Register" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), hubby_grid, "HUBBY" );

    /// ***
    gtk_widget_show_all ( window );
    gtk_main ();
}




GtkWidget *create_main ( GtkWidget *stack )
{
    GtkWidget *box;
    GtkWidget *login_button;
    GtkWidget *register_button;
    GtkWidget *close_button;

    /// *** Create the Box
    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 10 );

    /// *** Create the Buttons
    login_button    = gtk_button_new_with_label ( "Login" );
    register_button = gtk_button_new_with_label ( "Register" );

    /// *** Add them to the Box
    gtk_box_pack_start ( GTK_BOX ( box ), login_button,    TRUE, TRUE, 0 );
    gtk_box_pack_start ( GTK_BOX ( box ), register_button, TRUE, TRUE, 0 );

    /// ***
    g_signal_connect ( login_button,    "clicked", G_CALLBACK ( login_clbk ),    stack );
    g_signal_connect ( register_button, "clicked", G_CALLBACK ( register_clbk ), stack );

    /// *** Return the Box
    return box;
}

GtkWidget *Login_page ( GtkWidget *stack )
{
    GtkWidget *box;

    GtkWidget *login_button;
    GtkWidget *back_button;

    GtkWidget *label_username;
    GtkWidget *label_password;


    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 5 );

    
    label_username = gtk_label_new ( "Username:" );
    gtk_box_pack_start(GTK_BOX(box), label_username , TRUE, FALSE, 0);

    entry_username = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),   entry_username , TRUE, FALSE, 0);



    label_password = gtk_label_new ( "Password:" );
    gtk_box_pack_start(GTK_BOX(box),  label_password , TRUE, FALSE, 0);

    entry_password = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),   entry_password  , TRUE, FALSE, 0);

    login_button = gtk_button_new_with_label ( "Login" );
    gtk_box_pack_start(GTK_BOX(box),  login_button , TRUE, FALSE, 0);


    back_button = gtk_button_new_with_label ( "Retour" );
    gtk_box_pack_start(GTK_BOX(box),  back_button , TRUE, FALSE, 0);

    /// ***
    // login_button = gtk_button_new_with_label ( "Login" );
    // back_button  = gtk_button_new_with_label ( "Retour" );

    /// ***

    /// ***




    g_signal_connect (G_OBJECT(login_button), "clicked", G_CALLBACK(verification_login), stack);


    g_signal_connect ( back_button, "clicked", G_CALLBACK ( main_clbk ), stack );

    /// ***
    return box;
}





void verification_login(GtkButton *button, GtkStack *stack, gpointer data){

    const gchar *user = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar *pass = gtk_entry_get_text(GTK_ENTRY(entry_password));

    g_print("%s \n",user);
    g_print("%s \n",pass);

     gtk_stack_set_visible_child_full ( stack, "HUBBY", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
    
 
}





GtkWidget *create_hubby ( GtkWidget *stack ){

    GtkWidget *grid;
    GtkWidget *label_description;
    GtkWidget *box;
    GtkWidget *box2;
    GtkWidget *box3;
    

    GtkWidget *label_three;
    GtkWidget *label_two;
    GtkWidget *label_one;

    GtkWidget *label_one_id;
    GtkWidget *label_one_mdp;

    GtkWidget *label_two_id;
    GtkWidget *label_two_mdp;

    GtkWidget *label_three_id;
    GtkWidget *label_three_mdp;



    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3); 
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);

    label_description = gtk_label_new("GESTIONNAIRE DE MOT DE PASSE");


    label_one = gtk_label_new("Amazon" );
    label_one_id = gtk_label_new("exemple@gmail.com");
    label_one_mdp = gtk_label_new("TryingSome");


    label_two = gtk_label_new("Youtube" );
    label_two_id = gtk_label_new("exemple@gmail.com");
    label_two_mdp = gtk_label_new("TryingSome");

    label_three = gtk_label_new("Youtube" );
    label_three_id = gtk_label_new("exemple@gmail.com");
    label_three_mdp = gtk_label_new("TryingSome");



    // label_three = gtk_label_new("U.GG");

    gtk_box_pack_start(GTK_BOX(box),label_description, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box),box2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box2), box3, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box3), label_one , TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box3), label_one_id , TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box3), label_one_mdp , TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box3), label_two , TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box3), label_two_id , TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box3), label_two_mdp , TRUE, TRUE, 0);

      gtk_box_pack_start(GTK_BOX(box3), label_three , TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box3), label_three_id , TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box3), label_three_mdp , TRUE, TRUE, 0);

     GtkWidget *scrolled_window ;

    
    scrolled_window=gtk_scrolled_window_new(NULL, NULL);



    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window,1, 1);

    gtk_box_pack_start(GTK_BOX(box2), scrolled_window , FALSE, FALSE, 0);

    gtk_widget_show(scrolled_window);
   

    return box;

}





GtkWidget *Register_page ( GtkWidget *stack )
{
    GtkWidget *box;

    GtkWidget *label_username;
    GtkWidget *entry_username;

    GtkWidget *label_password;
    GtkWidget *entry_password;


    GtkWidget *register_button;
    GtkWidget *back_button;

    GtkWidget *label_email;
    GtkWidget *entry_email;


    /// *** Create the BOX
    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 10 );


    // FOR USERNAME 


    label_username = gtk_label_new ( "Username:" );
    gtk_box_pack_start(GTK_BOX(box), label_username , TRUE, FALSE, 0);

    entry_username = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),  entry_username  , TRUE, FALSE, 0);


    // FOR EMAIL

    label_email = gtk_label_new ( "Email:" );
    gtk_box_pack_start(GTK_BOX(box), label_email, TRUE, FALSE, 0);

    entry_email = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),  entry_email  , TRUE, FALSE, 0);


    // FOR PASSWORD

    label_password = gtk_label_new ( "Password:" );
    gtk_box_pack_start(GTK_BOX(box), label_password, TRUE, FALSE, 0);

    entry_password = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),  entry_password , TRUE, FALSE, 0);

    // FOR LOGIN

    register_button = gtk_button_new_with_label ( "S'inscrire" );
    gtk_box_pack_start(GTK_BOX(box),  register_button , TRUE, FALSE, 0);

    // FOR RETOUR

    back_button = gtk_button_new_with_label ( "Retour" );
    gtk_box_pack_start(GTK_BOX(box),  back_button , TRUE, FALSE, 0);





    /// ***
    g_signal_connect ( back_button, "clicked", G_CALLBACK ( main_clbk ), stack );

    /// ***
    return box;
}


void main_clbk ( GtkButton *button, GtkStack *stack )
{

    gtk_stack_set_visible_child_full ( stack, "Main", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
}

void login_clbk ( GtkButton *button, GtkStack *stack )
{
    // g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    // g_return_if_fail ( GTK_IS_STACK ( stack ) );


    gtk_stack_set_visible_child_full ( stack, "Login", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
}

void register_clbk ( GtkButton *button, GtkStack *stack )
{
    // g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    // g_return_if_fail ( GTK_IS_STACK ( stack ) );

    gtk_stack_set_visible_child_full ( stack, "Register", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
}
