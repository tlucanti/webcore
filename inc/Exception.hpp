/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:51:45 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:16:26 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <stdexcept>
# include <string>
# include "defs.h"

namespace tlucanti {
	class Exception : public std::exception
	/*
		This is a dummy class for basic exception messages

		all classes in this library using this exception as base class

		you can override this file by your own exception class
	*/
	{
	public:
		Exception(const std::string &parent, const std::string &message,
			int error) noexcept
				: _message("[FAIL] " + parent + ": " + strerror(error) +
					": " + message) {}
		__WUR inline const char *what() const noexcept override
		{ return _message.c_str(); }
	private:
		const std::string _message;
	};
}

#endif /* EXCEPTION_HPP */
