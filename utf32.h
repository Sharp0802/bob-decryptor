#ifndef BOB_DECRYPTOR_UTF32_H
#define BOB_DECRYPTOR_UTF32_H

#include <stdint.h>
#include <sys/types.h>

__attribute__((externally_visible))
size_t UTF32(uint8_t* utf8, const uint32_t* utf32, size_t nSrc);

#endif //BOB_DECRYPTOR_UTF32_H
