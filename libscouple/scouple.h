/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   scouple.h is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   scouple.h is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SCOUPLE_H
#define _SCOUPLE_H

#include "common.h"
#include "dataops.h"
#include "atomic.h"

// Meta is ubiquitous.
struct meta {
	scouple *head;
	scouple *midp;
	scouple *mid;
	scouple *tail;
	int numnodes;
	dataops dops;
#ifdef __ATOMIC_SUPPORT__
	sclock lock;
#endif // __ATOMIC_SUPPORT__
};
// Holds user data.
struct scouple {
	data *d;
	meta *m;
	scouple *next;
};

int curnumnodes(scouple *l);
void metabolize(scouple *l);
void demetabolize(scouple *l);
bool initlist(scouple *l, bool atomic);
scouple *nodenum(scouple *l, int n);
scouple *addnode(scouple *l);
scouple *delnode(scouple *l, data *d, int n);
void printlist(scouple *l);
scouple *createlist(void);
void destroylist(scouple *l);
scouple *finddatainlist(scouple *l, data *d);
data *dataofnodenum(scouple *l, int n);
void sortlistdata(scouple *l);
void sortlistnodes(scouple *l);
void reverselistdata(scouple *l);
scouple *reverselistnodes(scouple *l);
void fixmid(scouple *l, bool newmid);
scouple *swaphalves(scouple *l);
void replacemeta(scouple *l1, scouple *l2);
scouple *joinlist(scouple *l1, scouple *l2);
void halvelist(scouple **l, scouple **l1, scouple **l2);
scouple *slice(scouple *l, int start, int end);
scouple *braid(scouple *l1, scouple *l2);
scouple *spiralify(scouple *l);
scouple *simplifylist(scouple *l);

#define midin(l) ((l)->m->mid == (l) ? flowerin : "")
#define midout(l) ((l)->m->mid == (l) ? flowerout : "")

#define decor(v, f) yellow #v "(" nocolor "%" #f yellow ") " nocolor
#define p(v) decor(v, p)
#define d(v) decor(v, d)
#define s(v) decor(v, s)

#define midfmt p(mid) p(midp) p(head) p(tail) d(numnodes) "\n"
#define dopsfmt yellow "dataops : " p(initdata) p(comparedata) p(datas) p(freedata) p(sortdata) p(copydata) "\n"
#define midargs(m) (void *)(m)->mid, (void *)(m)->midp, (void *)(m)->head, (void *)(m)->tail, (m)->numnodes
#define dopsargs(m) 	(void *)(m)->dops.initdata, (void *)(m)->dops.comparedata, (void *)(m)->dops.datas,\
			(void *)(m)->dops.freedata, (void *)(m)->dops.sortdata, (void *)(m)->dops.copydata

#ifdef __ATOMIC_SUPPORT__
#define lockfmt yellow "lock : " s(atomic) p(lockfunc) "and with a pthread mutex.\n"
#define lockargs(m) , (m)->lock.atom ? "true" : "false", (void *)(m)->lock.f
#else
#define lockfmt
#define lockargs(...)
#endif

#define printmeta(m) printf(	midfmt\
				dopsfmt\
				lockfmt,\
				midargs(m),\
				dopsargs(m)\
				lockargs(m));

#define center(n) (((n) >> 1) + ((n) & 0x1))
#define scoupleof(ptr, field) ((scouple *)((char *)(ptr) - offsetof(scouple, field)))

#ifdef __VERBOSE__
	#define printlistdata(l, n) do {\
					char *s = (l)->m->dops.datas((l)->d);\
					printf(squarein "%p" squareout\
						parenthin "%p" parenthout\
						"%s%s%s"\
						"%s",\
						(void *)(l),\
						(void *)(l)->d,\
						midin(l), s, midout(l),\
						(n) ? arrow : "");\
					free(s);\
				} while (0)
	#define printsimplelistdata(s) printlistdata((s), (s)->next)
#else
	#define printlistdata(l, n) do {\
					char *s = (l)->m->dops.datas((l)->d);\
					printf("%s%s%s"\
						"%s",\
						midin(l), s, midout(l),\
						(n) ? arrow : "");\
					free(s);\
				} while (0)
	#define printsimplelistdata(s) printlistdata((s), (s)->next)
#endif // __VERBOSE__

#define xor(p1, p2) ((scouple *)((uintptr_t)(p1) ^ (uintptr_t)(p2)))

#define metabolic(l, ...) do {\
				sane(l, dnworry, __VA_ARGS__);\
				sane((l)->m, dnworry, __VA_ARGS__);\
			} while (0)
#define metabolized(l, ...) do {\
			sane(l, dnworry, __VA_ARGS__);\
			sane(!(l)->m, dnworry, __VA_ARGS__);\
		} while (0)

#ifdef __ATOMIC_SUPPORT__

// Wrapper macros for actual functions to eliminate noise
// in the actual function.
//
#define isatomic(list) ((list) ? (isatomic)(&(list)->m->lock) : true)
#define atom(list) ((list) ? (atom)(&(list)->m->lock) : true)
#define molecule(list) ((void)((list) ? (molecule)(&(list)->m->lock) : true))
#define meditate(list) ((void)((list) ? (meditate)(&(list)->m->lock, __func__) : true))
#define peaceout(list) ((void)((list) ? (peaceout)(&((scouple *)(list))->m->lock, __func__) : true))
#define makeatomic(list, beatomic, ...) do {\
					if (beatomic) {\
						bool atomicized = atom(list);\
						guilt(atomicized,\
							"atomicizing the list failed; "\
							"pthead_mutex_init\n", dnworry, __VA_ARGS__);\
					}\
				} while (0)
//
// Wrapper macros for actual functions to eliminate noise
// in the actual function.

#else

#define isatomic(...) (false)
#define atom(...)
#define molecule(...)
#define meditate(...)
#define peaceout(...)
#define makeatomic(...)

#endif // __ATOMIC_SUPPORT__

#endif // _SCOUPLE_H

