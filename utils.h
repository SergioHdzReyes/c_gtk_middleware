//
// Created by sergio on 13/11/21.
//

#ifndef C_GTK_MIDDLEWARE_UTILS_H
#define C_GTK_MIDDLEWARE_UTILS_H

#define SCKT_KEY 2021
#define SCKT_PORT 3500

#define CMD_TOP     'A'
#define CMD_RIGHT   'B'
#define CMD_BOTTOM  'C'
#define CMD_LEFT    'D'

struct control_struct {
    const int key;
    const char command;
};

#endif //C_GTK_MIDDLEWARE_UTILS_H
