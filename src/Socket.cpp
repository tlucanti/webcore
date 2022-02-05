/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:48:49 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/03 16:03:24 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

tlucanti::Socket tlucanti::Socket::nil = tlucanti::Socket(-1, false);

tlucanti::Socket::Socket(const std::string &address, uint16_t port, bool nonblock)
{
	struct sockaddr_in _addr = {};

	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (_sock == -1)
		throw SocketException("cannot create socket", errno);
	if (nonblock)
		fcntl(_sock, F_SETFL, O_NONBLOCK);
	if (inet_pton(AF_INET, address.c_str(), &_addr.sin_addr) <= 0)
		throw SocketException("invalid socket address", errno);
	_addr.sin_port = htons(port);
	if (bind(_sock, reinterpret_cast<const sockaddr *>(&_addr), sizeof(_addr)))
		throw SocketException("cannot bind address", errno);
	if (listen(_sock, 20))
		throw SocketException("cannot listen port", errno);
}

#include <iostream>
tlucanti::Socket::~Socket() noexcept
{
//	std::cout << "closed " << _sock << "\n";
//	close(_sock);
}

tlucanti::Socket::Socket(int sock, bool nonblock) noexcept
		: _sock(sock)
{
	if (nonblock)
		fcntl(_sock, F_SETFL, O_NONBLOCK);
}

tlucanti::Socket &
tlucanti::Socket::operator =(const Socket &cpy)
{
	_sock = cpy._sock;
	return *this;
}
