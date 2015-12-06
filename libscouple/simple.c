/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   simple.c is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   simple.c is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simple.h"

/////////////////////////////////////////////////////////////////////
// NOTE: All simple lists operations are expected to be lock-free. //
/////////////////////////////////////////////////////////////////////

scouple *scouplifysimplelist(scouple *s)
{
	print("Scouplifying simple list . . .\n");
	metabolic(s, NULL);
	meta *sm = s->m;
	scouple *c = sm->head;
	meta *m = calloc(sizeof *m);
	guilt(m, "creating meta for scouplified list failed; calloc", dnworry, NULL);
	scouple *p = NULL;
	m->dops = sm->dops;
	while (c) {
		scouple *n = calloc(sizeof *n);
		if (!n) {
			advice("scouplified list may be incomplete; calloc");
			break;
		}
		n->m = m;
		n->d = m->dops.copydata(c->d);
		if (!n->d) {
			free(n);
			n = NULL;
			advice("copying data for scouplified list failed; calloc");
			break;
		}	
		n->next = p;
		bool odd = ++m->numnodes & 0x1;
		if (p) {
			p->next = xor(p->next, n);
		}
		if (!m->head) {
			m->mid = m->head = n;
		} else if (odd) {
			scouple *midn = xor(m->mid->next, m->midp);
			m->midp = m->mid;
			m->mid = midn;
		}
		p = m->tail = n;
		c = c->next;
	}
	if (!m->numnodes) {
		free(m);
		return NULL;
	}
	return m->head;	
}

void printsimplelist(scouple *s)
{
	print("Simple list");
	metabolic(s);
	meta *m = s->m;
	print("(%d) : ", m->numnodes);
	scouple *c = m->head;
	while (c) {
		printsimplelistdata(c);
		c = c->next;
	}
	printf("\n");
}

void destroysimplelist(scouple *s)
{
	print("Destroying simple list . . .\n");
	metabolic(s);
	dataops dops = s->m->dops;
	demetabolize(s);
	while (s) {
		scouple *n = s->next;
		dops.freedata(s->d);
		free(s);	
		s = n;
	}
}


