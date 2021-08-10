/***
*heap.h - Heap code include file
*
*       Copyright (c) 1988-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Contains information needed by the C library heap code.
*
*       [Internal]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_HEAP
#define _INC_HEAP

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <cruntime.h>


/* Define __cdecl for non-Microsoft compilers */

#if (!defined (_MSC_VER) && !defined (__cdecl))
#define __cdecl
#endif  /* (!defined (_MSC_VER) && !defined (__cdecl)) */

/*
 * Heap block descriptor
 */

struct _block_descriptor {
        struct _block_descriptor *pnextdesc;    /* ptr to next descriptor */
        void *pblock;               /* ptr to memory block */
};

#define _BLKDESC    struct _block_descriptor
#define _PBLKDESC   struct _block_descriptor *


/*
 * Useful constants
 */

/*
 * Unit of allocation. All allocations are of size n * _GRANULARITY. Note
 * that _GRANULARITY must be a power of 2, or it cannot be used with the
 * _ROUND2 macro.
 */
#if defined (_M_IA64)
#define _GRANULARITY    8
#else  /* defined (_M_IA64) */
#define _GRANULARITY    4
#endif  /* defined (_M_IA64) */

/*
 * Size of the header in a memory block. Note that we must have
 * sizeof(void *) <= _HDRSIZE so the header is big enough to hold a pointer
 * to the descriptor.
 */

#define _HDRSIZE    1 * _GRANULARITY

/* _heapchk/_heapset parameter */
#define _HEAP_NOFILL    0x7FFFFFF


/*
 * Descriptor status values
 */

#define _INUSE      0
#define _FREE       1
#define _DUMMY      2


#if _INUSE != 0
#error *** Heap code assumes _INUSE value is 0! ***
#endif  /* _INUSE != 0 */


/*
 * Macros for manipulating heap memory block descriptors
 *      stat = one of the status values
 *      addr = user-visible address of a heap block
 */

#define _STATUS_MASK    0x3 /* last 2 bits are status */

#define _ADDRESS(pdesc)     ( (void *) ((unsigned)((pdesc)->pblock) & \
                    (~_STATUS_MASK)) )
#define _STATUS(pdesc)      ( (unsigned) ((unsigned)((pdesc)->pblock) & \
                    _STATUS_MASK) )

#define _SET_INUSE(pdesc)   ( pdesc->pblock = (void *) \
                       ((unsigned)_ADDRESS(pdesc) | _INUSE) )
#define _SET_FREE(pdesc)    ( pdesc->pblock = (void *) \
                       ((unsigned)_ADDRESS(pdesc) | _FREE) )
#define _SET_DUMMY(pdesc)   ( pdesc->pblock = (void *) \
                       ((unsigned)_ADDRESS(pdesc) | _DUMMY) )

#define _IS_INUSE(pdesc)    ( _STATUS(pdesc) == _INUSE )
#define _IS_FREE(pdesc)     ( _STATUS(pdesc) == _FREE )
#define _IS_DUMMY(pdesc)    ( _STATUS(pdesc) == _DUMMY )

#define _BLKSIZE(pdesc)     ( (unsigned) ( \
                      (char *)_ADDRESS(pdesc->pnextdesc) - \
                      (char *)_ADDRESS(pdesc) - _HDRSIZE ) )

#define _MEMSIZE(pdesc)     ( (char *)_ADDRESS(pdesc->pnextdesc) - \
                      (char *)_ADDRESS(pdesc) )

#define _BACKPTR(addr)      ( *(_PBLKDESC*)((char *)(addr) - _HDRSIZE) )

#define _CHECK_PDESC(pdesc) ( (*(_PBLKDESC*) (_ADDRESS(pdesc))) == pdesc )

#define _CHECK_BACKPTR(addr)    ( ((char *)(_BACKPTR(addr)->pblock) + _HDRSIZE) \
                    == addr)


/*
 * Heap descriptor
 */

struct _heap_desc_ {

        _PBLKDESC pfirstdesc;   /* pointer to first descriptor */
        _PBLKDESC proverdesc;   /* rover pointer */
        _PBLKDESC emptylist;    /* pointer to empty list */

        _BLKDESC  sentinel; /* Sentinel block for end of heap list */

};

extern struct _heap_desc_ _heap_desc;

/*
 * Region descriptor and heap grow data
 */

struct _heap_region_ {
        void * _regbase;    /* base address of region */
        unsigned _currsize; /* current size of region */
        unsigned _totalsize;    /* total size of region */
        };

#define _heap_growsize _amblksiz

extern unsigned int _heap_resetsize;
extern unsigned int _heap_regionsize;
extern unsigned int _heap_maxregsize;
extern struct _heap_region_ _heap_regions[];
extern void ** _heap_descpages;

#define _PAGESIZE_      0x1000      /* one page */

#define _SEGSIZE_       0x10000     /* one segment (i.e., 64 Kb) */

#define _HEAP_REGIONMAX     0x40        /* Max number of regions: 64 */
                                        /* For small memory systems: */
#define _HEAP_REGIONSIZE_S  0x4000      /* Initial region size (16K) */
#define _HEAP_MAXREGSIZE_S  0x1000000   /* Maximum region size (16M) */
                                        /* For large memory systems: */
#define _HEAP_REGIONSIZE_L  0x100000    /* Initial region size  (1M) */
#define _HEAP_MAXREGSIZE_L  0x1000000   /* Maximum region size (16M) */

