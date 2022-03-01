/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Thread.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:56:47 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:19:10 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_HPP
# define THREAD_HPP

# include <cstring>
# include <stdexcept>

# include "defs.h"
# include "pthread.h"

namespace tlucanti
{
	class Thread
	{
	public:
		Thread(void *(*func)(void *), const void *arg)
				: pthread_id()
		{
			int status = pthread_create(&pthread_id, nullptr, func, &arg);
			if (status)
				throw std::runtime_error(strerror(errno));
		}
		~Thread() __DEFAULT

		inline void join() { pthread_join(pthread_id, nullptr); }
		__WUR inline pthread_t get_id() const { return pthread_id; }

	private:
		pthread_t pthread_id;

	__DELETED_MEMBERS:
		Thread() __DELETE
		Thread(const Thread &) __DELETE
		Thread &operator =(const Thread &) __DELETE
	};
}

#endif /* THREAD_HPP */
