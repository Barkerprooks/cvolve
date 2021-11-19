#include <stdint.h>

#include "medium.h"

#define W 50
#define H 25
#define N 25
#define G 8

int main(void)
{ 
  // creates random pool of hex genes
  // for this example, 25 individuals
  // with 8 genes each
  uint16_t **pool = create_genes(N, G);  
  
  // medium which these individuals move
  // through. the individuals are governed
  // by a brain encoded into the hex DNA
  // we generated
  medium_t grid = create_medium(W, H, pool, N, G);

  output_medium(grid, W, H);

  vec2d_t v = grid.alive[0];
  agent_t a = grid.field[v.x + W * v.y];

  brain_info(a.brain);
  pulse(&(a.brain), a.brain.connect[0]);  
  brain_info(a.brain);

  unalloc_genes(pool, N);
  unalloc_medium(&grid);

  return 0;
}
