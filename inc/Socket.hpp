/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:33:33 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/03 16:02:55 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#include "defs.h"
#include "SocketException.hpp"

#ifndef SOCKET_HPP
# define SOCKET_HPP

namespace tlucanti
{
	class Socket
	{
	public:
		Socket(const std::string &address, uint16_t port, bool nonblock);
		Socket(int sock, bool nonblock) noexcept;
		~Socket() noexcept;
		Socket &operator =(const Socket &cpy);

		__WUR inline int get_sock() const { return _sock; }
		static const int READ_SIZE;

		__WUR inline bool operator ==(const Socket &eq) const { return _sock == eq._sock; }
		__WUR inline bool operator !=(const Socket &eq) const { return _sock != eq._sock; }

		static Socket nil;
	private:
		int _sock;
	};

	__WUR Socket accept(const Socket &_sock, bool nonblock);
	__WUR std::string recv(const Socket &_sock);
}

#endif	// SOCKET_HPP
