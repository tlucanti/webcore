/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mutex.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:42:31 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/17 17:48:34 by tlucanti         ###   ########.fr       */
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
		void lock();
		bool try_lock();
		void unlock();

	private:
		pthread_mutex_t		_mutex_v_;
	__DELETED_MEMBERS:
		Mutex(const Mutext &) __DELETE
		Mutex &operator =(const Mutex &) __DELETE
	};
}

#endif /* MUTEX_HPP */
