#include "genome.h"
// creates a randomized gene pool using hex genes
// where n = pool size, and gn = gene size
uint16_t **create_genes(size_t n, size_t gn)
{
  uint16_t seed;
  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, &seed, 1);
  close(fd);

  srand(seed);

  uint16_t **pool = calloc(sizeof(void *), n);
  for(int i = 0; i < n; i++)
    pool[i] = create_new_genome(gn);

  return pool;
}

uint16_t *create_new_genome(size_t n)
{
  uint16_t *genome = calloc(sizeof(uint16_t), n);

  for(int i = 0; i < n; i++)
    genome[i] = rand() % 0xffff;

  // returning a pointer to memory, free this shit!!!
  return genome;
}

uint16_t *create_sex_genome(uint16_t *p1, uint16_t *p2, size_t n)
{
  uint16_t *genome = calloc(sizeof(uint16_t), n);
  // copy odd values from parent 1
  for(int i = 1; i < n; i+=2)
    genome[i] = p1[i];
  // copy even values from parent 2
  for(int i = 0; i < n; i+=2)
    genome[i] = p2[i];
  // free this shit too
  return genome;
}

void gene_info(uint16_t gene)
{
  // gene bits divided into their meanings
  uint8_t i = (gene & I_MASK) >> 15, o = (gene & O_MASK) >> 11;
  uint8_t i_idx = (gene & I_INDEX_MASK) >> 12, o_idx = (gene & O_INDEX_MASK) >> 8;
  double s = (double) (gene & S_MASK) * 0.015625;
  
  if(!i)
    i_idx *= 0.5;
  
  if(o)
    o_idx *= 0.5;
  
  printf(GENE_FMT, gene, i ? '<' : '*', i_idx, o ? '*' : '>', o_idx, s);
}

void genome_info(uint16_t *genome, size_t n)
{
  for(int i = 0; i < n; i++)
  {
    if(i && i % 8 == 0)
      printf("\n");
    printf("[%04x]", genome[i]);
  }
  printf("\n");

  for(int i = 0; i < n; i++)
    gene_info(genome[i]);
}

void unalloc_genes(uint16_t **pool, size_t n)
{
  for(int i = 0; i < n; i++)
    free(pool[i]);
  free(pool);
}
