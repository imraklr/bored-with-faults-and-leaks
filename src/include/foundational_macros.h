/**
 * @file foundational_macros.h
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief This file contains all the basic types needed by this project.
 * @version 0.1.0
 * @date 2025-04-17
 * 
 * 
 */
#pragma once

#include <stdint.h>

typedef uint8_t u8;

/**
 * @brief This macro takes two arguments: type and result(out). This macro casts the value of 'out' to the desired type.
 * 
 */
#define cast(type, out) ((type)(out))