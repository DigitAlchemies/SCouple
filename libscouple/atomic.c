/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   atomic.c is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   atomic.c is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __ATOMIC_SUPPORT__

#include "atomic.h"

//
// Basic lock initialization and destruction functions.(START)
//
// These *must* be called by the same thread and it
// will be a case of "Who guards the security guard?"
// otherwise!
//
inline bool initlock(sclock *lock)
{
	molecular(lock);
	pthread_mutexattr_t a = { { 0 } };
	bool k = !pthread_mutexattr_settype(&a, PTHREAD_MUTEX_ERRORCHECK); // Force __owner to be filled.
	if (k) {
		k = !pthread_mutex_init(&lock->l, &a);
		if (k) {
			lock->atom = true;
		}
	}
	return k;
}

inline bool isatomic(sclock *lock)
{
	return lock->atom;
}

inline bool destroylock(sclock *lock)
{
	atomic(lock);
	bool d = !pthread_mutex_destroy(&lock->l);
	if (d) {
		lock->atom = false;
	}
	return d;
}

inline bool atom(sclock *lock)
{
	return initlock(lock);
}

inline bool molecule(sclock *lock)
{
	return destroylock(lock);
}
//
// Basic lock initialization and destruction functions.(END)
//

inline bool meditate(sclock *lock, const char *func) // NOTE: Call only once in a function.
{
	printvy("Trying to meditate in %s() with lock(%p) . . .\n", func, (void *)lock);
	atomic(lock);
	if (!meditating(lock)) {
		bool calm = !pthread_mutex_lock(&lock->l);
		if (!calm) {
			return false;
		}
		lock->f = func;
		printvy("Meditating in %s() . . ." nocolor "\n", func);
	}
	return true;
}

inline bool peaceout(sclock *lock, const char *func) // NOTE: Call only once in a function.
					     	     // and in the *same* function in which
				 	     	     // you are meditating.
{
	printvy("Trying to attain peace in %s() with lock(%p) . . .\n", func, (void *)lock);
	atomic(lock);
	if (meditating(lock) && here(lock)) {
		bool peace = !pthread_mutex_unlock(&lock->l);
		if (!peace) {
			return false;
		}
		lock->f = NULL;
		printvy("At peace in %s().\n", func);
	}
	return true;
} 

#endif // __ATOMIC_SUPPORT__


