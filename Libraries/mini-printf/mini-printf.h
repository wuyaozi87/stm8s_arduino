// mini-printf.h
#ifndef __MINI_PRINTF__
#define __MINI_PRINTF__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

int mini_vsnprintf(char* buffer, unsigned int buffer_len, const char *fmt, va_list va);
int mini_snprintf(char* buffer, unsigned int buffer_len, const char *fmt, ...);

#ifdef __cplusplus
}
#endif



#endif
