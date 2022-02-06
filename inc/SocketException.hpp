/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:54 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/06 17:43:33 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_EXCEPTION_HPP
# define SOCKET_EXCEPTION_HPP

#include "IRCException.hpp"

namespace tlucanti
{
	class SocketException : public IRCException
	{
	public:
		SocketException(const std::string &message, int error)
				: IRCException("socket", message, error) {}
	};
}

#endif	// SOCKET_EXCEPTION_HPP
