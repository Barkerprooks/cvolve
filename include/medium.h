#ifndef __medium_h__
#define __medium_h__

#include "genome.h"
#include "nuralnet.h"

typedef struct
{
  size_t x, y;
} vec2d_t;

typedef struct 
{
  nuralnet_t brain;
  uint16_t *genome;
  vec2d_t position;
} agent_t;

typedef struct
{
  size_t living;
  agent_t *field;
  vec2d_t *alive;
} medium_t;

agent_t create_new_agent(uint16_t *, size_t, vec2d_t);
medium_t create_medium(size_t, size_t, uint16_t **, size_t, size_t);

void update_inputs(medium_t *, size_t, size_t);
void update_medium(medium_t *, size_t, size_t);

void output_medium(medium_t, size_t, size_t);

void unalloc_medium(medium_t *);

#endif
