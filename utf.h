#ifndef UTF_H
#define UTF_H

#include "null.h"

NULLABILITY_NNBDs

size_t utf8enc(unsigned char *, uint_least32_t);
size_t utf8dec(uint_least32_t *, const unsigned char *, size_t);
size_t utf16enc(uint_least16_t *, uint_least32_t);

NULLABILITY_PARENT

#endif  /* UTF_H */
