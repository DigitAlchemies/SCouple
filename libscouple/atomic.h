/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   atomic.h is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   atomic.h is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ATOMIC_H
#define _ATOMIC_H

#ifdef __ATOMIC_SUPPORT__

#include <pthread.h>
#include <sys/syscall.h>

#include "common.h"

struct lock {
	bool atom; // God particle!
	const char *f; // Locking/meditating function.
	pthread_mutex_t l;
};

inline bool isatomic(sclock *lock);
inline bool atom(sclock *lock);
inline bool molecule(sclock *lock);
inline bool meditate(sclock *lock, const char *func);
inline bool peaceout(sclock *lock, const char *func);

#define atomic(lock) do {\
			if (!(lock)->atom) {\
				return true;\
			}\
		} while (0)
#define molecular(lock) do {\
			if ((lock)->atom) {\
				return true;\
			}\
		} while (0)
#define meditating(lock) ((lock)->l.__data.__owner == gettid())
#define here(lock) ((lock)->f == func)

#define gettid() syscall(SYS_gettid)

#else

#define atomic(...)
#define molecular(...)
#define meditating(...)
#define here(...)

#endif // __ATOMIC_SUPPORT__

#endif // _ATOMIC_H

