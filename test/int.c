/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   int.c is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   int.c is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <time.h>

#include "common.h"
#include "scouple.h"
#include "simple.h"

#define MIN_NODE (1)
#define MAX_INT_DATA (100)
#define MAX_NUM_NODES (1000)

struct data {
        int i;
};

static bool silent = true;

static int randomnumber(void)
{
	printv("Random number\n");
	static bool seeded;
	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	return rand() % MAX_INT_DATA;
}

static void asknumnodes(int *max)
{
	printf("Nodes, how many?\n");
	int n;
	if (silent) {
		n = (randomnumber() % (MAX_NUM_NODES - 1)) + 1;
		printf("%d\n", n);
	} else {
		int ign = scanf("%d", &n);
		(void)ign;
		if (n <= 0) {
			n = MIN_NODE;
		}
	}
	*max = n;
}

static void initdata(data **d)
{
	printv("Initialize data\n");
	data *n = calloc(sizeof *n);
	guilt(n, "initializing data failed; calloc\n", dnworry);
	n->i = randomnumber();
	*d = n;
}

static int comparedata(data *d1, data *d2)
{
	return d1->i - d2->i;
}

static char *datas(data *d)
{
	char *s = calloc(100);
	guilt(s, "stringizing data failed; calloc\n", dnworry, NULL);
	sprintf(s, "%d", d->i);
	return s;
}

static void freedata(data *d)
{
	free(d);
}

static void sortdata(data *d[], int n)
{
	int i = 0;
	while (i < n) {
		int j = 0;
		while (j < n - i - 1) {
			if (d[j]->i > d[j + 1]->i) {
				int t = d[j]->i;
				d[j]->i = d[j + 1]->i;
				d[j + 1]->i = t;
			}
			j++;
		}
		i++;
	}	
}

static data *copydata(data *d)
{
	data *c = calloc(sizeof *c);
	guilt(c, "copying data failed; calloc\n", dnworry, NULL);
	memcpy(c, d, sizeof *c);
	return c;		
}

static void addnodes(scouple *l, int max)
{
	int i = 1;
	while (i <= max) {
		addnode(l);
		i++;
	}
}

static scouple *askanddelsomenode(scouple *l)
{
	int numnodes = curnumnodes(l);
	printf("Node to delete among %d nodes? ", numnodes);
	fflush(stdout);
	int n;
	if (silent) {
		n = rand() % numnodes + 1;
		printf("%d\n", n);
	} else { 
		int ign = scanf("%d", &n);
		(void)ign;
	}
	return delnode(l, NULL, n);
}

static void initdataops(dataops *dops)
{
	printv("Initializing data operations\n");
	memset(dops, 0, sizeof *dops);
	dops->initdata = initdata;
	dops->comparedata = comparedata;
	dops->datas = datas;
	dops->freedata = freedata;
	dops->sortdata = sortdata;
	dops->copydata = copydata;
}

static scouple *newlist(bool atomic)
{
	int max;
	asknumnodes(&max);
	scouple *l = createlist();
	bool okay = initlist(l, atomic);
	if (okay) {
		initdataops(&l->m->dops);
	}
	addnodes(l, max);
	return l;
}

static scouple *testscouplifiedlist(scouple *l1)
{
	if (!l1) {
		l1 = newlist(true);
	}
	printlist(l1);
	l1 = askanddelsomenode(l1);
	printlist(l1);
	reverselistdata(l1);
	printlist(l1);
	l1 = reverselistnodes(l1);
	printlist(l1);
	l1 = swaphalves(l1);
	printlist(l1);
	scouple *l2 = newlist(true);
	printlist(l2);
	sortlistnodes(l2);
	printlist(l2);
	scouple *l3 = joinlist(l1, l2);
	printlist(l3);
	sortlistdata(l3);
	printlist(l3);
	scouple *fl = NULL;
	scouple *sl = NULL;
	halvelist(&l3, &fl, &sl);
	printlist(fl);
	printlist(sl);
	scouple *l4 = joinlist(fl, sl); // Returns NULL if either fl or sl is NULL.
	printlist(l4);
	l4 = l4 ? fl : sl;
	if (l4) {
		meta *m = l4->m;
		int numnodes = m->numnodes;
		int start = rand() % numnodes + 1;
		int end = rand() % numnodes + 1;
		if (start > end) {
			int t = start;
			start = end;
			end = t;
		}
		scouple *slc = slice(l4, start, end);
		printlist(slc);
		destroylist(l4); // (l4/l3) = fl + sl. So, destroy l3 at the end!
		scouple *bl = newlist(true);
		printlist(bl);
		scouple *brd = braid(bl, slc);
		printlist(brd);
		scouple *spl = spiralify(brd);
		printlist(spl);
		scouple *s = simplifylist(spl);
		destroylist(spl);
		return s;
	}
	return NULL;
}

static scouple *testsimplifiedlist(scouple *s)
{
	printsimplelist(s);
	scouple *l = scouplifysimplelist(s);
	destroysimplelist(s);
	return l;
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		silent = false;
	}
	int testnum = 1;
	scouple *l = NULL;
	while (-23) {
		printf("======================== Test %d ================\n", testnum++);
		scouple *s = testscouplifiedlist(l);
		l = testsimplifiedlist(s);
	}

	return 0;
}

