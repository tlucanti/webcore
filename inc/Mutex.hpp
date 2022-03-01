/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mutex.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:42:31 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/28 16:50:26 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_HPP
# define MUTEX_HPP

# include <pthread.h>

# include "defs.h"

namespace tlucanti
{
	class Mutex
	{
	public:
		Mutex() noexcept;
		~Mutex() noexcept;
		void lock() noexcept;
		bool try_lock() noexcept;
		void unlock() noexcept;

	private:
		pthread_mutex_t		_mutex_v_;

	__DELETED_MEMBERS:
		Mutex(const Mutex &) __DELETE
		Mutex &operator =(const Mutex &) __DELETE
	};
}

#endif /* MUTEX_HPP */
