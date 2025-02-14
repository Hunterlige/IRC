#ifndef NICK_CPP
# define NICK_CPP

#include "../include/server.hpp"

void nick(vector<string> *vec, User & usr, Server & srv) {
    string nick = vec->front();
    if (nick == ":")
        vec->erase(vec->begin());
    if (vec->empty() == false && usr.get_real_name() == "") {
        usr.set_nick(nick);
        return;
    }
    if (vec->empty()) {
        send_error(431, usr);
        return;
    }
    if (check_nick(nick) == false) {
        send_error(432, usr, nick);
        return;
    }

    if (nick == usr.get_nick())
        return;

    if (check_nick_availibility(nick, srv) == false) {
        send_error(433, usr, nick);
        return;
    }
    if (usr.is_registred())
        broadcast_update(usr, srv, "NICK", nick);
    usr.set_nick(nick);
    if (!usr.is_registred())
        register_user(usr, srv);
}

void inform_users(User & usr, string cmd, string nick, Server &srv) {
    (void)usr;
    (void)cmd;
    (void)nick;
    (void)srv;
    ;
}

#endif