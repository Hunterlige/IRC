#ifndef JOIN_CPP
# define JOIN_CPP

#include "../include/server.hpp"

void	join(vector<string> *vec, User & usr, Server & srv)
{
	if (vec->size() == 0)
	{
		send_error(461, usr); //:ergo.test 461 fg JOIN :Not enough parameters
		return;
	}
	map<string, Channel>::iterator it = srv.get_begin_channel();
	while(it != srv.get_end_channel())
	{
		if ((vec->front()).compare((*it).first) == 0)
		{
			if (usr.find_channel(vec->front()) == false || srv.find_chan_user(usr, (*it).second) == false)
			{
				string chanName = vec->front();
				Channel chan = srv.get_channel_by_name(chanName);
				usr.add_channel(chanName);
				srv.add_user_channel(usr, chanName);
				send_general_update(usr, srv, chan, "JOIN", chanName, false);
				welcome_chan(usr, srv, chan);
			}
			return;
		}
		it++;
	}
	if (it == srv.get_end_channel())
	{
		Channel chan(vec->front(), usr);
		usr.add_channel(vec->front());
		srv.add_channel(chan);
		send_general_update(usr, srv, chan, "JOIN", chan.get_name(), false);
		welcome_chan(usr, srv, chan);
	}
}

void	welcome_chan(User & usr, Server srv, Channel & chan)
{
	(void) srv;
	string msg = "= ";
	msg += chan.get_name();
	msg += " :";
	list<User> userList = chan.get_users();
	list<int> operList = chan.get_oper();
	for (list<User>::iterator uit = userList.begin(); uit != userList.end(); uit++)
	{
		for(list<int>::iterator fdit = operList.begin(); fdit != operList.end(); fdit++)
			if ((*fdit) == (*uit).get_fd())
				msg += "@";
		msg += (*uit).get_nick();
		if (++uit != userList.end())
			msg += " ";
		uit--;
	}
	send_msg2(353, usr, msg);
	send_error(366, usr, chan.get_name());
}


#endif



/*
- dans join lorsque le user join le channel la lsite le nom du chan s'affiche et des gens dedans s'affiche et les operator avec un @

*/