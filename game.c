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
GtkWidget *fixed;

GtkWidget *img1;
GtkWidget *img2;
GtkWidget *img3;

void startGUI();
void startServer();
void onWindowDestroy();
void processCommand(struct control_struct*);

void moveTop();
void moveRight();
void moveBottom();
void moveLeft();

int main (int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    g_thread_new(NULL, (GThreadFunc)startServer, NULL);

    startGUI();
    gtk_main();

    return EXIT_SUCCESS;
}

void startGUI()
{
    builder = gtk_builder_new_from_file("game.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "gtk_main_quit", NULL, NULL);
    g_signal_connect(window, "destroy", (GCallback)onWindowDestroy, NULL);
    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));

    img1 = GTK_WIDGET(gtk_builder_get_object(builder, "img1"));
    gtk_widget_show(img1);

    gtk_widget_show(window);
}

void startServer()
{
    g_print("Entrando en hilo de servidor...\n");

    int tcp_sock, aux = 0;
    char line[1024];
    struct sockaddr_in server_addr, client_addr;
    struct control_struct *ctrlData2 = NULL;

    // Se crea descriptor de archivo para socket
    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        g_print("Ocurrio un error al crear socket");

    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SCKT_PORT);

    // Se enlaza socket con direccion y puerto
    if (bind(tcp_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Ocurrio un eror en bind( )");
        exit(0);
    }

    // Se prepara para escuchar conexiones
    listen(tcp_sock, 5);

    int con_sock;
    socklen_t len;
    ssize_t n;

    while (1) {
        aux++;
        len = sizeof(client_addr);
        // Se acepta nueva conexion
        con_sock = accept(tcp_sock, (struct sockaddr*) &client_addr, &len);

        if (con_sock < 0) {
            perror("Ocurrio un error al aceptar comunicacion");
            exit(0);
        }

        while (1) {
            // Se recibe informacion desde socket, limitado a MAX_CHAR bytes
            n = read(con_sock, line, sizeof(struct control_struct));
            if (n == 0){
                printf("servidor: cliente termino de enviar\n");
                close(con_sock);
                break;
            }

            ctrlData2 = (struct control_struct *)&line;
            g_print("CLAVE: %d\n", ctrlData2->key);
            g_print("COMANDO: %c\n", ctrlData2->command);

            processCommand(ctrlData2);
        }
    }

    g_print("Saliendo de hilo de servidor...\n");
}

void processCommand(struct control_struct *cmd)
{
    if (cmd->key == SCKT_KEY) {
        switch (cmd->command) {
            case CMD_TOP:
                moveTop();
                break;
            case CMD_RIGHT:
                moveRight();
                break;
            case CMD_BOTTOM:
                moveBottom();
                break;
            case CMD_LEFT:
                moveLeft();
                break;
        }
    }
}

void moveTop() {
    //gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-TOP");
}

void moveRight() {
    //gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-RIGHT");
}

void moveBottom() {
    //gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-BOTTOM");
}

void moveLeft() {
    //gtk_label_set_text(GTK_LABEL(label), (const gchar*) "BTN-LEFT");
}

void onWindowDestroy()
{
    gtk_main_quit();
}