#ifndef BOB_DECRYPTOR_CP949_H
#define BOB_DECRYPTOR_CP949_H

#include <stdint.h>
#include <sys/types.h>


size_t CP949(uint8_t* utf8, const uint8_t* cp949, size_t nSrc);

#endif //BOB_DECRYPTOR_CP949_H
