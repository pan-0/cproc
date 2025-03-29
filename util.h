#include "null.h"

struct list {
	struct list *prev, *next;
};

struct array {
	void *val;
	size_t len, cap;
};

struct treenode {
	unsigned long long key;
	void *child[2];
	int height;
	bool new;  /* set by treeinsert if this node was newly allocated */
};

extern char *argv0;

#define LEN(a) (sizeof(a) / sizeof((a)[0]))
#define ALIGNDOWN(x, n) ((x) & -(n))
#define ALIGNUP(x, n) ALIGNDOWN((x) + (n) - 1, n)

void warn(const char *, ...);
void fatal(const char *fmt, ...);

void *reallocarray(void *, size_t, size_t);
void *xreallocarray(void *, size_t, size_t);
void *nonnull xmalloc(size_t);

char *progname(char *, char *);

void listinsert(struct list *, struct list *);
void listremove(struct list *);
#define listelement(list, type, member) (type *)((char *)list - offsetof(type, member))

void *nonnull arrayadd(struct array *, size_t);
void arrayaddptr(struct array *, void *);
void arrayaddbuf(struct array *, const void *, size_t);
void *arraylast(struct array *, size_t);
#define arrayforeach(a, m) for (m = (a)->val; m != (void *)((char *)((a)->val) + (a)->len); ++m)

/* map */

struct map {
	size_t len, cap;
	struct mapkey *keys;
	void **vals;
};

struct mapkey {
	unsigned long hash;
	const void *str;
	size_t len;
};

void mapkey(struct mapkey *, const void *, size_t);
void mapinit(struct map *, size_t);
void mapfree(struct map *, void(void *));
void **mapput(struct map *, struct mapkey *);
void *mapget(struct map *, struct mapkey *);

/* tree */

void *nonnull treeinsert(void *nullable *nonnull, unsigned long long, size_t);
