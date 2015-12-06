/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   common.h is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   common.h is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#define dnworry (NULL)

#define calloc(size) ((calloc)(1, size))
#define usenthrow(outsider, insider, value) (&(outsider){ .insider = value })
#define half(num) ((num) >> 1)

#ifndef __ATOMIC_SUPPORT__
#define peaceout(...)
#endif

#define advice(a) (fprintf(stderr, a " : %s\n", strerror(errno)))
#define sane(c, l, ...) do {\
			if (!(c)) {\
				peaceout(l);\
				return __VA_ARGS__;\
			}\
		} while (0)
#define guilt(c, m, l, ...) do {\
				if (!(c)) {\
					advice(m);\
					peaceout(l);\
					return __VA_ARGS__;\
				}\
			} while (0)

#define green "\e[32m"
#define boldgreen "\e[32;1m"
#define yellow "\e[33m"
#define boldred "\e[31;1m"
#define boldcyan "\e[36;1m"
#define nocolor "\e[m"

#define arrow yellow "~>" nocolor
#define squarein boldcyan "[" nocolor
#define squareout boldcyan "]" nocolor
#define parenthin boldred "(" nocolor
#define parenthout boldred ")" nocolor
#define flowerin boldgreen "{" nocolor
#define flowerout boldgreen "}" nocolor

#define print(...) do {\
			printf(green);\
			printf(__VA_ARGS__);\
			printf(nocolor);\
			fflush(stdout);\
		} while (0)

#ifdef __VERBOSE__
#define printv(...) printf(__VA_ARGS__)
#define printvy(...) do {\
			printf(yellow);\
			printf(__VA_ARGS__);\
			printf(nocolor);\
			fflush(stdout);\
		} while (0)
#else
#define printv(...)
#define printvy(...)
#endif // __VERBOSE__

typedef struct scouple scouple;
typedef struct meta meta;
typedef struct data data;
typedef struct dataops dataops;
#ifdef __ATOMIC_SUPPORT__
typedef struct lock sclock;
#endif // __ATOMIC_SUPPORT__

extern char *strone(const char *s, ...);

#endif // _COMMON_H

