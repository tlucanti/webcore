/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:34:11 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:23:24 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

tlucanti::Server::Server(const std::string &address, uint16_t port) :
	sock(address, port, true)
	, _polls_unprocessed(0)
	, _last_processed_poll(-1)
	{}

tlucanti::Server::~Server() noexcept
{
	sock.close();
	container::iterator it = poll_data.begin();
	for (; it != poll_data.end(); ++it)
	{
#ifdef __DEBUG
		std::cout << "closing socket " << it->fd << std::endl;
#endif /* __DEBUG */

		close(it->fd);
	}
}

__WUR tlucanti::Socket
tlucanti::Server::accept()
{
	return sock.accept();
}

__WUR tlucanti::Socket
tlucanti::Server::poll()
{
	if (_polls_unprocessed == 0)
	/*
		if all clients were processed - call ::poll again and return first
		client with event
		else - continue from next client with event
 	*/
	{
		_polls_unprocessed = ::poll(poll_data.data(), poll_data.size(), WAIT_TIME);
		if (_polls_unprocessed < 0)
			throw ServerException("poll error", errno);
		else if (_polls_unprocessed == 0)
		{
			_last_processed_poll = -1;
			return Socket::nil;
		}
	}
	for (int cli=_last_processed_poll + 1; cli < (int)poll_data.size(); ++cli)
	{
		if (poll_data.at(cli).revents & POLLIN)
		{
			poll_data[cli].revents = 0;	// don't need .at because already
										//checked
			--_polls_unprocessed;
			return Socket(poll_data[cli].fd, true);
		}
	}
	_polls_unprocessed = 0;
	_last_processed_poll = -1;
	return Socket::nil;
}

void
tlucanti::Server::add_client(Socket &new_cli)
{
	struct pollfd new_struct = {};
	new_struct.fd = new_cli.get_sock();
	new_struct.events = POLLIN;
	new_struct.revents = 0;
	poll_data.push_back(new_struct);
}
