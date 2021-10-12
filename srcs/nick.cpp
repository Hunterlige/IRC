#ifndef NICK_CPP
# define NICK_CPP

#include "../include/server.hpp"

void nick(vector<string> *vec, User & usr, Server & srv) {
    (void) srv;
    if (vec->front() == ":")
        vec->erase(vec->begin());
    if (vec->empty() == false && usr.getRealName() == "") {
        usr.set_nick(vec->front());
        return;
    }
    if (vec->empty()) {
        send_error(431, usr);
        return;
    }
    if (check_nick(vec->front()) == false) {
        send_error(432, usr, vec->front());
        return;
    }
    if (usr.isRegistred())
        send_update(usr, "NICK", vec->front());
    usr.set_nick(vec->front());
    if (!usr.isRegistred())
        registerUser(usr);
}

#endif