//
// Created by sergio on 12/11/21.
//

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkBuilder *builder;
GtkLabel *label;

GtkWidget *fixed;
GtkWidget *btnTop;
GtkWidget *btnRight;
GtkWidget *btnBottom;
GtkWidget *btnLeft;

int main (int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("control.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "gtk_main_quit", NULL, NULL);
    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));

    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));

    btnTop = GTK_WIDGET(gtk_builder_get_object(builder, "btn-top"));
    btnRight = GTK_WIDGET(gtk_builder_get_object(builder, "btn-right"));
    btnBottom = GTK_WIDGET(gtk_builder_get_object(builder, "btn-bottom"));
    btnLeft = GTK_WIDGET(gtk_builder_get_object(builder, "btn-left"));

    gtk_widget_show(window);
    gtk_main();

    return EXIT_SUCCESS;
}

void on_btn_top_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-TOP");
}

void on_btn_right_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-RIGHT");
}

void on_btn_bottom_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-BOTTOM");
}

void on_btn_left_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-LEFT");
}