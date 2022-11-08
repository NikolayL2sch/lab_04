#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "structs.h"

uint64_t tick(void);

void print_time(int64_t start, int64_t end);

int compare_stacks(void);

#endif