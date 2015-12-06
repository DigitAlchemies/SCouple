#
#   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
#   I wrote this SingleCouple library for fun in managing a singly
#   linked list as a doubly linked list with many useful APIs to
#   offer! Send any opinions/suggestions/bug reports to
#   raghavanil4m@gmail.com.
#
#   Makefile is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Makefile is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC := gcc
AR := ar crvs
INC := -I../dataops -I../libcommon
CFLAGS := -Wall -c
SHCFLAGS := -fPIC
SHLFLAGS := -shared
OFLAGS := -O2
DFLAGS := -g -D__VERBOSE__
ATOMIC := -D__ATOMIC_SUPPORT__

COMMON := $(CC) $(CFLAGS) $(INC)

all:
	$(COMMON) $(OFLAGS) $(SHCFLAGS) scouple.c -o scouple_shared.o
	$(COMMON) $(OFLAGS) scouple.c -o scouple_static.o
	$(COMMON) $(OFLAGS) $(SHCFLAGS) simple.c -o simple_shared.o
	$(COMMON) $(OFLAGS) simple.c -o simple_static.o
	$(CC) $(SHLFLAGS) scouple_shared.o simple_shared.o -o libscouple.so
	$(AR) libscouple.a scouple_static.o simple_static.o

atomic:
	$(COMMON) $(OFLAGS) $(SHCFLAGS) $(ATOMIC) scouple.c -o scouple_shared.o
	$(COMMON) $(OFLAGS) $(ATOMIC) scouple.c -o scouple_static.o
	$(COMMON) $(OFLAGS) $(ATOMIC) $(SHCFLAGS) simple.c -o simple_shared.o
	$(COMMON) $(OFLAGS) $(ATOMIC) simple.c -o simple_static.o
	$(COMMON) $(OFLAGS) $(ATOMIC) $(SHCFLAGS) atomic.c -o atomic_shared.o
	$(COMMON) $(OFLAGS) $(ATOMIC) atomic.c -o atomic_static.o
	$(CC) $(SHLFLAGS) scouple_shared.o simple_shared.o atomic_shared.o -o libscouple.so
	$(AR) libscouple.a scouple_static.o simple_static.o atomic_static.o

debug:
	$(COMMON) $(DFLAGS) $(SHCFLAGS) scouple.c -o scouple_debug_shared.o
	$(COMMON) $(DFLAGS) scouple.c -o scouple_debug_static.o
	$(COMMON) $(DFLAGS) $(SHCFLAGS) simple.c -o simple_debug_shared.o
	$(COMMON) $(DFLAGS) simple.c -o simple_debug_static.o
	$(CC) $(SHLFLAGS) scouple_debug_shared.o simple_debug_shared.o -o libscouple.so
	$(AR) libscouple.a scouple_debug_static.o simple_debug_static.o

debugatomic:
	$(COMMON) $(DFLAGS) $(SHCFLAGS) $(ATOMIC) scouple.c -o scouple_debug_shared.o
	$(COMMON) $(DFLAGS) $(ATOMIC) scouple.c -o scouple_debug_static.o
	$(COMMON) $(DFLAGS) $(SHCFLAGS) $(ATOMIC) simple.c -o simple_debug_shared.o
	$(COMMON) $(DFLAGS) $(ATOMIC) simple.c -o simple_debug_static.o
	$(COMMON) $(DFLAGS) $(ATOMIC) $(SHCFLAGS) atomic.c -o atomic_debug_shared.o
	$(COMMON) $(DFLAGS) $(ATOMIC) atomic.c -o atomic_debug_static.o
	$(CC) $(SHLFLAGS) scouple_debug_shared.o simple_debug_shared.o atomic_debug_shared.o \
										-o libscouple.so
	$(AR) libscouple.a scouple_debug_static.o simple_debug_static.o atomic_debug_static.o

clean:
	rm -f ./libscouple.*
	rm -f ./*.o


