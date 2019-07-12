/* Atomic operations usable in machine independent code */
#ifndef _LINUX_ATOMIC_H
#define _LINUX_ATOMIC_H
#include <asm/atomic.h>
#include <asm/barrier.h>

/*
 * Relaxed variants of xchg, cmpxchg and some atomic operations.
 *
 * We support four variants:
 *
 * - Fully ordered: The default implementation, no suffix required.
 * - Acquire: Provides ACQUIRE semantics, _acquire suffix.
 * - Release: Provides RELEASE semantics, _release suffix.
 * - Relaxed: No ordering guarantees, _relaxed suffix.
 *
 * For compound atomics performing both a load and a store, ACQUIRE
 * semantics apply only to the load and RELEASE semantics only to the
 * store portion of the operation. Note that a failed cmpxchg_acquire
 * does -not- imply any memory ordering constraints.
 *
 * See Documentation/memory-barriers.txt for ACQUIRE/RELEASE definitions.
 */

#ifndef atomic_read_acquire
#define  atomic_read_acquire(v)		smp_load_acquire(&(v)->counter)
#endif

#ifndef atomic_set_release
#define  atomic_set_release(v, i)	smp_store_release(&(v)->counter, (i))
#endif

/*
 * The idea here is to build acquire/release variants by adding explicit
 * barriers on top of the relaxed variant. In the case where the relaxed
 * variant is already fully ordered, no additional barriers are needed.
 */
