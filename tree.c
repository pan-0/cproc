#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "util.h"
#include "null.h"

NULLABILITY_NNBDs

#define MAXH (sizeof(void *) * 8 * 3 / 2)

static inline int
height(struct treenode *nullable n) {
	return n ? unnull(n)->height : 0;
}

static int
rot(void **p, struct treenode *x, int dir /* deeper side */)
{
	struct treenode *z;
	struct treenode *y = unnull(x->child[dir]);
	struct treenode *nullable nz = y->child[!dir];
	int hx = x->height;
	int hz = height(nz);
	if (hz > height(y->child[dir])) {
		z = unnull(nz);
		/*
		 *   x
		 *  / \ dir          z
		 * A   y            / \
		 *    / \   -->    x   y
		 *   z   D        /|   |\
		 *  / \          A B   C D
		 * B   C
		 */
		x->child[dir] = z->child[!dir];
		y->child[!dir] = z->child[dir];
		z->child[!dir] = x;
		z->child[dir] = y;
		x->height = hz;
		y->height = hz;
		z->height = hz + 1;
	} else {
		/*
		 *   x               y
		 *  / \             / \
		 * A   y    -->    x   D
		 *    / \         / \
		 *   z   D       A   z
		 */
		x->child[dir] = nz;
		y->child[!dir] = x;
		x->height = hz + 1;
		y->height = hz + 2;
		z = y;
	}
	*p = z;
	return z->height - hx;
}

/* balance *p, return 0 if height is unchanged.  */
static int balance(void **p)
{
	struct treenode *n = *p;
	int h0 = height(n->child[0]);
	int h1 = height(n->child[1]);
	if (h0 - h1 + 1u < 3u) {
		int old = n->height;
		n->height = h0 < h1 ? h1 + 1 : h0 + 1;
		return n->height - old;
	}
	return rot(p, n, h0<h1);
}

void *
treeinsert(void *nullable *root, unsigned long long key, size_t sz)
{
	void **a[MAXH];
	struct treenode *r, *nullable nn = *root;
	int i = 0;

	a[i++] = root;
	while (nn) {
		struct treenode *n = unnull(nn);
		if (key == n->key) {
			n->new = false;
			return n;
		}
		a[i++] = &n->child[key > n->key];
		nn = n->child[key > n->key];
	}
	assert(sz > sizeof(*r));
	r = xmalloc(sz);
	r->key = key;
	r->child[0] = r->child[1] = 0;
	r->height = 1;
	/* insert new node, rebalance ancestors.  */
	*a[--i] = r;
	while (i && balance(a[--i]))
		;
	r->new = true;
	return r;
}
