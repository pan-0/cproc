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
#	define unnull
#endif

#endif  /* NULL_H */