#define __atomic_op_acquire(op, args...)				\
({									\
	typeof(op##_relaxed(args)) __ret  = op##_relaxed(args);		\
	smp_mb__after_atomic();						\
	__ret;								\
})
#define __atomic_op_release(op, args...)				\
({									\
	smp_mb__before_atomic();					\
	op##_relaxed(args);						\
})
#define __atomic_op_fence(op, args...)					\
({									\
	typeof(op##_relaxed(args)) __ret;				\
	smp_mb__before_atomic();					\
	__ret = op##_relaxed(args);					\
	smp_mb__after_atomic();						\
	__ret;								\
})

/* atomic_add_return_relaxed */
#ifndef atomic_add_return_relaxed
#define  atomic_add_return_relaxed	atomic_add_return
#define  atomic_add_return_acquire	atomic_add_return
#define  atomic_add_return_release	atomic_add_return

#else /* atomic_add_return_relaxed */

#ifndef atomic_add_return_acquire
#define  atomic_add_return_acquire(...)					\
	__atomic_op_acquire(atomic_add_return, __VA_ARGS__)
#endif

#ifndef atomic_add_return_release
#define  atomic_add_return_release(...)					\
	__atomic_op_release(atomic_add_return, __VA_ARGS__)
#endif

#ifndef atomic_add_return
#define  atomic_add_return(...)						\
	__atomic_op_fence(atomic_add_return, __VA_ARGS__)
#endif
#endif /* atomic_add_return_relaxed */

#ifndef atomic_inc
#define atomic_inc(v)			atomic_add(1, (v))
#endif

/* atomic_inc_return_relaxed */
#ifndef atomic_inc_return_relaxed

#ifndef atomic_inc_return
#define atomic_inc_return(v)		atomic_add_return(1, (v))
#define atomic_inc_return_relaxed(v)	atomic_add_return_relaxed(1, (v))
#define atomic_inc_return_acquire(v)	atomic_add_return_acquire(1, (v))
#define atomic_inc_return_release(v)	atomic_add_return_release(1, (v))
#else /* atomic_inc_return */
#define  atomic_inc_return_relaxed	atomic_inc_return
#define  atomic_inc_return_acquire	atomic_inc_return
#define  atomic_inc_return_release	atomic_inc_return
#endif /* atomic_inc_return */

#else /* atomic_inc_return_relaxed */

#ifndef atomic_inc_return_acquire
#define  atomic_inc_return_acquire(...)					\
	__atomic_op_acquire(atomic_inc_return, __VA_ARGS__)
#endif

#ifndef atomic_inc_return_release
#define  atomic_inc_return_release(...)					\
	__atomic_op_release(atomic_inc_return, __VA_ARGS__)
#endif

#ifndef atomic_inc_return
#define  atomic_inc_return(...)						\
	__atomic_op_fence(atomic_inc_return, __VA_ARGS__)
#endif
#endif /* atomic_inc_return_relaxed */

/* atomic_sub_return_relaxed */
#ifndef atomic_sub_return_relaxed
#define  atomic_sub_return_relaxed	atomic_sub_return
#define  atomic_sub_return_acquire	atomic_sub_return
#define  atomic_sub_return_release	atomic_sub_return

#else /* atomic_sub_return_relaxed */

#ifndef atomic_sub_return_acquire
#define  atomic_sub_return_acquire(...)					\
	__atomic_op_acquire(atomic_sub_return, __VA_ARGS__)
#endif

#ifndef atomic_sub_return_release
#define  atomic_sub_return_release(...)					\
	__atomic_op_release(atomic_sub_return, __VA_ARGS__)
#endif

#ifndef atomic_sub_return
#define  atomic_sub_return(...)						\
	__atomic_op_fence(atomic_sub_return, __VA_ARGS__)
#endif
#endif /* atomic_sub_return_relaxed */
/* atomic_xchg_relaxed */
#ifndef atomic_xchg_relaxed
#define  atomic_xchg_relaxed		atomic_xchg
#define  atomic_xchg_acquire		atomic_xchg
#define  atomic_xchg_release		atomic_xchg

#else /* atomic_xchg_relaxed */

#ifndef atomic_xchg_acquire
#define  atomic_xchg_acquire(...)					\
	__atomic_op_acquire(atomic_xchg, __VA_ARGS__)
#endif

#ifndef atomic_xchg_release
#define  atomic_xchg_release(...)					\
	__atomic_op_release(atomic_xchg, __VA_ARGS__)
#endif

#ifndef atomic_xchg
#define  atomic_xchg(...)						\
	__atomic_op_fence(atomic_xchg, __VA_ARGS__)
#endif
#endif /* atomic_xchg_relaxed */

/* atomic_cmpxchg_relaxed */
#ifndef atomic_cmpxchg_relaxed
#define  atomic_cmpxchg_relaxed		atomic_cmpxchg
#define  atomic_cmpxchg_acquire		atomic_cmpxchg
#define  atomic_cmpxchg_release		atomic_cmpxchg

#else /* atomic_cmpxchg_relaxed */

#ifndef atomic_cmpxchg_acquire
#define  atomic_cmpxchg_acquire(...)					\
	__atomic_op_acquire(atomic_cmpxchg, __VA_ARGS__)
#endif

#ifndef atomic_cmpxchg_release
#define  atomic_cmpxchg_release(...)					\
	__atomic_op_release(atomic_cmpxchg, __VA_ARGS__)
#endif

#ifndef atomic_cmpxchg
#define  atomic_cmpxchg(...)						\
	__atomic_op_fence(atomic_cmpxchg, __VA_ARGS__)
#endif
#endif /* atomic_cmpxchg_relaxed */
#ifndef atomic64_read_acquire
#define  atomic64_read_acquire(v)	smp_load_acquire(&(v)->counter)
#endif
#ifndef atomic64_set_release
#define  atomic64_set_release(v, i)	smp_store_release(&(v)->counter, (i))
#endif
/* atomic64_add_return_relaxed */
#ifndef atomic64_add_return_relaxed
#define  atomic64_add_return_relaxed	atomic64_add_return
#define  atomic64_add_return_acquire	atomic64_add_return
#define  atomic64_add_return_release	atomic64_add_return
#else /* atomic64_add_return_relaxed */
#ifndef atomic64_add_return_acquire
#define  atomic64_add_return_acquire(...)				\
	__atomic_op_acquire(atomic64_add_return, __VA_ARGS__)
#endif
#ifndef atomic64_add_return_release
#define  atomic64_add_return_release(...)				\
	__atomic_op_release(atomic64_add_return, __VA_ARGS__)
#endif
#ifndef atomic64_add_return
#define  atomic64_add_return(...)					\
	__atomic_op_fence(atomic64_add_return, __VA_ARGS__)
#endif
#endif /* atomic64_add_return_relaxed */
/* atomic64_sub_return_relaxed */
#ifndef atomic64_sub_return_relaxed
#define  atomic64_sub_return_relaxed	atomic64_sub_return
#define  atomic64_sub_return_acquire	atomic64_sub_return
#define  atomic64_sub_return_release	atomic64_sub_return
#else /* atomic64_sub_return_relaxed */
#ifndef atomic64_sub_return_acquire
#define  atomic64_sub_return_acquire(...)				\
	__atomic_op_acquire(atomic64_sub_return, __VA_ARGS__)
#endif
#ifndef atomic64_sub_return_release
#define  atomic64_sub_return_release(...)				\
	__atomic_op_release(atomic64_sub_return, __VA_ARGS__)
#endif
#ifndef atomic64_sub_return
#define  atomic64_sub_return(...)					\
	__atomic_op_fence(atomic64_sub_return, __VA_ARGS__)
#endif
#endif /* atomic64_sub_return_relaxed */
/* atomic64_xchg_relaxed */
#ifndef atomic64_xchg_relaxed
#define  atomic64_xchg_relaxed		atomic64_xchg
#define  atomic64_xchg_acquire		atomic64_xchg
#define  atomic64_xchg_release		atomic64_xchg
#else /* atomic64_xchg_relaxed */
#ifndef atomic64_xchg_acquire
#define  atomic64_xchg_acquire(...)					\
	__atomic_op_acquire(atomic64_xchg, __VA_ARGS__)
#endif
#ifndef atomic64_xchg_release
#define  atomic64_xchg_release(...)					\
	__atomic_op_release(atomic64_xchg, __VA_ARGS__)
#endif
#ifndef atomic64_xchg
#define  atomic64_xchg(...)						\
	__atomic_op_fence(atomic64_xchg, __VA_ARGS__)
#endif
#endif /* atomic64_xchg_relaxed */
/* atomic64_cmpxchg_relaxed */
#ifndef atomic64_cmpxchg_relaxed
#define  atomic64_cmpxchg_relaxed	atomic64_cmpxchg
#define  atomic64_cmpxchg_acquire	atomic64_cmpxchg
#define  atomic64_cmpxchg_release	atomic64_cmpxchg
#else /* atomic64_cmpxchg_relaxed */
#ifndef atomic64_cmpxchg_acquire
#define  atomic64_cmpxchg_acquire(...)					\
	__atomic_op_acquire(atomic64_cmpxchg, __VA_ARGS__)
#endif
#ifndef atomic64_cmpxchg_release
#define  atomic64_cmpxchg_release(...)					\
	__atomic_op_release(atomic64_cmpxchg, __VA_ARGS__)
#endif
#ifndef atomic64_cmpxchg
#define  atomic64_cmpxchg(...)						\
	__atomic_op_fence(atomic64_cmpxchg, __VA_ARGS__)
#endif
#endif /* atomic64_cmpxchg_relaxed */
/* cmpxchg_relaxed */
#ifndef cmpxchg_relaxed
#define  cmpxchg_relaxed		cmpxchg
#define  cmpxchg_acquire		cmpxchg
#define  cmpxchg_release		cmpxchg

#else /* cmpxchg_relaxed */

#ifndef cmpxchg_acquire
#define  cmpxchg_acquire(...)						\
	__atomic_op_acquire(cmpxchg, __VA_ARGS__)
#endif

#ifndef cmpxchg_release
#define  cmpxchg_release(...)						\
	__atomic_op_release(cmpxchg, __VA_ARGS__)
#endif

#ifndef cmpxchg
#define  cmpxchg(...)							\
	__atomic_op_fence(cmpxchg, __VA_ARGS__)
#endif
#endif /* cmpxchg_relaxed */

/* cmpxchg64_relaxed */
#ifndef cmpxchg64_relaxed
#define  cmpxchg64_relaxed		cmpxchg64
#define  cmpxchg64_acquire		cmpxchg64
#define  cmpxchg64_release		cmpxchg64

#else /* cmpxchg64_relaxed */

#ifndef cmpxchg64_acquire
#define  cmpxchg64_acquire(...)						\
	__atomic_op_acquire(cmpxchg64, __VA_ARGS__)
#endif

#ifndef cmpxchg64_release
#define  cmpxchg64_release(...)						\
	__atomic_op_release(cmpxchg64, __VA_ARGS__)
#endif

#ifndef cmpxchg64
#define  cmpxchg64(...)							\
	__atomic_op_fence(cmpxchg64, __VA_ARGS__)
#endif
#endif /* cmpxchg64_relaxed */

/* xchg_relaxed */
#ifndef xchg_relaxed
#define  xchg_relaxed			xchg
#define  xchg_acquire			xchg
#define  xchg_release			xchg

#else /* xchg_relaxed */

#ifndef xchg_acquire
#define  xchg_acquire(...)		__atomic_op_acquire(xchg, __VA_ARGS__)
#endif

#ifndef xchg_release
#define  xchg_release(...)		__atomic_op_release(xchg, __VA_ARGS__)
#endif

#ifndef xchg
#define  xchg(...)			__atomic_op_fence(xchg, __VA_ARGS__)
#endif
#endif /* xchg_relaxed */

/**
 * cmpwait - compare and wait for a variable to change
 * @ptr: pointer to the variable to wait on
 * @val: the value it should change from
 *
 * A simple constuct that waits for a variable to change from a known
 * value; some architectures can do this in hardware.
 */
#ifndef cmpwait
#define cmpwait(ptr, val) do {					\
	typeof (ptr) __ptr = (ptr);				\
	typeof (val) __val = (val);				\
	while (READ_ONCE(*__ptr) == __val)			\
		cpu_relax();					\
} while (0)
#endif

/**
 * smp_cond_load_acquire() - (Spin) wait for cond with ACQUIRE ordering
 * @ptr: pointer to the variable to wait on
 * @cond: boolean expression to wait for
 *
 * Equivalent to using smp_load_acquire() on the condition variable but employs
 * the control dependency of the wait to reduce the barrier on many platforms.
 *
 * Due to C lacking lambda expressions we load the value of *ptr into a
 * pre-named variable @VAL to be used in @cond.
 *
 * The control dependency provides a LOAD->STORE order, the additional RMB
 * provides LOAD->LOAD order, together they provide LOAD->{LOAD,STORE} order,
 * aka. ACQUIRE.
 */
#ifndef smp_cond_load_acquire
#define smp_cond_load_acquire(ptr, cond_expr) ({		\
	typeof(ptr) __PTR = (ptr);				\
	typeof(*ptr) VAL;					\
	for (;;) {						\
		VAL = READ_ONCE(*__PTR);			\
		if (cond_expr)					\
			break;					\
		cmpwait(__PTR, VAL);				\
	}							\
	smp_rmb(); /* ctrl + rmb := acquire */			\
	VAL;							\
})
#endif

