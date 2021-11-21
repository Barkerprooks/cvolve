#include "nuralnet.h"

#define CON_FMT "%c [%lu] - [%0.3f] - %c [%lu]\n"

nnetlink_t transcribe_gene(uint16_t gene)
{
  nnetlink_t link;
  link.i = (gene & I_MASK) >> 15;
  link.o = (gene & O_MASK) >> 11;
  link.ii = (gene & I_INDEX_MASK) >> 12;
  link.oi = (gene & O_INDEX_MASK) >> 8;
  link.s = (double) (gene & S_MASK) * 0.015625;
  return link;
}

nuralnet_t create_new_brain(size_t x, size_t y, uint16_t *genome, size_t g)
{
  nuralnet_t brain;
  memset(&brain, 0, sizeof(nuralnet_t));

  brain.name = "hello";
  brain.connect = calloc(sizeof(nnetlink_t), g);
  brain.connections = g;

  // no inputs yet so dont init
  for(int i = 0; i < 8; i++)
  { 
    brain.outputs[i] = sin(rand() % 65535);
    if(i < 4)
      brain.inner[i] = sin(rand() % 65535);
  }

  for(int i = 0; i < g; i++)
    brain.connect[i] = transcribe_gene(genome[i]);
  
  return brain;
}



void pulse(nuralnet_t *brain)
{
  nnetlink_t link;
  double value;
  
  for(int i = 0; i < brain->connections; i++)
  {
    link = brain->connect[i];
    value += link.s;
  }
}

void brain_info(nuralnet_t brain)
{
  const char *ilabels[] = {"cr", "wl", "wr", "wu", "wd"};
  const char *olabels[] = {"mr", "ml", "mr", "mu", "md"};

  for(int i = 0; i < 5; i++)
    printf("( %s: %0.2f ) ", ilabels[i], brain.input[i]);
  printf("\n");
  for(int i = 0; i < 4; i++)
    printf("( %0.2f )", brain.inner[i]);
  printf("\n");
  for(int i = 0; i < 5; i++)
    printf("( %s: %0.2f ) ", olabels[i], brain.outputs[i]);
  printf("\n");

  nnetlink_t link;
  for(int i = 0; i < brain.connections; i++)
  {
    link = brain.connect[i];
    
    if(link.i)
      link.ii = link.ii % 5;
    else
      link.ii = link.ii % 4;

    if(link.o)
      link.oi = link.oi % 4;
    else
      link.oi = link.oi % 5;

    printf(CON_FMT, link.i ? '<':'*', link.ii, link.s, link.o ? '*':'>', link.oi);
  }
}
