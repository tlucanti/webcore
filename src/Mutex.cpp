/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mutex.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:49:26 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/17 18:00:04 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Mutex.hpp"
#warning "delete iostream"
#include <iostream>

tlucanti::Mutex::Mutex() noexcept
		: _mutex_v_(PTHREAD_MUTEX_INITIALIZER)
		{}

void
tlucanti::Mutex::lock()
{
//	std::cout << "locking mutex " << this << std::endl;
	pthread_mutex_lock(&_mutex_v_);
}

bool
tlucanti::Mutex::try_lock()
{
	return !!pthread_mutex_trylock(&_mutex_v_);
}

void
tlucanti::Mutex::unlock()
{
//	std::cout << "unlock " << this << std::endl;
	pthread_mutex_unlock(&_mutex_v_);
}

tlucanti::Mutex::~Mutex()
{
	unlock();
	pthread_mutex_destroy(&_mutex_v_);
}
