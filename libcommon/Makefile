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

DFLAGS := -g -D__VERBOSE__
OFLAGS := -O2

cmd1 := gcc -c -Wall common.c -static -o libcommon.a
cmd2 := gcc -c -Wall common.c -fPIC -o common_shared.o
cmd3 := gcc -shared common_shared.o -o libcommon.so

all atomic:
	$(cmd1) $(OFLAGS)
	$(cmd2) $(OFLAGS)
	$(cmd3) $(OFLAGS)

debug debugatomic:
	$(cmd1) $(DFLAGS)
	$(cmd2) $(DFLAGS)
	$(cmd3) $(DFLAGS)

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so

