#ifndef NULL_H
#define NULL_H

#if defined __CPROC__ && !defined NONULL
#	define NULLABILITY_MODC   _Pragma("cproc nullability MODC")
#	define NULLABILITY_NNBDs  _Pragma("cproc nullability NNBDs")
#	define NULLABILITY_NNBDm  _Pragma("cproc nullability NNBDm")
#	define NULLABILITY_NNBDr  _Pragma("cproc nullability NNBDr")
#	define NULLABILITY_PARENT _Pragma("cproc nullability parent")
#	define nullable _Nullable
#	define nonnull  _Nonnull
#	define unnull   _Unnull
#else
#	define NULLABILITY_MODC
#	define NULLABILITY_NNBDs
#	define NULLABILITY_NNBDm
#	define NULLABILITY_NNBDr
#	define NULLABILITY_PARENT
#	define nullable
#	define nonnull

#	ifndef NULLCHECK
#	define unnull
#	else
#	include <assert.h>
#	ifdef __GNUC__
#		define unnull(ptr)                    \
			(__extension__ ({                 \
				__typeof__(ptr) ptr_ = (ptr); \
				assert(ptr_ != 0);            \
				ptr_;                         \
			}))
#	else
		inline static void *unnull_checked(void *ptr)
		{
			assert(ptr != 0);
			return ptr;
		}
#		define unnull(ptr) ((__typeof__(ptr)) unnull_checked((void *)(ptr)))
#	endif
#	endif
#endif

#endif  /* NULL_H */
