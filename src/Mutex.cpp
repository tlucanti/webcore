/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mutex.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:49:26 by tlucanti          #+#    #+#             */
/*   Updated: 2022/02/23 18:19:18 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Mutex.hpp"

tlucanti::Mutex::Mutex() noexcept
{
	pthread_mutex_init(&_mutex_v_, nullptr);
}

void
tlucanti::Mutex::lock() noexcept
{
	pthread_mutex_lock(&_mutex_v_);
}

bool
tlucanti::Mutex::try_lock() noexcept
{
	return !!pthread_mutex_trylock(&_mutex_v_);
}

void
tlucanti::Mutex::unlock() noexcept
{
	pthread_mutex_unlock(&_mutex_v_);
}

tlucanti::Mutex::~Mutex() noexcept
{
	unlock();
	pthread_mutex_destroy(&_mutex_v_);
}
