#ifndef XMSX_H
#define XMSX_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


uint32_t xmsx32(const void *buf, size_t len, uint32_t seed);


#ifdef __cplusplus
};
#endif

#endif /* XMSX_H */
