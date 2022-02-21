#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <gtk/gtk.h>

static void
print_about (GtkWidget *widget, gpointer data)
{
        g_print ("\nTrueRand is copyright 2015 Starlight Graphics Design Studio.\nIf you have any questions or comments please contact me at\n\n Website: http://starlightgraphics.tuxfamily.org\n Email: starlightgraphicstudio@gmail.com\n\nThank you.\n");
}

static void
print_cmessage (GtkWidget *widget, gpointer data)
{
        g_print ("\nThank you for using TrueRand. Come again soon!\n");
}

static void
print_rnum (GtkWidget *widget, GtkButton *button, GtkLabel *label, gpointer user_data)
{
        sleep(1);

        /* Generate the random number based on time */
        srand(time(NULL));

        /* Do the complex calculation to get the final random number */
        int tRand = rand() * time(NULL);
        int r1 = rand() % 50049640;
        int r2 = r1 + rand() % 550700360;
        int r3 = r2 - rand() % 5004837 / tRand;
        int r4 = r3 * rand() % 50395008;
        int r5 = r4 - rand() % 570030 * tRand;
        int r6 = r1 * rand() % 67803850;
        int r7 = r3 + rand() % 45789 - tRand;
        int r8 = r6 - rand() % 347;
        int r9 = r5 * rand() % 486790 + tRand;
        int r10 = r8 + rand() % 89490670;
        int r11 = r6 / rand() * r4 + r3;
        int r12 = rand() / r5 + r10 * time(NULL) / rand() * time(NULL) + r7 + r4 + r7 / r3 - r9 - r11 * r10 - tRand;

        sleep(0.5);

        int rn1 = r5 + r8 - r12 * rand() / r7 * r4 - r1 / r6 * r3 * rand() / r12 + r3 * r12 - r8 + time(NULL) * r7;
        int rn2 = r8 + r7 / r7 * r5 - r3 / r2 * r10 * tRand / r11 + r9 * rand() - r12 + time(NULL) * r9;

        /* The final random number */
        int rf = rn1 * tRand + rn2;

        /* Tell the user their random number */
        g_print("\n");
        g_print("Your random number is: %d\n",rf);
        g_print("We garentee that this number is random.\n");
        g_print("If you think it is not, it probally actually is.\n");

        gchar *outputNum;
        outputNum = g_strdup_printf("%d", rf);
        gtk_label_set_text (GTK_LABEL(label), outputNum);
        g_free(outputNum);
}

static void
activate (GtkApplication *app, gpointer user_data)
{
        GtkWidget *window;
        GtkWidget *box;
        GtkWidget *label;
        GtkWidget *button;
        GtkWidget *button_box;

        window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "TrueRand Number Generator");
        gtk_window_set_default_size (GTK_WINDOW (window), 350, 50);

        box = gtk_box_new(TRUE, 25);
        gtk_container_add(GTK_CONTAINER (window), box);
        gtk_widget_show(box);

        label = gtk_label_new("hi");
        gtk_widget_show(label);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 1);

        button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        gtk_container_add (GTK_CONTAINER (box), button_box);

        button = gtk_button_new_with_label ("Generate");
        g_signal_connect (button, "clicked", G_CALLBACK (print_rnum), NULL);
        gtk_container_add (GTK_CONTAINER (button_box), button);

        button = gtk_button_new_with_label ("About");
        g_signal_connect (button, "clicked", G_CALLBACK (print_about), NULL);
        gtk_container_add (GTK_CONTAINER (button_box), button);

        button = gtk_button_new_with_label ("Close");
        g_signal_connect (button, "clicked", G_CALLBACK (print_cmessage), NULL);
        g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
        gtk_container_add (GTK_CONTAINER (button_box), button);

        gtk_widget_show_all (window);
}

int main(int argc,char *argv[])
{
        GtkApplication *app;
        int status;

        app = gtk_application_new ("org.starlightgraphics.truerand", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);

        return status;

        /* Finish the program */
        return 0;
}