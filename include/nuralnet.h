#ifndef __nuralnet_h__
#define __nuralnet_h__

#include <math.h>
#include "genome.h"

typedef struct
{
  uint8_t i, o;
  size_t ii, oi;
  double s;
} nnetlink_t;

typedef struct
{
  const char *name;
  size_t connections;
  double input[8], inner[4], outputs[8];
  nnetlink_t *connect;
} nuralnet_t;

nnetlink_t trascribe_gene(uint16_t);
nuralnet_t create_new_brain(size_t, size_t, uint16_t *, size_t);

void pulse(nuralnet_t *);
void brain_info(nuralnet_t);

#endif
