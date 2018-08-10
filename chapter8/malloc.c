#include <stdio.h>
#include <errno.h>
#include "malloc.h"

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));
    return freep;
}

void *m_alloc(unsigned nbytes)
{
    if (nbytes == 0)
        return NULL;

    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

void free(void *ap)
{
    Header *bp, *p;
    bp = (Header *)ap - 1;

    //find the right place for the block
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            //the block to be freed is on the right side or left side
            break;
    
    if (bp + bp->s.size == p->s.ptr) {
        //in middle and can be combined with the right one
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        //can be combined with the left one
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else 
        p->s.ptr = bp;
    freep = p;
}

void *c_alloc(size_t n, size_t size)
{
    void *ret;
    char *ptr;
    size_t size_in_bytes = n * size;
    ptr = ret = m_alloc(size_in_bytes);
    if (ret == NULL)
        return NULL;
    while (size_in_bytes--)
        *ptr++ = 0;
    return ret;
}

int main()
{
    if (errno != 0)
        printf("err:%d\n", errno);
    errno = 0;
    int *a;
    a = c_alloc(10, sizeof(int));

    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
}
