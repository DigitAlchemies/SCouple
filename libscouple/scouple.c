/*
 *   Copyright (C) 2015  Raghavan Santhanam, raghavanil4m@gmail.com.
 *   I wrote this SingleCouple library for fun in managing a singly
 *   linked list as a doubly linked list with many useful APIs to
 *   offer! Send any opinions/suggestions/bug reports to
 *   raghavanil4m@gmail.com.
 *
 *   scouple.c is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   scouple.c is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "scouple.h"

int curnumnodes(scouple *l)
{
	metabolic(l, -1);
	return l->m->numnodes;
}

void metabolize(scouple *l)
{
	sane(l, dnworry);
	l->m = calloc(sizeof *l->m);
	guilt(l->m, "creating meta failed; calloc", dnworry);
}

void demetabolize(scouple *l)
{
	sane(l, dnworry);
	free(l->m);
	l->m = NULL;
}

bool initlist(scouple *l, bool atomic)
{
	metabolized(l, false);
	metabolize(l); // Meta is ubiquitous.
	meta *m = l->m;
	guilt(m, "initialization of list failed\n", dnworry, false);
	makeatomic(l, atomic, false);
	return true;
}

scouple *createlist(void)
{
	scouple *l = calloc(sizeof *l);
	guilt(l, "creating new scouple failed; calloc", dnworry, NULL);
	return l;
}

scouple *nodenum(scouple *l, int n)
{
	metabolic(l, NULL);
	meditate(l);
	meta *m = l->m;
	sane(n <= 0 || n >= m->numnodes, l, NULL);
	scouple *c = m->head;
	scouple *p = NULL;
	int i = 1;
	while (c) {
		if (i == n) {
			break;
		}
		scouple *n = xor(c->next, p);
		p = c;
		c = n;
		i++;
	}
	peaceout(l);
	return c;
}

scouple *addnode(scouple *l)
{
	printv("Adding node . . .\n");
	metabolic(l, NULL);
	meditate(l);
	meta *m = l->m;
	if (!m->numnodes) {
		// The very first node of the list acts as the head
		// of the node as well as the place holder for an
		// empty list. A list is said to be "empty" when
		// it's not *metabolized*, in other words, if <l>
		// is the list, then <l->m> should be non-NULL
		// to say the list is not empty.
		m->tail = m->mid = m->head = l;
		m->dops.initdata(&l->d);
		m->numnodes++;
		peaceout(l);
		return l;
	}
	scouple *n = calloc(sizeof *n);
	guilt(n, "adding node failed; calloc", l, NULL);
	n->m = m;
	n->next = m->tail; // xor() for the new tail will be just the previous node.
				// The previous node to the new node will be the
				// current tail.
	int nn = ++m->numnodes;
	m->dops.initdata(&n->d);
	m->tail->next = xor(m->tail->next, n);
	bool odd = nn & 0x1;
	if (odd) {
		// Mid takes one step forward for every even node added
		scouple *t = m->mid;
		m->mid = xor(m->mid->next, m->midp);
		m->midp = t;
	}
	m->tail = n;
	peaceout(l);
	return n;
}

static void updatemid(scouple *c, int n, int numnodes)
{
	int midnum = center(numnodes);
	bool odd = numnodes & 0x1;
	meta *m = c->m;
	scouple *midpp = m->midp ? xor(m->midp->next, m->mid) : NULL;
	scouple *midn = xor(m->mid->next, m->midp);
	if (odd) {
		bool behindmidp = n < midnum - 1;
		if (c == m->mid) {
			m->mid = midn;
		} else if (c == m->midp || behindmidp) {
			m->midp = m->mid;
			m->mid = midn;
		}
	} else {
		bool aheadofmidp = n > midnum;
		if (c == m->mid || aheadofmidp) {
			m->mid = m->midp;
			m->midp = midpp;
		} else if (c == m->midp) {
			m->midp = midpp;
		}
	}
}

//
// Deleting a node in a given list based on data-match(d) or
// the node number(n). Always, <d> is given preference over
// <n>. Here, data-match is content-wise as opposed to
// address-wise.
//
scouple *delnode(scouple *l, data *d, int n)
{
	printv("Deleting node . . .\n");
	metabolic(l, l); // Nothing to do on an empty list.
	meditate(l);
	meta *m = l->m;
	scouple *c = m->head;
	scouple *p = NULL;
	if (d) {
		while (c) {
			bool same = !m->dops.comparedata(c->d, d);
			if (same) {
				break;
			}
			scouple *n = xor(c->next, p);
			p = c;
			c = n;
		}
	} else {
		int numnodes = m->numnodes;
		sane(n > 0 && n <= numnodes, l, m->head);
		int i = 1;
		while (c) {
			bool found = i == n;
			if (found) {
				break;
			}
			scouple *n = xor(c->next, p);
			p = c;
			c = n;
			i++;
		}
	}
	if (c) {
		int numnodes = --m->numnodes;
		if (!numnodes) {
			m->dops.freedata(c->d);
			peaceout(l);
			molecule(l);
			demetabolize(c);
			free(c);
			return NULL;
		}

		updatemid(c, n, numnodes);

		// Now, just remove the node informing
		// his close ones and console them, if possible.
		// Just got emotional, chill!
		scouple *cn = xor(c->next, p);
		if (p) {
			p->next = xor(p->next, c);
			p->next = xor(p->next, cn);
		}
		if (cn) {
			cn->next = xor(cn->next, c);
			cn->next = xor(cn->next, p);
		}
		if (c == m->head) {
			m->head = m->head->next;
		} else if (c == m->tail) {
			m->tail = m->tail->next;
		}
		m->dops.freedata(c->d); // Don't free (m). It's reference-counted.
		free(c);
	}
	peaceout(l);
	return m->head;
}

void printlist(scouple *l)
{
	print("Priniting list . . .\n");
	metabolic(l);
	meditate(l);
	meta *m = l->m;
	print("List(%d) : ", m->numnodes);
	scouple *c = m->head;
	scouple *p = NULL;
	while (c) {
		scouple *n = xor(c->next, p);
		printlistdata(c, n);
		fflush(stdout);
		p = c;
		c = n;
	}
	printf("\n");
	peaceout(l);
}

void destroylist(scouple *l)
{
	print("Destroying scouple list . . .\n");
	sane(l, dnworry);
	meditate(l);
	if (!l->m) {
		// Empty list.
		peaceout(l);
		free(l);
		return;
	}
	meta *m = l->m;
	scouple *c = m->head;
	scouple *p = NULL;
	dataops dops = m->dops;
	while (c) {
		scouple *n = xor(c->next, p);
		dops.freedata(c->d);
		free(c);
		p = c; // Holds address. Won't be dereferenced.
		c = n;
	}
	peaceout(l);
	demetabolize(l); // Lock is inside meta.
}

//
// Content-wise data-match as opposed to address-wise.
//
scouple *finddatainlist(scouple *l, data *d)
{
	print("Finding data in list . . .\n");
	metabolic(l, NULL);
	sane(d, dnworry, NULL);
	meditate(l);
	meta *m = l->m;
	scouple *c = m->head;
	scouple *p = NULL;
	while (c) {
		scouple *n = xor(c->next, p);
		bool same = !m->dops.comparedata(c->d, d);
		if (same) {
			break;
		}
		p = c;
		c = n;
	}
	peaceout(l);
	return c;	
}

data *dataofnodenum(scouple *l, int n)
{
	meditate(l);
	scouple *nn = nodenum(l, n);
	sane(nn, l, NULL);
	peaceout(l);
	return nn->d;
}

void sortlistdata(scouple *l)
{
	print("Sorting list data . . .\n");
	metabolic(l);
	meditate(l);
	meta *m = l->m;
	data *dptr[m->numnodes];
	scouple *c = m->head;
	scouple *p = NULL;
	int i = 0;
	while (c) {
		scouple *n = xor(c->next, p);
		dptr[i++] = c->d;
		p = c;
		c = n;
	}
	m->dops.sortdata(dptr, i);
	peaceout(l);
}

static void scoupleswap(scouple *n1, scouple *n2)
{
	//
	// The list looks like this. 
	// <-> n1p <-> n1 <-> n2 <-> n2n <->
	// And the list becomes like this.
	// <-> n1p <-> n2 <-> n1 <-> n2n <->
	//
	scouple *n1p = xor(n1->next, n2);
	scouple *n2n = xor(n2->next, n1);
	if (n1p) {
		n1p->next = xor(n1p->next, n1); // n1p <-break-> n1
		n1p->next = xor(n1p->next, n2); // n1p <-make-> n2
	}
	if (n2n) {
		n2n->next = xor(n2n->next, n2); // n2 <-break-> n2n
		n2n->next = xor(n2n->next, n1); // n1 <-make-> n2n
	}
	n1->next = xor(n1->next, n1p); // n1p <-break-> n1
	n1->next = xor(n1->next, n2n); // n1 <-make-> n2n
	n2->next = xor(n2->next, n2n); // n2 <-break-> n2n
	n2->next = xor(n2->next, n1p); // n1p <-make-> n2
}

static void scouplesort(scouple *l, scouple *nodeptr[])
{
	meta *m = l->m;
	int numnodes = m->numnodes;
	dataops dops = m->dops;
	int i = 0;
	while (i < numnodes) {
		int j = 0;
		while (j < numnodes - i - 1) {
			bool greater = dops.comparedata(nodeptr[j]->d, nodeptr[j + 1]->d) > 0;
			if (greater) {
				//
				// Instead of doing a scoupleswap() here, we can
				// simply sort the nodeptr[] and later run through
				// the sorted nodeptr[] and fix the <next> of each
				// node. Though it may looks simpler, that's
				// inefficient compared to fixing the <next> if and
				// only if needed. For example, when the list is
				// already sorted, there will be no swapping required
				// at all and in that case fixing the <next> later
				// is unnecessary and thus inefficient.
				//
				// Thus, do scoupleswap() only when needed as under.
				//
				scoupleswap(nodeptr[j], nodeptr[j + 1]); // Swap in the list positions.
				// Now, swap in the array for this sorting to be correct.
				scouple *t = nodeptr[j];
				nodeptr[j] = nodeptr[j + 1];
				nodeptr[j + 1] = t;
			}
			j++;
		}
		i++;
	}
}

void sortlistnodes(scouple *l)
{
	print("Sorting list nodes . . .\n");
	metabolic(l);
	meditate(l);
	meta *m = l->m;
	int numnodes = m->numnodes;
	sane(numnodes > 1, l);
	scouple *nodeptr[numnodes];
	scouple *c = m->head;
	scouple *p = NULL;
	int i = 0;
	while (c) {
		scouple *n = xor(c->next, p);
		nodeptr[i++] = c;
		p = c;
		c = n;
	}
	scouplesort(l, nodeptr);
	// Now, just fix the meta like a boss! \m/
	m->head = nodeptr[0];
	m->tail = nodeptr[numnodes - 1];
	int mid = center(numnodes) - 1;
	m->mid = nodeptr[mid];
	m->midp = mid >= 1 ? nodeptr[mid - 1] : NULL;
	peaceout(l);
}

void reverselistdata(scouple *r)
{
	print("Reversing list data . . .\n");
	metabolic(r);
	meditate(r);
	meta *m = r->m;
	sane(m->numnodes >= 2, r);
	scouple *f = m->head;
	scouple *fp = NULL;
	scouple *l = m->tail;
	scouple *lp = NULL;
	int i = 1;
	int numloops = half(m->numnodes);
	while (i <= numloops) {
		scouple *fn = xor(f->next, fp);
		scouple *ln = xor(l->next, lp);
		data *t = f->d;
		f->d = l->d;
		l->d = t;
		fp = f;
		f = fn;
		lp = l;
		l = ln;
		i++;
	}
	peaceout(r);
}

scouple *reverselistnodes(scouple *l)
{
	print("Reversing list nodes . . .\n");
	metabolic(l, l); // l->m could be NULL, but l.
	meditate(l);
	meta *m = l->m;
	sane(m->numnodes >= 2, l, l);
	// Mandatory updates of O(1) helpers.
	bool odd = m->numnodes & 0x1;
	scouple *midn = xor(m->mid->next, m->midp);
	scouple *midnn = midn ? xor(midn->next, m->mid) : NULL;
	if (odd) {
		m->midp = midn;
	} else {
		m->mid = midn;
		m->midp = midnn;
	}
	// Make the best use of prev ^ next relation
	scouple *t = m->head;
	m->head = m->tail;
	m->tail = t;
	peaceout(l);
	return m->head;
}

scouple *swaphalves(scouple *l)
{
	print("Swapping halves . . .\n");
	metabolic(l, l); // Meta might be NULL. But, list might not be.
	meditate(l);
	meta *m = l->m;
	int numnodes = m->numnodes;
	sane(numnodes >= 2, l, l);
	bool odd = numnodes & 0x1;
	if (odd) {
		if (numnodes == 3) {
			scouple *t = m->head;
			m->midp = m->head = m->tail;
			m->tail = t;
			peaceout(l);
			return m->head;
		}
		// Engage head and tail with mid.
		m->tail->next = xor(m->tail->next, m->mid);
		m->head->next = xor(m->head->next, m->mid);
		// Untangle midp and midn from mid.
		scouple *midn = xor(m->mid->next, m->midp);
		m->midp->next = xor(m->midp->next, m->mid);
		midn->next = xor(midn->next, m->mid);
		// Entangle mid with new mates.
		m->mid->next = xor(m->tail, m->head);
		// Groom the boys.
		scouple *t = m->tail;
		m->head = midn;
		m->tail = m->midp;
		m->midp = t;
	} else {
		if (numnodes == 2) {
			scouple *t = m->head;
			m->head = m->tail;
			m->mid = m->tail;
			m->tail = t;
			peaceout(l);
			return m->head;
		}
		scouple *midn = xor(m->mid->next, m->midp);
		// Engage head and tail with each other.
		m->head->next = xor(m->head->next, m->tail);
		scouple *tailp = m->tail->next;
		m->tail->next = xor(m->tail->next, m->head);
		// Untangle mid and midn from each other.
		m->mid->next = xor(m->mid->next, midn);
		midn->next = xor(midn->next, m->mid);
		// Groom the boys.
		scouple *t = m->mid;
		m->mid = m->tail;
		m->midp = tailp;
		m->head = midn;
		m->tail = t;
	}
	peaceout(l);
	return m->head;
}

void replacemeta(scouple *replaceel, scouple *replacerl)
{
	metabolic(replaceel);
	metabolic(replacerl);
	meditate(replacerl);
	meditate(replaceel);
	meta *rm = replaceel->m;
	meta *am = replacerl->m;
	scouple *c = rm->head;
	scouple *p = NULL;
	while (c) {
		c->m = am;
		scouple *t = c;
		c = xor(c->next, p);
		p = t;
	}
	peaceout(usenthrow(scouple, m, rm));
	peaceout(replaceel);
}

// pn acts as "previous" in forward mode and as "next" otherwise.
static void walklist(scouple *l, scouple *pn, bool forward, int steps, scouple **mid, scouple **midp)
{	
	while (steps--) {
		scouple *t = pn;
		pn = l;
		l = xor(l->next, t);
	}
	*mid = l;
	if (forward) {
		*midp = pn;
	} else {
		*midp = xor(l->next, pn);
	}
}

//
// Joins two scouplified lists and updates the mid pointers. The latter is complex.
// The complexity comes from the need to efficiently traverse the list which will
// have the new mid and midp of the joined list. The efficiency is achieved by
// determining which one of the mid and tail is nearer to the new mid and midp.
// Once determined, the traversal happens from either mid in forward direction
// or from tail in backward direction to reach the new mid and midp needed.
//
// In addition, the meta of the longer list(which has the new mid and midp),
// will be used for the joined list. This replaces the shorter list's meta.
// The replaced meta is discarded. If both lists are equal in length, we pick
// first list's meta and replace the second's meta with that throughout.
//
scouple *joinlist(scouple *l1, scouple *l2)
{
	print("Joining lists . . .\n");
	metabolic(l1, NULL);
	metabolic(l2, NULL);
	meditate(l1);
	meditate(l2);
	meta *m1 = l1->m;
	meta *m2 = l2->m;
	int n1 = m1->numnodes;
	int n2 = m2->numnodes;
	int mid1 = center(n1);
	int mid2 = center(n2);
	int n = n1 + n2;
	int m = center(n);
	scouple *mid = m1->tail;
	scouple *midp = m1->tail->next;
	scouple *replacerl = l1;
	scouple *replaceel = l2;
	if (n1 != n2) {	// Unequal lengths of the lists.
		//
		// Assume first list is longer.
		//
		scouple *midd = m1->mid;
		scouple *middp = m1->midp;
		scouple *middn = NULL; // N/A for first list.
		int middiff = abs(m - mid1);
		int taildiff = abs(m - n1);
		scouple *tail = m1->tail;
		bool midisinsecondlist = n2 > n1;
		if (midisinsecondlist) {
			// Okay, second one is longer.
			middiff = abs(m - (n1 + mid2)); // m is relative to n1
			taildiff = abs(m - (n1 + n2));  // -- ditto --
			tail = m2->tail;
			midd = m2->mid;
			middn = xor(m2->mid->next, m2->midp);
			replacerl = l2;
			replaceel = l1;
		}
		bool midisnearer = middiff < taildiff;
		bool forward = !midisinsecondlist && midisnearer; // Mid is nearer to new mid?
		int steps = midisnearer ? middiff : taildiff;
		scouple *c = forward ? midd :
				!midisinsecondlist ? tail :
						midisnearer ? midd : tail;
		scouple *p = forward ? middp :
				!midisinsecondlist ? NULL :
						midisnearer ? middn : NULL; 
		walklist(c, p, forward, steps, &mid, &midp); // March towards the new mid and midp
							// taking steps in the right direction.
		if (midisinsecondlist && !midp) {
			// Border case! Zero miles walked!
			midp = m1->tail;
		}
	} else {
		// Equal lengths. Nothing extraordinary.
		mid = m1->tail;
		midp = m1->tail->next;
	}
	meta *replacerm = replacerl->m;
	meta *replaceem = replaceel->m;
	replacemeta(replaceel, replacerl); // Reuse a single meta(m1 or m2) for the combined list.
	m1->tail->next = xor(m1->tail->next, m2->head);
	m2->head->next = xor(m2->head->next, m1->tail);
	replacerm->mid = mid;
	replacerm->midp = midp;
	replacerm->tail = m2->tail;
	replacerm->head = m1->head;
	replacerm->numnodes = n;
	if (replaceem == m2) {
		peaceout(usenthrow(scouple, m, replaceem));
		peaceout(l1);
	} else {
		peaceout(l2);
		peaceout(usenthrow(scouple, m, replaceem));
	}
	free(replaceem); // Discard the replaced meta.
	return l1;
}

void fixmid(scouple *l, bool newmid)
{
	metabolic(l);
	meditate(l);
	meta *m = l->m;
	int i = 1;
	int n = m->numnodes;
	int numloops = center(n) - 1;
	scouple *c = m->head;
	scouple *p = NULL;
	while (i <= numloops) {
		if (newmid) {
			// Specific to halvelist().
			//  First node of the second half will have new mid
			//  but the rest.
			c->m = m;
		}
		scouple *n = xor(c->next, p);
		p = c;
		c = n;
		i++;
	}
	m->mid = c;
	m->midp = p;
	if (newmid) {
		// Specific to halvelist().
		//  First node of the second half will have new mid
		//  but the rest.
		while (c) {
			// Update it from mid onward.
			c->m = m;
			scouple *n = xor(c->next, p);
			p = c;
			c = n;
		}
	}
	peaceout(l);
}

//
// First list has the nodes until mid and the second the rest.
// First list reuses the existing meta while the second uses a
// new meta.
//
void halvelist(scouple **ll, scouple **l1, scouple **l2)
{
	print("Halving the list . . .\n");
	sane(ll, dnworry);
	scouple *l = *ll;
	metabolic(l);
	meditate(l);
	meta *m = l->m;
	sane(m->numnodes > 1, l);
	sane(l1 && l2, l);
	int numnodes = m->numnodes;
	scouple *head1 = m->head;
	scouple *tail1 = m->mid;
	scouple *midn = xor(m->mid->next, m->midp);
	scouple *head2 = midn;
	scouple *tail2 = m->tail;
	// Unchain the two siblings.
	tail1->next = xor(tail1->next, head2);
	head2->next = xor(head2->next, tail1);
	// List 1 - retains existing meta.
	meta *m1 = m;
	m1->head = head1; // Dummy. For clarity.
	m1->tail = tail1;
	m1->numnodes = center(numnodes);
	*l1 = head1;
	fixmid(*l1, false);
	// List 2 - uses new meta.
	*l2 = head2;
	(*l2)->m = NULL; // We *shouldn't* free <(*l2)->m> here, since
			 // first half is reusing it!
	metabolize(*l2);
	makeatomic(*l2, isatomic(l));
	meta *m2 = (*l2)->m;
	m2->head = head2;
	m2->tail = tail2;
	m2->numnodes = numnodes - m1->numnodes;
	m2->dops = m1->dops;
	fixmid(*l2, true);
	peaceout(l);
	*ll = NULL;
}

//
// Creates a slice from the main list from start to end.
// Sliced list will be a copy of the main list from start to end.
//
scouple *slice(scouple *l, int start, int end)
{
	print("Slicing list from %d to %d\n", start, end);
	metabolic(l, NULL);
	meditate(l);
	meta *m = l->m;
	int numnodes = m->numnodes;
	sane(start >= 1 && start <= numnodes && end <= numnodes && start <= end, l, NULL);
	int i = 1;
	scouple *c = m->head;
	scouple *p = NULL;
	// Walk on to start.
	while (c && i < start) {
		scouple *n = xor(c->next, p);
		p = c;
		c = n;
		i++;
	}
	// Prepare to hold the sliced list.
	scouple *nl = createlist();
	guilt(nl, "empty list creation for slice failed", l, NULL);
	initlist(nl, isatomic(l));
	// Initalize the meta for sliced list.
	meta *nlm = nl->m;
	guilt(nlm, "meta creation for slice failed", l, nl);
	nlm->dops = m->dops;
	dataops dops = nlm->dops;
	nlm->mid = nlm->tail = nlm->head = nl;
	nlm->numnodes = 1;
	// Fill the data for the first node of the sliced list.
	nl->d = dops.copydata(c->d);
	guilt(nl->d, "copying data for a node in slice failed;"
			" slice might be incomplete\n", l, nlm->head);
	// Steap ahead of the node at the start.
	scouple *n = xor(c->next, p);
	p = c;
	c = n;
	scouple *pp = nl;
	i++; // Move to second node of the sliced list.
	// Start copying the remaining nodes until end.
	while (i <= end) {
		scouple *nn = calloc(sizeof *nn);
		guilt(nn, "new node creation for sliced list failed;"
				" slice might be incomplete; calloc\n", l, nlm->head);
		nn->m = nlm;
		nn->d = dops.copydata(c->d);
		if (!nn->d) {
			free(nn);
			nn = NULL;
			advice("copying data failed for a node in sliced listl"
				" slice might be incomplete");
			break;
		}
		nlm->tail = nn;
		nlm->numnodes++;
		bool odd = nlm->numnodes & 0x1;
		if (odd) {
			scouple *midn = xor(nlm->mid->next, nlm->midp);
			nlm->midp = nlm->mid;
			nlm->mid = midn;
		}
		// Maintain the (prev ^ next) relation for the sliced list.
		nn->next = pp;
		if (pp) {
			pp->next = xor(pp->next, nn);
		}
		pp = nn;
		// Move on to the next node in the main list.
		scouple *n = xor(c->next, p);
		p = c;
		c = n;
		i++;
	}
	peaceout(l);
	return nlm->head;
}

//
// Forms a braid by using the two lists as the strands with the first
// list as the first strand.
//
scouple *braid(scouple *l1, scouple *l2)
{
	print("Braiding . . .\n");
	metabolic(l1, NULL);
	metabolic(l2, NULL);
	meditate(l1);
	meditate(l2);
	meta *m1 = l1->m;
	meta *m2 = l2->m;
	scouple *c1 = m1->head;
	scouple *c2 = m2->head;
	scouple *p1 = NULL;
	scouple *p2 = NULL;
	// Replace the shorter list's meta with that of the longer.
	bool use1 = m1->numnodes > m2->numnodes;
	if (use1) {
		m1->numnodes += m2->numnodes;
		replacemeta(l2, l1);
	} else {
		m2->numnodes += m1->numnodes;
		replacemeta(l1, l2);
		m2->head = m1->head;
	}
	//
	// Form the braid as shown in the example below.
	//	List 2 : 5 ~> 6 ~> 7 ~> 8 ~> 9 ~> 10 ~> 11
	//	List 1 : 1 ~> 2 ~> 3 ~> 4
	//	Braid  : 1 ~> 5 ~> 2 ~> 6 ~> 3 ~> 7 ~> 4 ~> 8 ~> 9 ~> 10 ~> 11
	//
	while (c1 && c2) {
		scouple *n1 = xor(c1->next, p1);
		scouple *n2 = xor(c2->next, p2);
		c1->next = xor(p2, c2);
		c2->next = xor(c1, n1);
		p1 = c1;
		p2 = c2;
		c1 = n1;
		c2 = n2;
	}
	// We have two different logic here based on which list is shorter.
	// This is a consequence of having the first list as the first strand
	// of the braid.
	if (c1) {
		c1->next = xor(c1->next, p1);
		c1->next = xor(c1->next, p2);
	} else if (c2) {
		p2->next = xor(p1, c2);
	}
	fixmid(l1, false);
	if (use1) {
		peaceout(usenthrow(scouple, m, m2));
		peaceout(l1);
		free(m2);
	} else {
		peaceout(l2);
		peaceout(usenthrow(scouple, m, m1));
		free(m1);
	}
	return l1->m->head;
}

//
// Spiralifies the given list.
//
scouple *spiralify(scouple *l)
{
	print("Sprialifying list . . .\n");
	metabolic(l, NULL);
	meditate(l);
	meta *m = l->m;
	int numnodes = m->numnodes;
	if (numnodes <= 1) {
		return m->head;
	}
	scouple *f = m->head;
	scouple *fp = NULL;
	scouple *b = m->tail;
	scouple *bp = NULL;
	int i = 1;
	int numloops = numnodes / 2;
	bool even = !(numnodes & 0x1);
	scouple *midn = xor(m->mid->next, m->midp);
	m->tail = even ? midn : m->mid;
	int midi = numloops / 2;
	//
	// Form the spiral as shown in the below example.
	//	__________________________________
	//	| 				 |
	//	| 	________________	 |
	//	|	|		|	 |
	//	|	|		V	 V
	//	1	2	3 	4	 5
	//		^	^_______|	 |
	//		|			 |
	//		|________________________|
	//
	while (i <= numloops) {
		// Retail spiral shape.
		scouple *fn = xor(f->next, fp);
		scouple *bn = xor(b->next, bp);
		// Form the (prev ^ next) relation.
		f->next = xor(b, bp);
		b->next = xor(f, fn);
		// Save cycles and update mid(p) here!
		if (i == midi) {
			bool odd = midi & 0x1;
			if (odd) {
				m->midp = fn;
				m->mid = bn;
			} else {
				m->midp = b;
				m->mid = fn;
			}
		}
		// Move front and back pointers towards each other.
		fp = f;
		f = fn;
		bp = b;
		b = bn;
		i++;
	}
	// Even number of nodes need to be
	// differentiated w.r.t last node.
	if (even) {
		bp->next = b;
	} else {
		b->next = bp;
	}
	return m->head;
}

//
// Simple list is created without (prev ^ next) relation.
// * Caller is responsible to clean it up using destroysimplelist().
// * Simple list thus created shall only be printed using printsimplelist().
// * Meta/data semantics of simplified list remain same as the coupled list.
//
scouple *simplifylist(scouple *l)
{
	print("Simplifying list . . .\n");
	metabolic(l, NULL);
	meditate(l);
	meta *lm = l->m;
	scouple *c = lm->head;
	scouple *p = NULL;
	scouple *cpp = NULL;
	meta *m = calloc(sizeof *m);
	guilt(m, "creating meta for simplified list failed; calloc", l, NULL);
	m->dops = lm->dops;
	while (c) {
		scouple *cp = calloc(sizeof *cp);
		if (!cp) {
			advice("simplified list may not be complete; calloc");
			break;
		}
		cp->m = m;
		cp->d = lm->dops.copydata(c->d);
		if (!cp->d) {
			free(cp);
			cp = NULL;
			advice("simplified list may not be complete; calloc");
			break;
		}
		m->numnodes++;
		bool odd = m->numnodes & 0x1;
		if (!m->head) {
			m->mid = m->head = cp;
		} else if (odd) {
			m->midp = m->mid;
			m->mid = m->mid->next;
		}
		m->tail = cp;
		if (cpp) {
			cpp->next = cp;
		}
		cpp = cp;
		scouple *n = xor(c->next, p);
		p = c;
		c = n;
	}
	if (!m->head) {
		// Not even one node.
		free(m);
		return NULL;
	}
	peaceout(l);
	return m->head;
}



