#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "server.hpp"


void send(std::string str, int fd);
void send_msg2(int num, User & usr, string msg);
void send_error(int err, User & usr, std::string ctx);


class Channel
{
	private:

		string		_name;
		list<User>	_user;
		list<int>	_operators;
		string		_mode;
	
	public:

		Channel(){
			_mode = "+nt";

		};
		Channel(string name, User & usr): _name(name)
		{
			_user.push_front(usr);
			_operators.push_back(usr.get_fd());
			_mode = "+nt";
		};
		virtual	~Channel(){};

		list<User> get_users() const {
			return _user;
		}

		string		get_name() const {
			return _name;
		}

		list<int>	get_oper() const{
			return _operators;
		}

		string		get_mode() const {
			return _mode;
		}
		
		bool find_user(User & usr)
		{
			list<User>::iterator it = _user.begin();
			while (it != _user.end())
			{
				if (*it == usr)
					return true;
				it++;
			}
			return false;
		}

		bool find_user(string nick)
		{
			list<User>::iterator it = _user.begin();
			while (it != _user.end())
			{
				if ((it->get_nick()) == nick)
					return true;
				it++;
			}
			return false;
		}

		void	add_user(User &usr )
		{
			_user.push_back(usr);
		}

		void	add_oper(User & usr){
			_operators.push_back(usr.get_fd());
		}

		void	rm_oper(User & usr) {
			_operators.remove(usr.get_fd());
		}

		void	add_oper(int fd){
			_operators.push_back(fd);
		}

		void	rm_oper(int fd) {
			_operators.remove(fd);
		}

		bool	is_oper(User & usr) {
			list<int>::iterator it = _operators.begin();
			while (it != _operators.end()) {
				if (*it == usr.get_fd())
					return true;
				it++;
			}
			return false;
		}

		void	del_user(User & usr)
		{
			for (list<int>::iterator it = _operators.begin(); it != _operators.end(); it++)
			{
				if (usr.get_fd() == (*it))
				{
					_operators.erase(it);
					break;
				}
			}
			for (list<User>::iterator it = _user.begin(); it != _user.end(); it++)
			{
				if (usr.get_nick() == (*it).get_nick())
				{

					_user.erase(it);
					break;
				}
			}
		}
};


#endif
