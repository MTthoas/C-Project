#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

// #include <gdk/gdk.h>



GtkWidget *create_main     ( GtkWidget *stack );
GtkWidget *create_login_grid    ( GtkWidget *stack );
GtkWidget *create_register_grid ( GtkWidget *stack );

void login_clbk    ( GtkButton *button, GtkStack *stack );
void main_clbk     ( GtkButton *button, GtkStack *stack );
void register_clbk ( GtkButton *button, GtkStack *stack );

void clicked_clbk ( GtkButton *button, GtkStack *stack );
void quit_clbk    ( void );

int main ( void )
{

    system("open http://google.fr");

    
    GtkWidget *window;
    GtkWidget *main;
    GtkWidget *login_grid;
    GtkWidget *register_grid;
    GtkWidget *stack;
    GtkWidget *box;

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

    /// *** Create the Stack Box


    /// *** Create the Box
    box = gtk_box_new ( GTK_ORIENTATION_VERTICAL, 5 );

    /// *** Create a Stack
    stack = gtk_stack_new ();
    gtk_widget_set_halign ( stack, GTK_ALIGN_CENTER );
    gtk_box_set_center_widget ( GTK_BOX ( box ), stack );

    gtk_container_add ( GTK_CONTAINER ( window ), box );

    /// ***
    main     = create_main     ( stack );
    login_grid    = create_login_grid    ( stack );
    register_grid = create_register_grid ( stack );

    /// ***
    gtk_stack_add_named  ( GTK_STACK ( stack ), main,     "Main" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), login_grid,    "Login" );
    gtk_stack_add_named  ( GTK_STACK ( stack ), register_grid, "Register" );

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
    gtk_box_pack_start ( GTK_BOX ( box ), login_button,    0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX ( box ), register_button, 0, 0, 0 );

    /// ***
    g_signal_connect ( login_button,    "clicked", G_CALLBACK ( login_clbk ),    stack );
    g_signal_connect ( register_button, "clicked", G_CALLBACK ( register_clbk ), stack );

    /// *** Return the Box
    return box;
}

GtkWidget *create_login_grid ( GtkWidget *stack )
{
    GtkWidget *grid;
    GtkWidget *login_button;
    GtkWidget *back_button;

    GtkWidget *label_username;
    GtkWidget *entry_username;

    GtkWidget *label_password;
    GtkWidget *entry_password;

    /// *** Create the Grid
    grid = gtk_grid_new();

    /// ***
    label_username = gtk_label_new ( "Username:" );
    label_password = gtk_label_new ( "Password:" );

    /// ***
    entry_username = gtk_entry_new();
    entry_password = gtk_entry_new();

    /// ***
    login_button = gtk_button_new_with_label ( "Login" );
    back_button  = gtk_button_new_with_label ( "Retour" );

    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), label_username, 0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_username, 1, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), label_password, 0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_password, 1, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), back_button,    0, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), login_button,   1, 2, 1, 1 );

    /// ***
    g_signal_connect ( back_button, "clicked", G_CALLBACK ( main_clbk ), stack );

    /// ***
    return grid;
}

GtkWidget *create_register_grid ( GtkWidget *stack )
{
    GtkWidget *grid;
    GtkWidget *register_button;
    GtkWidget *back_button;

    GtkWidget *label_firstName;
    GtkWidget *entry_firstName;

    GtkWidget *label_lastName;
    GtkWidget *entry_lastName;

    GtkWidget *label_password;
    GtkWidget *entry_password;

    GtkWidget *label_street;
    GtkWidget *entry_street;

    GtkWidget *label_number;
    GtkWidget *entry_number;

    GtkWidget *label_email;
    GtkWidget *entry_email;


    /// *** Create the Grid
    grid = gtk_grid_new();

    /// ***
    label_firstName = gtk_label_new ( "First Name:" );
    label_lastName  = gtk_label_new ( "Last Name" );
    label_password  = gtk_label_new ( "Password:" );
    label_street    = gtk_label_new ( "Street:" );
    label_number    = gtk_label_new ( "Number:" );
    label_email     = gtk_label_new ( "Email:" );

    /// ***
    entry_firstName = gtk_entry_new();
    entry_lastName  = gtk_entry_new();
    entry_password  = gtk_entry_new();
    entry_street    = gtk_entry_new();
    entry_number    = gtk_entry_new();
    entry_email     = gtk_entry_new();

    /// ***
    register_button = gtk_button_new_with_label ( "Register" );
    back_button    = gtk_button_new_with_label ( "Retour" );

    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), label_firstName, 0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_firstName, 1, 0, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_lastName,  0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_lastName,  1, 1, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_password,  0, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_password,  1, 2, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_street,    0, 3, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_street,    1, 3, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_number,    0, 4, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_number,    1, 4, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), label_email,     0, 5, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), entry_email,     1, 5, 1, 1 );

    gtk_grid_attach ( GTK_GRID ( grid ), back_button,     0, 6, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), register_button, 1, 6, 1, 1 );

    /// ***
    g_signal_connect ( back_button, "clicked", G_CALLBACK ( main_clbk ), stack );

    /// ***
    return grid;
}

void main_clbk ( GtkButton *button, GtkStack *stack )
{
    g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    g_return_if_fail ( GTK_IS_STACK ( stack ) );

    gtk_stack_set_visible_child_full ( stack, "Main", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
}

void login_clbk ( GtkButton *button, GtkStack *stack )
{
    g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    g_return_if_fail ( GTK_IS_STACK ( stack ) );


    gtk_stack_set_visible_child_full ( stack, "Login", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
}

void register_clbk ( GtkButton *button, GtkStack *stack )
{
    g_return_if_fail ( GTK_IS_BUTTON ( button ) );
    g_return_if_fail ( GTK_IS_STACK ( stack ) );

    gtk_stack_set_visible_child_full ( stack, "Register", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN );
}