/*
 * The idea here is to build acquire/release variants by adding explicit
 * barriers on top of the relaxed variant. In the case where the relaxed
 * variant is already fully ordered, no additional barriers are needed.
 */
#define __atomic_op_acquire(op, args...)				\
({									\
	typeof(op##_relaxed(args)) __ret  = op##_relaxed(args);		\
	smp_mb__after_atomic();						\
	__ret;								\
})

#define __atomic_op_release(op, args...)				\
({									\
	smp_mb__before_atomic();					\
	op##_relaxed(args);						\
})

#define __atomic_op_fence(op, args...)					\
({									\
	typeof(op##_relaxed(args)) __ret;				\
	smp_mb__before_atomic();					\
	__ret = op##_relaxed(args);					\
	smp_mb__after_atomic();						\
	__ret;								\
})

/* atomic_add_return_relaxed */
#ifndef atomic_add_return_relaxed
#define  atomic_add_return_relaxed	atomic_add_return
#define  atomic_add_return_acquire	atomic_add_return
#define  atomic_add_return_release	atomic_add_return

#else /* atomic_add_return_relaxed */

#ifndef atomic_add_return_acquire
#define  atomic_add_return_acquire(...)					\
	__atomic_op_acquire(atomic_add_return, __VA_ARGS__)
#endif

#ifndef atomic_add_return_release
#define  atomic_add_return_release(...)					\
	__atomic_op_release(atomic_add_return, __VA_ARGS__)
#endif

#ifndef atomic_add_return
#define  atomic_add_return(...)						\
	__atomic_op_fence(atomic_add_return, __VA_ARGS__)
#endif
#endif /* atomic_add_return_relaxed */

/* atomic_inc_return_relaxed */
#ifndef atomic_inc_return_relaxed
#define  atomic_inc_return_relaxed	atomic_inc_return
#define  atomic_inc_return_acquire	atomic_inc_return
#define  atomic_inc_return_release	atomic_inc_return

#else /* atomic_inc_return_relaxed */

#ifndef atomic_inc_return_acquire
#define  atomic_inc_return_acquire(...)					\
	__atomic_op_acquire(atomic_inc_return, __VA_ARGS__)
#endif

#ifndef atomic_inc_return_release
#define  atomic_inc_return_release(...)					\
	__atomic_op_release(atomic_inc_return, __VA_ARGS__)
#endif

#ifndef atomic_inc_return
#define  atomic_inc_return(...)						\
	__atomic_op_fence(atomic_inc_return, __VA_ARGS__)
#endif
#endif /* atomic_inc_return_relaxed */

/* atomic_sub_return_relaxed */
#ifndef atomic_sub_return_relaxed
#define  atomic_sub_return_relaxed	atomic_sub_return
#define  atomic_sub_return_acquire	atomic_sub_return
#define  atomic_sub_return_release	atomic_sub_return

#else /* atomic_sub_return_relaxed */

#ifndef atomic_sub_return_acquire
#define  atomic_sub_return_acquire(...)					\
	__atomic_op_acquire(atomic_sub_return, __VA_ARGS__)
#endif

#ifndef atomic_sub_return_release
#define  atomic_sub_return_release(...)					\
	__atomic_op_release(atomic_sub_return, __VA_ARGS__)
#endif

#ifndef atomic_sub_return
#define  atomic_sub_return(...)						\
	__atomic_op_fence(atomic_sub_return, __VA_ARGS__)
#endif
#endif /* atomic_sub_return_relaxed */

/* atomic_dec_return_relaxed */
#ifndef atomic_dec_return_relaxed
#define  atomic_dec_return_relaxed	atomic_dec_return
#define  atomic_dec_return_acquire	atomic_dec_return
#define  atomic_dec_return_release	atomic_dec_return

#else /* atomic_dec_return_relaxed */

#ifndef atomic_dec_return_acquire
#define  atomic_dec_return_acquire(...)					\
	__atomic_op_acquire(atomic_dec_return, __VA_ARGS__)
#endif

#ifndef atomic_dec_return_release
#define  atomic_dec_return_release(...)					\
	__atomic_op_release(atomic_dec_return, __VA_ARGS__)
#endif

#ifndef atomic_dec_return
#define  atomic_dec_return(...)						\
	__atomic_op_fence(atomic_dec_return, __VA_ARGS__)
#endif
#endif /* atomic_dec_return_relaxed */

/* atomic_xchg_relaxed */
#ifndef atomic_xchg_relaxed
#define  atomic_xchg_relaxed		atomic_xchg
#define  atomic_xchg_acquire		atomic_xchg
#define  atomic_xchg_release		atomic_xchg

#else /* atomic_xchg_relaxed */

#ifndef atomic_xchg_acquire
#define  atomic_xchg_acquire(...)					\
	__atomic_op_acquire(atomic_xchg, __VA_ARGS__)
#endif

#ifndef atomic_xchg_release
#define  atomic_xchg_release(...)					\
	__atomic_op_release(atomic_xchg, __VA_ARGS__)
#endif

#ifndef atomic_xchg
#define  atomic_xchg(...)						\
	__atomic_op_fence(atomic_xchg, __VA_ARGS__)
#endif
#endif 

#ifndef atomic64_read_acquire
#define  atomic64_read_acquire(v)	smp_load_acquire(&(v)->counter)
#endif

#ifndef atomic64_set_release
#define  atomic64_set_release(v, i)	smp_store_release(&(v)->counter, (i))
#endif

/* atomic64_add_return_relaxed */
#ifndef atomic64_add_return_relaxed
#define  atomic64_add_return_relaxed	atomic64_add_return
#define  atomic64_add_return_acquire	atomic64_add_return
#define  atomic64_add_return_release	atomic64_add_return

#else /* atomic64_add_return_relaxed */

#ifndef atomic64_add_return_acquire
#define  atomic64_add_return_acquire(...)				\
	__atomic_op_acquire(atomic64_add_return, __VA_ARGS__)
#endif

#ifndef atomic64_add_return_release
#define  atomic64_add_return_release(...)				\
	__atomic_op_release(atomic64_add_return, __VA_ARGS__)
#endif

#ifndef atomic64_add_return
#define  atomic64_add_return(...)					\
	__atomic_op_fence(atomic64_add_return, __VA_ARGS__)
#endif
#endif /* atomic64_add_return_relaxed */

/* atomic64_inc_return_relaxed */
#ifndef atomic64_inc_return_relaxed
#define  atomic64_inc_return_relaxed	atomic64_inc_return
#define  atomic64_inc_return_acquire	atomic64_inc_return
#define  atomic64_inc_return_release	atomic64_inc_return

#else /* atomic64_inc_return_relaxed */

#ifndef atomic64_inc_return_acquire
#define  atomic64_inc_return_acquire(...)				\
	__atomic_op_acquire(atomic64_inc_return, __VA_ARGS__)
#endif

#ifndef atomic64_inc_return_release
#define  atomic64_inc_return_release(...)				\
	__atomic_op_release(atomic64_inc_return, __VA_ARGS__)
#endif

#ifndef atomic64_inc_return
#define  atomic64_inc_return(...)					\
	__atomic_op_fence(atomic64_inc_return, __VA_ARGS__)
#endif
#endif /* atomic64_inc_return_relaxed */


/* atomic64_sub_return_relaxed */
#ifndef atomic64_sub_return_relaxed
#define  atomic64_sub_return_relaxed	atomic64_sub_return
#define  atomic64_sub_return_acquire	atomic64_sub_return
#define  atomic64_sub_return_release	atomic64_sub_return

#else /* atomic64_sub_return_relaxed */

#ifndef atomic64_sub_return_acquire
#define  atomic64_sub_return_acquire(...)				\
	__atomic_op_acquire(atomic64_sub_return, __VA_ARGS__)
#endif

#ifndef atomic64_sub_return_release
#define  atomic64_sub_return_release(...)				\
	__atomic_op_release(atomic64_sub_return, __VA_ARGS__)
#endif

#ifndef atomic64_sub_return
#define  atomic64_sub_return(...)					\
	__atomic_op_fence(atomic64_sub_return, __VA_ARGS__)
#endif
#endif /* atomic64_sub_return_relaxed */

/* atomic64_dec_return_relaxed */
#ifndef atomic64_dec_return_relaxed
#define  atomic64_dec_return_relaxed	atomic64_dec_return
#define  atomic64_dec_return_acquire	atomic64_dec_return
#define  atomic64_dec_return_release	atomic64_dec_return

#else /* atomic64_dec_return_relaxed */

#ifndef atomic64_dec_return_acquire
#define  atomic64_dec_return_acquire(...)				\
	__atomic_op_acquire(atomic64_dec_return, __VA_ARGS__)
#endif

#ifndef atomic64_dec_return_release
#define  atomic64_dec_return_release(...)				\
	__atomic_op_release(atomic64_dec_return, __VA_ARGS__)
#endif

#ifndef atomic64_dec_return
#define  atomic64_dec_return(...)					\
	__atomic_op_fence(atomic64_dec_return, __VA_ARGS__)
#endif
#endif /* atomic64_dec_return_relaxed */

/* atomic64_xchg_relaxed */
#ifndef atomic64_xchg_relaxed
#define  atomic64_xchg_relaxed		atomic64_xchg
#define  atomic64_xchg_acquire		atomic64_xchg
#define  atomic64_xchg_release		atomic64_xchg

#else /* atomic64_xchg_relaxed */

#ifndef atomic64_xchg_acquire
#define  atomic64_xchg_acquire(...)					\
	__atomic_op_acquire(atomic64_xchg, __VA_ARGS__)
#endif

#ifndef atomic64_xchg_release
#define  atomic64_xchg_release(...)					\
	__atomic_op_release(atomic64_xchg, __VA_ARGS__)
#endif

#ifndef atomic64_xchg
#define  atomic64_xchg(...)						\
	__atomic_op_fence(atomic64_xchg, __VA_ARGS__)
#endif
#endif /* atomic64_xchg_relaxed */

/* atomic64_cmpxchg_relaxed */
#ifndef atomic64_cmpxchg_relaxed
#define  atomic64_cmpxchg_relaxed	atomic64_cmpxchg
#define  atomic64_cmpxchg_acquire	atomic64_cmpxchg
#define  atomic64_cmpxchg_release	atomic64_cmpxchg

#else /* atomic64_cmpxchg_relaxed */

#ifndef atomic64_cmpxchg_acquire
#define  atomic64_cmpxchg_acquire(...)					\
	__atomic_op_acquire(atomic64_cmpxchg, __VA_ARGS__)
#endif

#ifndef atomic64_cmpxchg_release
#define  atomic64_cmpxchg_release(...)					\
	__atomic_op_release(atomic64_cmpxchg, __VA_ARGS__)
#endif

#ifndef atomic64_cmpxchg
#define  atomic64_cmpxchg(...)						\
	__atomic_op_fence(atomic64_cmpxchg, __VA_ARGS__)
#endif
#endif /* atomic64_cmpxchg_relaxed */

#ifndef atomic_try_cmpxchg

#define __atomic_try_cmpxchg(type, _p, _po, _n)				\
({									\
	typeof(_po) __po = (_po);					\
	typeof(*(_po)) __o = *__po;					\
	*__po = atomic_cmpxchg##type((_p), __o, (_n));			\
	(*__po == __o);							\
})

#define atomic_try_cmpxchg(_p, _po, _n)		__atomic_try_cmpxchg(, _p, _po, _n)
#define atomic_try_cmpxchg_relaxed(_p, _po, _n)	__atomic_try_cmpxchg(_relaxed, _p, _po, _n)
#define atomic_try_cmpxchg_acquire(_p, _po, _n)	__atomic_try_cmpxchg(_acquire, _p, _po, _n)
#define atomic_try_cmpxchg_release(_p, _po, _n)	__atomic_try_cmpxchg(_release, _p, _po, _n)

#else /* atomic_try_cmpxchg */
#define atomic_try_cmpxchg_relaxed	atomic_try_cmpxchg
#define atomic_try_cmpxchg_acquire	atomic_try_cmpxchg
#define atomic_try_cmpxchg_release	atomic_try_cmpxchg
#endif /* atomic_try_cmpxchg */

/* cmpxchg_relaxed */
#ifndef cmpxchg_relaxed
#define  cmpxchg_relaxed		cmpxchg
#define  cmpxchg_acquire		cmpxchg
#define  cmpxchg_release		cmpxchg

#else /* cmpxchg_relaxed */

#ifndef cmpxchg_acquire
#define  cmpxchg_acquire(...)						\
	__atomic_op_acquire(cmpxchg, __VA_ARGS__)
#endif

#ifndef cmpxchg_release
#define  cmpxchg_release(...)						\
	__atomic_op_release(cmpxchg, __VA_ARGS__)
#endif

#ifndef cmpxchg
#define  cmpxchg(...)							\
	__atomic_op_fence(cmpxchg, __VA_ARGS__)
#endif
#endif /* cmpxchg_relaxed */

/* cmpxchg64_relaxed */
#ifndef cmpxchg64_relaxed
#define  cmpxchg64_relaxed		cmpxchg64
#define  cmpxchg64_acquire		cmpxchg64
#define  cmpxchg64_release		cmpxchg64

#else /* cmpxchg64_relaxed */

#ifndef cmpxchg64_acquire
#define  cmpxchg64_acquire(...)						\
	__atomic_op_acquire(cmpxchg64, __VA_ARGS__)
#endif

#ifndef cmpxchg64_release
#define  cmpxchg64_release(...)						\
	__atomic_op_release(cmpxchg64, __VA_ARGS__)
#endif

#ifndef cmpxchg64
#define  cmpxchg64(...)							\
	__atomic_op_fence(cmpxchg64, __VA_ARGS__)
#endif
#endif /* cmpxchg64_relaxed */

/* xchg_relaxed */
#ifndef xchg_relaxed
#define  xchg_relaxed			xchg
#define  xchg_acquire			xchg
#define  xchg_release			xchg

#else /* xchg_relaxed */

#ifndef xchg_acquire
#define  xchg_acquire(...)		__atomic_op_acquire(xchg, __VA_ARGS__)
#endif

#ifndef xchg_release
#define  xchg_release(...)		__atomic_op_release(xchg, __VA_ARGS__)
#endif

#ifndef xchg
#define  xchg(...)			__atomic_op_fence(xchg, __VA_ARGS__)
#endif
#endif /* xchg_relaxed */

/**
 * atomic_add_unless - add unless the number is already a given value
 * @v: pointer of type atomic_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @v, so long as @v was not already @u.
 * Returns non-zero if @v was not @u, and zero otherwise.
 */
static inline int atomic_add_unless(atomic_t *v, int a, int u)
{
	return __atomic_add_unless(v, a, u) != u;
}

/**
 * atomic_inc_not_zero - increment unless the number is zero
 * @v: pointer of type atomic_t
 *
 * Atomically increments @v by 1, so long as @v is non-zero.
 * Returns non-zero if @v was non-zero, and zero otherwise.
 */
#ifndef atomic_inc_not_zero
#define atomic_inc_not_zero(v)		atomic_add_unless((v), 1, 0)
#endif

#ifndef atomic_andnot
static inline void atomic_andnot(int i, atomic_t *v)
{
	atomic_and(~i, v);
}
#endif

static inline __deprecated void atomic_clear_mask(unsigned int mask, atomic_t *v)
{
	atomic_andnot(mask, v);
}

static inline __deprecated void atomic_set_mask(unsigned int mask, atomic_t *v)
{
	atomic_or(mask, v);
}

/**
 * atomic_inc_not_zero_hint - increment if not null
 * @v: pointer of type atomic_t
 * @hint: probable value of the atomic before the increment
 *
 * This version of atomic_inc_not_zero() gives a hint of probable
 * value of the atomic. This helps processor to not read the memory
 * before doing the atomic read/modify/write cycle, lowering
 * number of bus transactions on some arches.
 *
 * Returns: 0 if increment was not done, 1 otherwise.
 */
#ifndef atomic_inc_not_zero_hint
static inline int atomic_inc_not_zero_hint(atomic_t *v, int hint)
{
	int val, c = hint;

	/* sanity test, should be removed by compiler if hint is a constant */
	if (!hint)
		return atomic_inc_not_zero(v);

	do {
		val = atomic_cmpxchg(v, c, c + 1);
		if (val == c)
			return 1;
		c = val;
	} while (c);

	return 0;
}
#endif

#ifndef atomic_inc_unless_negative
static inline int atomic_inc_unless_negative(atomic_t *p)
{
	int v, v1;
	for (v = 0; v >= 0; v = v1) {
		v1 = atomic_cmpxchg(p, v, v + 1);
		if (likely(v1 == v))
			return 1;
	}
	return 0;
}
#endif

#ifndef atomic_dec_unless_positive
static inline int atomic_dec_unless_positive(atomic_t *p)
{
	int v, v1;
	for (v = 0; v <= 0; v = v1) {
		v1 = atomic_cmpxchg(p, v, v - 1);
		if (likely(v1 == v))
			return 1;
	}
	return 0;
}
#endif

/*
 * atomic_dec_if_positive - decrement by 1 if old value positive
 * @v: pointer of type atomic_t
 *
 * The function returns the old value of *v minus 1, even if
 * the atomic variable, v, was not decremented.
 */
#ifndef atomic_dec_if_positive
static inline int atomic_dec_if_positive(atomic_t *v)
{
	int c, old, dec;
	c = atomic_read(v);
	for (;;) {
		dec = c - 1;
		if (unlikely(dec < 0))
			break;
		old = atomic_cmpxchg((v), c, dec);
		if (likely(old == c))
			break;
		c = old;
	}
	return dec;
}
#endif

 /**
+ * atomic_fetch_or - perform *p |= mask and return old value of *p
+ * @p: pointer to atomic_t
+ * @mask: mask to OR on the atomic_t
+ */
#ifndef atomic_fetch_or
static inline int atomic_fetch_or(int mask, atomic_t *p)
{
	int old, val = atomic_read(p);

	for (;;) {
		old = atomic_cmpxchg(p, val, val | mask);
		if (old == val)
			break;
		val = old;
	}

	return old;
}
#endif

#define atomic_cond_read_relaxed(v, c)	smp_cond_load_relaxed(&(v)->counter, (c))
#define atomic_cond_read_acquire(v, c)	smp_cond_load_acquire(&(v)->counter, (c))

#ifdef CONFIG_GENERIC_ATOMIC64
#include <asm-generic/atomic64.h>
#endif

#ifndef atomic64_try_cmpxchg

#define __atomic64_try_cmpxchg(type, _p, _po, _n)			\
({									\
	typeof(_po) __po = (_po);					\
	typeof(*(_po)) __o = *__po;					\
	*__po = atomic64_cmpxchg##type((_p), __o, (_n));		\
	(*__po == __o);							\
})

#define atomic64_try_cmpxchg(_p, _po, _n)		__atomic64_try_cmpxchg(, _p, _po, _n)
#define atomic64_try_cmpxchg_relaxed(_p, _po, _n)	__atomic64_try_cmpxchg(_relaxed, _p, _po, _n)
#define atomic64_try_cmpxchg_acquire(_p, _po, _n)	__atomic64_try_cmpxchg(_acquire, _p, _po, _n)
#define atomic64_try_cmpxchg_release(_p, _po, _n)	__atomic64_try_cmpxchg(_release, _p, _po, _n)

#else /* atomic64_try_cmpxchg */
#define atomic64_try_cmpxchg_relaxed	atomic64_try_cmpxchg
#define atomic64_try_cmpxchg_acquire	atomic64_try_cmpxchg
#define atomic64_try_cmpxchg_release	atomic64_try_cmpxchg
#endif /* atomic64_try_cmpxchg */

#ifndef atomic64_andnot
static inline void atomic64_andnot(long long i, atomic64_t *v)
{
	atomic64_and(~i, v);
}
#endif

#define atomic64_cond_read_relaxed(v, c)	smp_cond_load_relaxed(&(v)->counter, (c))
#define atomic64_cond_read_acquire(v, c)	smp_cond_load_acquire(&(v)->counter, (c))

#include <asm-generic/atomic-long.h>

#endif /* _LINUX_ATOMIC_H */
