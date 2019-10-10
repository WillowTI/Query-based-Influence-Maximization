#ifndef SFMT_SFMT_H
#define SFMT_SFMT_H

#include <cstdint>

#define SFMT_MEXP 19937
#define SFMT_N (SFMT_MEXP / 128 + 1)
#define SFMT_N32 (SFMT_N * 4)
#define SFMT_POS1	68
#define SFMT_SL1	14
#define SFMT_SL2	3
#define SFMT_SR1	7
#define SFMT_SR2	3
#define SFMT_MSK1	0xeffff7fbU
#define SFMT_MSK2	0xffffffefU
#define SFMT_MSK3	0xdfdfbfffU
#define SFMT_MSK4	0x7fffdbfdU
#define SFMT_PARITY1	0x00000001U
#define SFMT_PARITY2	0x00000000U
#define SFMT_PARITY3	0xe8148000U
#define SFMT_PARITY4	0xd0c7afa3U

//typedef unsigned int uint32_t;
//typedef unsigned long long uint64_t;

union W128_T {
    uint32_t u[4];
    uint64_t u64[2];
};
typedef union W128_T w128_t;
struct SFMT_T {
    /** the 128-bit internal state array */
    w128_t state[SFMT_N];
    /** index counter to the 32-bit internal state array */
    int idx;
};

typedef struct SFMT_T sfmt_t;

void sfmt_init_gen_rand(sfmt_t * sfmt, uint32_t seed);
inline static int idxof(int i);
static void period_certification(sfmt_t * sfmt);
uint32_t sfmt_genrand_uint32(sfmt_t * sfmt);
static void sfmt_gen_rand_all(sfmt_t * sfmt);
inline static void do_recursion(w128_t * r, w128_t * a, w128_t * b, w128_t * c, w128_t * d);
inline static void rshift128(w128_t *out,  w128_t const *in, int shift);
inline static void lshift128(w128_t *out,  w128_t const *in, int shift);
double sfmt_genrand_real1(sfmt_t * sfmt);
double sfmt_to_real1(uint32_t v);

#endif