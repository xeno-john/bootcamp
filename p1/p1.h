#ifndef P1_H_
#define P1_H_

#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**
 * @fn char* print_bits(uint32_t input_value);
 * @brief Function that receives an uint32_t and returns the bit configuration of that number.
 * @param [in] input_value - the value gave by the user for which we will print the bits.
 * @return *number_representation - a char array that stores the bit configuration of the number
 */
char* print_bits(uint32_t input_value);

#endif