/*
 * linux/include/asm-m68k/io.h 
 *
 * 4/1/00 RZ: - rewritten to avoid clashes between ISA/PCI and other
 *              IO access
 *            - added Q40 support
 *            - added skeleton for GG-II and Amiga PCMCIA
 * 2/3/01 RZ: - moved a few more defs into raw_io.h
 *
 * inX/outX/readX/writeX should not be used by any driver unless it does
 * ISA or PCI access. Other drivers should use function defined in raw_io.h
 * or define its own macros on top of these.
 *
 *    inX(),outX()              are for PCI and ISA I/O
 *    readX(),writeX()          are for PCI memory
 *    isa_readX(),isa_writeX()  are for ISA memory
 *
 * moved mem{cpy,set}_*io inside CONFIG_PCI
 */

#ifndef _IO_H
#define _IO_H

#ifdef __KERNEL__

#include <linux/config.h>
#include <asm/raw_io.h>
#include <asm/virtconvert.h>


#ifdef CONFIG_ATARI
#include <asm/atarihw.h>
#endif


/*
 * IO/MEM definitions for various ISA bridges
 */


#ifdef CONFIG_Q40

#define q40_isa_io_base  0xff400000
#define q40_isa_mem_base 0xff800000

#define Q40_ISA_IO_B(ioaddr) (q40_isa_io_base+1+4*((unsigned long)(ioaddr)))
#define Q40_ISA_IO_W(ioaddr) (q40_isa_io_base+  4*((unsigned long)(ioaddr)))
#define Q40_ISA_MEM_B(madr)  (q40_isa_mem_base+1+4*((unsigned long)(madr)))
#define Q40_ISA_MEM_W(madr)  (q40_isa_mem_base+  4*((unsigned long)(madr)))

#define MACH_HAS_ISA 1
#endif /* Q40 */

/* GG-II Zorro to ISA bridge */
#ifdef CONFIG_GG2

extern unsigned long gg2_isa_base;
#define GG2_ISA_IO_B(ioaddr) (gg2_isa_base+1+((unsigned long)(ioaddr)*4))
#define GG2_ISA_IO_W(ioaddr) (gg2_isa_base+  ((unsigned long)(ioaddr)*4))
#define GG2_ISA_MEM_B(madr)  (gg2_isa_base+1+(((unsigned long)(madr)*4) & 0xfffff))
#define GG2_ISA_MEM_W(madr)  (gg2_isa_base+  (((unsigned long)(madr)*4) & 0xfffff))

#ifndef MACH_HAS_ISA
#define MACH_HAS_ISA 1
#else 
#undef MACH_HAS_ISA
#define MACH_HAS_ISA m
#endif
#endif /* GG2 */

#ifdef CONFIG_AMIGA_PCMCIA
#include <asm/amigayle.h>

#define AG_ISA_IO_B(ioaddr) ( GAYLE_IO+(ioaddr)+(((ioaddr)&1)*GAYLE_ODD) )
#define AG_ISA_IO_W(ioaddr) ( GAYLE_IO+(ioaddr) )

#ifndef MACH_HAS_ISA
#define MACH_HAS_ISA 1
#else 
#undef MACH_HAS_ISA
#define MACH_HAS_ISA m
#endif
#endif /* AMIGA_PCMCIA */



#ifdef MACH_HAS_ISA

#define Q40_ISA (1)
#define GG2_ISA (2)
#define AG_ISA  (3)

#if defined(CONFIG_Q40) && MACH_HAS_ISA==1
#define ISA_TYPE Q40_ISA
#define ISA_SEX  0
#endif
#if defined(CONFIG_AMIGA_PCMCIA) && MACH_HAS_ISA==1
#define ISA_TYPE AG_ISA
#define ISA_SEX  1
#endif 
#if defined(CONFIG_GG2) && MACH_HAS_ISA==1
#define ISA_TYPE GG2_ISA
#define ISA_SEX  0
#endif

#ifdef CONFIG_ISA
extern int isa_type;
extern int isa_sex;

#define ISA_TYPE isa_type
#define ISA_SEX  isa_sex
#endif

/*
 * define inline addr translation functions. Normally only one variant will
 * be compiled in so the case statement will be optimised away
 */

static inline unsigned long isa_itb(long addr)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case Q40_ISA: return Q40_ISA_IO_B(addr);
#endif
#ifdef CONFIG_GG2
    case GG2_ISA: return GG2_ISA_IO_B(addr);
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case AG_ISA: return AG_ISA_IO_B(addr);
#endif
    default: return 0; /* avoid warnings, just in case */
    }
}
static inline unsigned long isa_itw(long addr)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case Q40_ISA: return Q40_ISA_IO_W(addr);
#endif
#ifdef CONFIG_GG2
    case GG2_ISA: return GG2_ISA_IO_W(addr);
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case AG_ISA: return AG_ISA_IO_W(addr);
#endif
    default: return 0; /* avoid warnings, just in case */
    }
}
static inline unsigned long isa_mtb(long addr)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case Q40_ISA: return Q40_ISA_MEM_B(addr);
#endif
#ifdef CONFIG_GG2
    case GG2_ISA: return GG2_ISA_MEM_B(addr);
#endif
      /* FIXME: any ISA mem mapping for PCMCIA? */
    default: return 0; /* avoid warnings, just in case */
    }
}
static inline unsigned long isa_mtw(long addr)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case Q40_ISA: return Q40_ISA_MEM_W(addr);
#endif
#ifdef CONFIG_GG2
    case GG2_ISA: return GG2_ISA_MEM_W(addr);
