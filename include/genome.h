#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#ifndef __genome_h__
#define __genome_h__

#define I_MASK 0x8000 // 0: input_node, 1: inner_node
#define O_MASK 0x0800 // 0: inner_node, 1: output_node
#define S_MASK 0x00ff // v: strength of connection x 2
#define I_INDEX_MASK 0x7000 // v: index of input connection
#define O_INDEX_MASK 0x0700 // v: index of output connection
#define GENE_FMT "[%04x] : [ %c | %02u | %c | %02u | %0.2f ]\n"

// allocating memory, don't forget to free!
// generates a random genome
uint16_t **create_genes(size_t, size_t);
uint16_t *create_new_genome(size_t);
uint16_t *create_sex_genome(uint16_t *, uint16_t *, size_t);

void gene_info(uint16_t);
void genome_info(uint16_t *, size_t);

// free memory from gene pool
void unalloc_genes(uint16_t **, size_t);

#endif
