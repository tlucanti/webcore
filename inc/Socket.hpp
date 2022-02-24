/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:33:33 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:18:56 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cerrno>
# include <cstring>
# include <unistd.h>
# include <fcntl.h>

# ifdef __DEBUG
#  include <iostream>
# endif /* __DEBUG */

# include "defs.h"
# include "SocketException.hpp"


namespace tlucanti
{
	class Socket
	{
	public:
		Socket(const std::string &address, uint16_t port, bool nonblock);
		explicit Socket(int sock, bool nonblock=true) noexcept;
		Socket(const Socket &cpy)
				: _sock(cpy._sock), _address(cpy._address), _port(cpy._port) {}
		~Socket() noexcept __DEFAULT
		Socket &operator =(const Socket &cpy);

		__WUR Socket accept(bool nonblock=true) const;
		__WUR std::string recv() const;
		void send(const std::string &message) const;
		void close();

		__WUR inline int get_sock() const { return _sock; }
		__WUR inline std::string get_address() const { return _address; }
		__WUR inline uint16_t get_port() const { return _port; }
		static const int READ_SIZE;

		__WUR inline bool operator ==(const Socket &eq) const
		{ return _sock == eq._sock; }
		__WUR inline bool operator !=(const Socket &eq) const
		{ return _sock != eq._sock; }
		__WUR inline bool operator <(const Socket &cmp) const
		{ return  _sock < cmp._sock; }

		static Socket nil;
	private:
		int _sock;
		std::string _address;
		uint16_t _port;

	__DELETED_MEMBERS:
		Socket() __DELETE
	};
}

#endif /* SOCKET_HPP */
