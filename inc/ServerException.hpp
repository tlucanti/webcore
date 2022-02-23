/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:00:01 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:18:26 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_EXCEPTION_HPP
# define SERVER_EXCEPTION_HPP

# include "Exception.hpp"

namespace tlucanti
{
	class ServerException : public Exception
	{
	public:
		ServerException(const std::string &message, int error)
				: Exception("server", message, error)  {}
	};
}

#endif /* SERVER_EXCEPTION_HPP */
