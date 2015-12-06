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

INC := -I../libscouple -I../libcommon -I../dataops
CFLAGS := -Wall
OFLAGS := -O2
DFLAGS := -g
LFLAGS := -L../libscouple -lscouple -L../libcommon -lcommon
AFLAGS := -D__ATOMIC_SUPPORT__ -lpthread
cmd := gcc $(CFLAGS) $(INC) int.c -o int $(LFLAGS)

all:
	$(cmd) $(OFLAGS)

atomic:
	$(cmd) $(OFLAGS) $(AFLAGS)

debug:
	$(cmd) $(DFLAGS)

debugatomic:
	$(cmd) $(DFLAGS) $(AFLAGS)

clean:
	rm -f int
	rm -f *.o