#define _HEAP_GROWSIZE      0x10000     /* Default grow increment (64K) */

#define _HEAP_GROWMIN       _PAGESIZE_  /* Minimum grow inc (1 page) */
#define _HEAP_GROWSTART     _PAGESIZE_  /* Startup grow increment */
#define _HEAP_COALESCE      -1      /* Coalesce heap value */

#define _HEAP_EMPTYLIST_SIZE    (1 * _PAGESIZE_)

/*
 * Values returned by _heap_findaddr() routine
 */

#define _HEAPFIND_EXACT     0   /* found address exactly */
#define _HEAPFIND_WITHIN    1   /* address is within a block */
#define _HEAPFIND_BEFORE    -1  /* address before beginning of heap */
#define _HEAPFIND_AFTER     -2  /* address after end of heap */
#define _HEAPFIND_EMPTY     -3  /* address not found: empty heap */

/*
 * Arguments to _heap_param
 */

#define _HP_GETPARAM    0       /* get heap parameter value */
#define _HP_SETPARAM    1       /* set heap parameter value */

#define _HP_AMBLKSIZ    1       /* get/set _amblksiz value (aka */
#define _HP_GROWSIZE    _HP_AMBLKSIZ    /* _heap_growsize */
#define _HP_RESETSIZE   2       /* get/set _heap_resetsize value */


/*
 * Macros to round numbers
 *
 * _ROUND2 = rounds a number up to a power of 2
 * _ROUND = rounds a number up to any other numer
 *
 * n = number to be rounded
 * pow2 = must be a power of two value
 * r = any number
 */

#define _ROUND2(n,pow2) \
        ( ( n + pow2 - 1) & ~(pow2 - 1) )

#define _ROUND(n,r) \
        ( ( (n/r) + ((n%r)?1:0) ) * r)

/*

   Macros for accessing heap descriptor lists:

        _PUTEMPTY(x) = Puts an empty heap desc on the empty list

        (x = _PBLKDESC = pointer to heap block descriptor)
*/

#ifdef _DEBUG

#define _PUTEMPTY(x) \
{                               \
        (x)->pnextdesc = _heap_desc.emptylist;      \
                                \
        (x)->pblock = NULL;             \
                                \
        _heap_desc.emptylist = (x);         \
}

#else  /* _DEBUG */

#define _PUTEMPTY(x) \
{                               \
        (x)->pnextdesc = _heap_desc.emptylist;      \
                                \
        _heap_desc.emptylist = (x);         \
}

#endif  /* _DEBUG */


/*
 * Macros for finding the next 64 Kb boundary from a pointer
 */

#define _NXTSEGBNDRY(p)     ((void *)((unsigned)(p) & 0xffff0000 + 0x10000))

#define _DISTTOBNDRY(p)     ((unsigned)(0x10000 - (0x0000ffff & (unsigned)(p))))


/*
 * Define size_t type (if necessary)
 */

#if !defined (_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#define _W64 __w64
#else  /* !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300 */
#define _W64
#endif  /* !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300 */
#endif  /* !defined (_W64) */

#ifndef _SIZE_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64    size_t;
#else  /* _WIN64 */
typedef _W64 unsigned int   size_t;
#endif  /* _WIN64 */
#define _SIZE_T_DEFINED
#endif  /* _SIZE_T_DEFINED */


/*
 * Prototypes
 */

void * __cdecl _nh_malloc(size_t, int);
void * __cdecl _heap_alloc(size_t);
void * __cdecl _flat_malloc(size_t);
_PBLKDESC __getempty(void);
void __cdecl _heap_abort(void);
int __cdecl _heap_addblock(void *, unsigned int);


void __cdecl _heap_free_region(int);
int __cdecl _heap_findaddr(void *, _PBLKDESC *);
int __cdecl _heap_grow(unsigned int);
int __cdecl _heap_grow_region(unsigned, size_t);
int __cdecl _heap_init(void);

int __cdecl _heap_param(int, int, void *);

_PBLKDESC __cdecl _heap_search(unsigned size);
_PBLKDESC __cdecl _heap_split_block(_PBLKDESC, size_t);

#ifdef _DEBUG
void __cdecl _heap_print_all(void);
void __cdecl _heap_print_regions(void);
void __cdecl _heap_print_desc(void);
void __cdecl _heap_print_emptylist(void);
void __cdecl _heap_print_heaplist(void);
#endif  /* _DEBUG */


/*
 * Prototypes and macros for multi-thread support
 */

#ifdef _MT

void __cdecl _free_lk(void *);
size_t __cdecl _msize_lk(void *);
size_t __cdecl _heapused_lk(size_t *pUsed, size_t *pFree);

#ifdef _DEBUG
void __cdecl _heap_print_regions_lk(void);
void __cdecl _heap_print_desc_lk(void);
void __cdecl _heap_print_emptylist_lk(void);
void __cdecl _heap_print_heaplist_lk(void);
#endif  /* _DEBUG */

#else  /* _MT */

#define _free_lk(p) free(p)
#define _msize_lk(p)    _msize(p)

#ifdef _DEBUG
#define _heap_print_regions_lk()    _heap_print_regions()
#define _heap_print_desc_lk()       _heap_print_desc()
#define _heap_print_emptylist_lk()  _heap_print_emptylist()
#define _heap_print_heaplist_lk()   _heap_print_heaplist()
#endif  /* _DEBUG */

#endif  /* _MT */


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_HEAP */
