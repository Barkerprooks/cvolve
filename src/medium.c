#include "nuralnet.h"
#include "medium.h"

agent_t create_new_agent(uint16_t *genome, size_t g, vec2d_t position)
{
  agent_t agent = {
    create_new_brain(position.x, position.y, genome, g),
    genome,
    position
  };
  return agent;
}

// to have a gene pool, srand is probably already called
medium_t create_medium(size_t w, size_t h, uint16_t **pool, size_t n, size_t g)
{ 
  medium_t medium;
  memset(&medium, 0, sizeof(medium_t));

  medium.field = calloc(sizeof(agent_t), w * h);
  medium.alive = calloc(sizeof(vec2d_t), w * h);

  for(int i = 0; i < n; i++)
  {
    size_t x = rand() % w, y = rand() % h;
    vec2d_t position = { x, y };
    medium.field[x + w * y] = create_new_agent(pool[i], g, position);
    medium.alive[i] = position;
    medium.living++;
  }

  return medium;
}

void output_medium(medium_t medium, size_t w, size_t h)
{
  agent_t cell;
  for(int y = 0; y < h; y++)
  {
    for(int x = 0; x < w; x++)
    {
      cell = medium.field[x + w * y];
      if(cell.genome)
        printf("#");
      else
        printf(".");
    }
    printf("\n");
  }

}

void unalloc_medium(medium_t *medium)
{
  free(medium->field);
  free(medium->alive);
}
