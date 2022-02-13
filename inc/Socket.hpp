/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:33:33 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/06 17:43:32 by tlucanti         ###   ########.fr       */
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

// delete
#include <iostream>

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
		explicit Socket(int sock, bool nonblock=true) noexcept;
		Socket(const Socket &cpy) : _sock(cpy._sock), _address(cpy._address), _port(cpy._port) {}
		~Socket() noexcept;
		Socket &operator =(const Socket &cpy);

		__WUR Socket accept(bool nonblock=true) const;
		__WUR std::string recv() const;
		void send(const std::string &message) const;
		void close() { std::cout << "closing socket " << std::to_string(_sock) << std::endl; ::close(_sock); _sock = -1; }

		__WUR inline int get_sock() const { return _sock; }
		__WUR inline std::string get_address() const { return _address; }
		__WUR inline uint16_t get_port() const { return _port; }
		static const int READ_SIZE;

		__WUR inline bool operator ==(const Socket &eq) const { return _sock == eq._sock; }
		__WUR inline bool operator !=(const Socket &eq) const { return _sock != eq._sock; }

		static Socket nil;
	private:
		int _sock;
		std::string _address;
		uint16_t _port;

	__DELETED_MEMBERS:
		Socket() __DELETE
	};
}

#endif	// SOCKET_HPP
