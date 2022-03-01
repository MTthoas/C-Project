#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>

char* get_time_string(){
  time_t time_var = time(NULL);
  struct tm *info;
  char *time_string = calloc(100, sizeof(char));
  info = localtime( &time_var );
  strftime(time_string, 100, "%I:%M:%S %p", info);
  return time_string;
}

gboolean update_label_time (gpointer user_data) {
   gchar *t = get_time_string();
   gtk_label_set_text(GTK_LABEL(user_data), t);
   g_free (t);
   return G_SOURCE_CONTINUE;
}

int main (int argc, char *argv[])
{
   gchar *t;
   GtkWidget *window;
   GtkWidget *label_time; 

   gtk_init(&argc, &argv);

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_default_size (GTK_WINDOW(window), 300, 200);
   t = get_time_string();
   label_time = gtk_label_new (t);
   g_free (t);

   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   gtk_container_add (GTK_CONTAINER(window), label_time);


   g_timeout_add_seconds(0.5, update_label_time, label_time);


   gtk_widget_show_all(window);

   gtk_main();

   return 0;
}