#endif
    default: return 0; /* avoid warnings, just in case */
    }
}


#define isa_inb(port)      in_8(isa_itb(port))
#define isa_inw(port)      (ISA_SEX ? in_be16(isa_itw(port)) : in_le16(isa_itw(port)))
#define isa_outb(val,port) out_8(isa_itb(port),(val))
#define isa_outw(val,port) (ISA_SEX ? out_be16(isa_itw(port),(val)) : out_le16(isa_itw(port),(val)))

#define isa_readb(p)       in_8(isa_mtb(p))
#define isa_readw(p)       in_le16(isa_mtw(p))
#define isa_writeb(val,p)  out_8(isa_mtb(p),(val))
#define isa_writew(val,p)  out_le16(isa_mtw(p),(val))

#define isa_inb_p(p)      ({unsigned char v=isa_inb(p);isa_outb(0,0x80);v;})
#define isa_outb_p(v,p)   ({isa_outb((v),(p));isa_outb(0,0x80);})

#define isa_insb(port, buf, nr) raw_insb(isa_itb(port), (buf), (nr))
#define isa_outsb(port, buf, nr) raw_outsb(isa_itb(port), (buf), (nr))

#define isa_insw(port, buf, nr)     \
       (ISA_SEX ? raw_insw(isa_itw(port), (buf), (nr)) :    \
                  raw_insw_swapw(isa_itw(port), (buf), (nr)))

#define isa_outsw(port, buf, nr)    \
       (ISA_SEX ? raw_outsw(isa_itw(port), (buf), (nr)) :  \
                  raw_outsw_swapw(isa_itw(port), (buf), (nr)))
#endif  /* MACH_HAS_ISA */


#if defined(CONFIG_ISA) && !defined(CONFIG_PCI) 
#define inb     isa_inb
#define inb_p   isa_inb_p
#define outb    isa_outb
#define outb_p  isa_outb_p
#define inw     isa_inw
#define outw    isa_outw
#define inl     isa_inw
#define outl    isa_outw
#define insb    isa_insb
#define insw    isa_insw
#define outsb   isa_outsb
#define outsw   isa_outsw
#endif /* MACH_HAS_ISA */


#if defined(CONFIG_PCI)

#define inl(port)       in_le32(port)
#define outl(val,port)  out_le32((port),(val))

#define readb(addr)  in_8(addr)
#define readw(addr)  in_le16(addr)
#define readl(addr)  in_le32(addr)

#define writeb(val,addr)  out_8((addr),(val))
#define writew(val,addr)  out_le16((addr),(val))
#define writel(val,addr)  out_le32((addr),(val))


#ifndef CONFIG_ISA
#define inb(port)      in_8(port)
#define outb(val,port) out_8((port),(val))
#define inw(port)      in_le16(port)
#define outw(val,port) out_le16((port),(val))

#else
/*
 * kernel with both ISA and PCI compiled in, those have 
 * conflicting defs for in/out. Simply consider port < 1024 
 * ISA and everything else PCI
 */
#define inb(port) ((port)<1024 ? isa_inb(port) : in_8(port))
#define inb_p(port) ((port)<1024 ? isa_inb_p(port) : in_8(port))
#define inw(port) ((port)<1024 ? isa_inw(port) : in_le16(port))

#define outb(val,port) ((port)<1024 ? isa_outb((val),(port)) : out_8((port),(val)))
#define outb_p(val,port) ((port)<1024 ? isa_outb_p((val),(port)) : out_8((port),(val)))
#define outw(val,port) ((port)<1024 ? isa_outw((val),(port)) : out_le16((port),(val)))
#endif
#endif /* CONFIG_PCI */


/* Values for nocacheflag and cmode */
#define IOMAP_FULL_CACHING		0
#define IOMAP_NOCACHE_SER		1
#define IOMAP_NOCACHE_NONSER		2
#define IOMAP_WRITETHROUGH		3

extern void iounmap(void *addr);

extern void *__ioremap(unsigned long physaddr, unsigned long size,
		       int cacheflag);
extern void __iounmap(void *addr, unsigned long size);

extern inline void *ioremap(unsigned long physaddr, unsigned long size)
{
	return __ioremap(physaddr, size, IOMAP_NOCACHE_SER);
}
extern inline void *ioremap_nocache(unsigned long physaddr, unsigned long size)
{
	return __ioremap(physaddr, size, IOMAP_NOCACHE_SER);
}
extern inline void *ioremap_writethrough(unsigned long physaddr,
					 unsigned long size)
{
	return __ioremap(physaddr, size, IOMAP_WRITETHROUGH);
}
extern inline void *ioremap_fullcache(unsigned long physaddr,
				      unsigned long size)
{
	return __ioremap(physaddr, size, IOMAP_FULL_CACHING);
}

extern void iounmap(void *addr);

/* Nothing to do */

#define dma_cache_inv(_start,_size)		do { } while (0)
#define dma_cache_wback(_start,_size)		do { } while (0)
#define dma_cache_wback_inv(_start,_size)	do { } while (0)

#ifndef CONFIG_SUN3
#define IO_SPACE_LIMIT 0xffff
#else
#define IO_SPACE_LIMIT 0x0fffffff
#endif

#endif /* __KERNEL__ */
#endif /* _IO_H */
