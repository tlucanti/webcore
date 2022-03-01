/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:48:49 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:20:31 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"

tlucanti::Socket tlucanti::Socket::nil = tlucanti::Socket(-1, false);

tlucanti::Socket::Socket(const std::string &address, uint16_t port, bool nonblock)
{
	struct sockaddr_in _addr = {};

	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (_sock == -1)
		throw SocketException("cannot create socket", errno);
	if (nonblock)
		fcntl(_sock, F_SETFL, O_NONBLOCK);
	int yes = 1;
	setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if (inet_pton(AF_INET, address.c_str(), &_addr.sin_addr) <= 0)
		throw SocketException("invalid socket address", errno);
	_addr.sin_port = htons(port);
	if (bind(_sock, reinterpret_cast<const sockaddr *>(&_addr), sizeof(_addr)))
		throw SocketException("cannot bind address", errno);
	if (listen(_sock, 20))
		throw SocketException("cannot listen port", errno);
	_address = address;
	_port = port;
}

tlucanti::Socket::Socket(int sock, bool nonblock) noexcept
		: _sock(sock)
{
	char ip_str[INET_ADDRSTRLEN];
	struct sockaddr_storage addr = {};
	socklen_t len = sizeof addr;
	getpeername(_sock, reinterpret_cast<sockaddr *>(&addr), &len);
	sockaddr_in *struct_in = reinterpret_cast<sockaddr_in *>(&addr);
	_port = struct_in->sin_port;
	inet_ntop(AF_INET, &struct_in->sin_addr, ip_str, sizeof ip_str);
	_address.assign(ip_str);

	if (nonblock)
		fcntl(_sock, F_SETFL, O_NONBLOCK);
}

__WUR tlucanti::Socket
tlucanti::Socket::accept(bool nonblock) const
{
	int int_sock = ::accept(_sock, nullptr, nullptr);
	if (int_sock < 0)
	{
		if (errno == EWOULDBLOCK)
			return Socket::nil;
		else
			throw SocketException("cannot accept socket", errno);
	}
	return Socket(int_sock, nonblock);
}

__WUR std::string
tlucanti::Socket::recv() const
{
	std::string message;
	char buff[Socket::READ_SIZE + 1];

	ssize_t rbytes;

	while (true)
	{
		rbytes = ::recv(_sock, buff, Socket::READ_SIZE, 0);
		buff[rbytes] = 0;
		if (rbytes == Socket::READ_SIZE)
			message += buff;
		else if (rbytes <= 0)
			throw SocketException("recv error", errno);
		else
		{
			message += buff;

#ifdef __DEBUG
			std::cout << "data from " << _sock << " client (" <<
				message.size() << ")\n<";
			for (int i=0; i < (int)message.size(); ++i)
			{
				if (isprint(message.at(i)))
					std::cout << message.at(i);
				else
					std::cout << '(' << (int)message.at(i) << ')';
			}
			std::cout << ">\n";
#endif /* __DEBUG */

			return message;
		}
	}
}

void
tlucanti::Socket::send(const std::string &message) const
{
	ssize_t done = 0;

#ifdef __DEBUG
	std::cout << "sending to fd " << _sock << " message\n<";
	for (int i=0; i < (int)message.size(); ++i)
	{
		if (isprint(message.at(i)))
			std::cout << message.at(i);
		else
			std::cout << '(' << (int)message.at(i) << ')';
	}
	std::cout << ">\n";
#endif /* __DEBUG */

_SEND:
	done = ::send(_sock, message.c_str() + done, message.size(), MSG_NOSIGNAL);
	if (done < 0)
		throw SocketException("send error", errno);
	if (done < static_cast<ssize_t>(message.size()))
		goto _SEND;

#ifdef __DEBUG
	std::cout << "\n";
#endif /* __DEBUG */

}

void
tlucanti::Socket::close()
{
#ifdef __DEBUG
	std::cout << "closing socket " << _sock << std::endl;
#endif /* __DEBUG */

	::close(_sock);
	_sock = -1;
}

tlucanti::Socket &
tlucanti::Socket::operator =(const Socket &cpy)
{
	_sock = cpy._sock;
	_address = cpy._address;
	_port = cpy._port;
	return *this;
}
