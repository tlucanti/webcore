/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:43:54 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:19:05 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_EXCEPTION_HPP
# define SOCKET_EXCEPTION_HPP

# include "Exception.hpp"

namespace tlucanti
{
	class SocketException : public tlucanti::Exception
	{
	public:
		SocketException(const std::string &message, int error)
				: Exception("socket", message, error) {}
	};
}

#endif /* SOCKET_EXCEPTION_HPP */
