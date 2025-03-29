#ifndef ASCII_H
#define ASCII_H

#include <stdbool.h>  /* bool */
#include <stdint.h>   /* int32_t, uint32_t */

inline static bool is_alpha(int32_t c)
{
	return ((uint32_t)c | 32) - 'a' < 26;
}

inline static bool is_digit(int32_t c)
{
	return (uint32_t)c - '0' < '9' - '0' + 1;
}

inline static bool is_alnum(int32_t c)
{
	return is_alpha(c) | is_digit(c);
}

inline static bool is_xdigit(int32_t c)
{
	return is_digit(c) | ((uint32_t)c | 32) - 'a' < 6;
}

inline static bool is_odigit(int32_t c)
{
	return (uint32_t)c - '0' < '7' - '0' + 1;
}

inline static bool is_print(int32_t c)
{
	return (uint32_t)c - 0x20 < 0x5F;
}

inline static bool is_upper(int32_t c)
{
	return (uint32_t)c - 'A' < 'Z' - 'A' + 1;
}

inline static int32_t to_lower(int32_t c)
{
	return c | (32 & -(int32_t)is_upper(c));
}

#endif  /* ASCII_H */
