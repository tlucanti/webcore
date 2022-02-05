/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:58:05 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/05 14:20:38 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <string>
#include <vector>
#include <sys/poll.h>

#include "ServerException.hpp"
#include "Socket.hpp"
#include "defs.h"

namespace tlucanti
{
	class Server
	{
	public:
		typedef std::vector<struct pollfd> container;

		Server(const std::string &address, uint16_t port);
		~Server() noexcept;

		__WUR Socket accept();
		__WUR Socket poll();
		void add_client(Socket &new_cli);

		static const int WAIT_TIME;
	private:
		container poll_data;
		Socket sock;

		// Server::poll variables
		int _polls_unprocessed;
		int _last_processed_poll;
	};

	__NORET void server_start(Server &server);
}

#endif /* SERVER_HPP */
