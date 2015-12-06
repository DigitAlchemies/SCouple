/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   dataops.h is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   dataops.h is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _DATAOPS_H
#define _DATAOPS_H

#include "common.h"

typedef void (initdataf)(data **);
typedef int (comparedataf)(data *d1, data *d2); // returns 0(==), +ve(>), -ve(<)
typedef char *(dataf)(data *d); // returns an empty string("n/a") if data is not stringizable
typedef void (freedataf)(data *d);
typedef void (sortdataf)(data *d[], int n);
typedef data *(copydataf)(data *d);

// Defined by the user
struct dataops {
	initdataf *initdata;
	comparedataf *comparedata;
	dataf *datas;
	freedataf *freedata;
	sortdataf *sortdata;
	copydataf *copydata;
};

#endif // _DATAOPS_H

