typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

#define NALLOC 1024

static Header *morecore(unsigned nu);
void *m_alloc(unsigned nbytes);
void free(void *ap);