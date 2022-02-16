/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:00:01 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/06 17:43:30 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_EXCEPTION_HPP
# define SERVER_EXCEPTION_HPP

# include "IRCException.hpp"

namespace tlucanti
{
	class ServerException : public IRCException
	{
	public:
		ServerException(const std::string &message, int error)
				: IRCException("server", message, error)  {}
	};
}

#endif	// SERVER_EXCEPTION_HPP
