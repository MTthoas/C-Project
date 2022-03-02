#include <stdio.h>

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

#include "transition.h"


void start_link_transition(GtkButton * button){

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

void quit_time_app_transition(GtkWidget *w){

     gtk_widget_destroy(w);

}

void hubby_transition(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "HUBBY", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

}

void main_transition(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "Main", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void login_transition(GtkButton * button, GtkStack * stack) {



    gtk_stack_set_visible_child_full(stack, "Login", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void register_transition(GtkButton * button, GtkStack * stack) {


    gtk_stack_set_visible_child_full(stack, "Register", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void choice_transition(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "CHOICE", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
}

void time_transition(GtkButton * button, GtkStack * stack) {

    gtk_stack_set_visible_child_full(stack, "TIME", GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

}















































