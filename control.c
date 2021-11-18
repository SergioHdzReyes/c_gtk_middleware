//
// Created by sergio on 12/11/21.
//

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include "utils.h"

GtkWidget *window;
GtkBuilder *builder;
GtkWidget *label;

GtkWidget *fixed;
GtkWidget *btnTop;
GtkWidget *btnRight;
GtkWidget *btnBottom;
GtkWidget *btnLeft;

void startGUI();
void sendCommand(char cmd);
void onWindowDestroy();

int main (int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    startGUI();
    gtk_main();

    return EXIT_SUCCESS;
}

void startGUI()
{
    builder = gtk_builder_new_from_file("control.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "gtk_main_quit", NULL, NULL);
    g_signal_connect(window, "destroy", (GCallback)onWindowDestroy, NULL);
    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));

    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));

    btnTop = GTK_WIDGET(gtk_builder_get_object(builder, "btn-top"));
    btnRight = GTK_WIDGET(gtk_builder_get_object(builder, "btn-right"));
    btnBottom = GTK_WIDGET(gtk_builder_get_object(builder, "btn-bottom"));
    btnLeft = GTK_WIDGET(gtk_builder_get_object(builder, "btn-left"));

    gtk_widget_show(window);
}

void sendCommand(char cmd)
{
    int tcp_sock, r, bytes;
    struct sockaddr_in server_addr;
    char line[1024], ans[1024];
    struct control_struct *datos = malloc(sizeof(struct control_struct));
    *(int *)&datos->key = SCKT_KEY;
    *(char *)&datos->command = cmd;

    // Se crea descriptor de archivo para socket
    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ocurrio un error al crear el socket");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SCKT_PORT);
    g_print("[send_conexions] PUERTO: %d\n", SCKT_PORT);

    // Se intenta conectar a servidor
    if (connect(tcp_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        g_print("Ocurrio un error al conectar");
        return;
    }
    g_print("Conectado al servidor\n");

    ssize_t size = (ssize_t)sizeof(struct control_struct);
    bytes = write(tcp_sock, datos, size);
    g_print("Bytes enviados: %d", bytes);

    // Se cierra Socket
    shutdown (tcp_sock, SHUT_RDWR);
    close(tcp_sock);
}

void onBtnTopClicked() {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-TOP");
    sendCommand(CMD_TOP);
}

void onBtnRightClicked() {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-RIGHT");
    sendCommand(CMD_RIGHT);
}

void onBtnBottomClicked() {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-BOTTOM");
    sendCommand(CMD_BOTTOM);
}

void onBtnLeftClicked() {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-LEFT");
    sendCommand(CMD_LEFT);
}

void onWindowDestroy()
{
    gtk_main_quit();
}