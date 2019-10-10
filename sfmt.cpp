#include "sfmt.h"


void sfmt_init_gen_rand(sfmt_t * sfmt, uint32_t seed) {
    int i;

    uint32_t *psfmt32 = &sfmt->state[0].u[0];

    psfmt32[idxof(0)] = seed;
    for (i = 1; i < SFMT_N32; i++) {
        psfmt32[idxof(i)] = 1812433253UL * (psfmt32[idxof(i - 1)] ^ (psfmt32[idxof(i - 1)] >> 30)) + i;
    }
    sfmt->idx = SFMT_N32;
    period_certification(sfmt);
}

inline static int idxof(int i) {
    return i;
}

static void period_certification(sfmt_t * sfmt) {
    int inner = 0;
    int i, j;
    uint32_t work;
    uint32_t *psfmt32 = &sfmt->state[0].u[0];
    const uint32_t parity[4] = {SFMT_PARITY1, SFMT_PARITY2,
                                SFMT_PARITY3, SFMT_PARITY4};

    for (i = 0; i < 4; i++)
        inner ^= psfmt32[idxof(i)] & parity[i];
    for (i = 16; i > 0; i >>= 1)
        inner ^= inner >> i;
    inner &= 1;
    /* check OK */
    if (inner == 1) {
        return;
    }
    /* check NG, and modification */
    for (i = 0; i < 4; i++) {
        work = 1;
        for (j = 0; j < 32; j++) {
            if ((work & parity[i]) != 0) {
                psfmt32[idxof(i)] ^= work;
                return;
            }
            work = work << 1;
        }
    }
}

uint32_t sfmt_genrand_uint32(sfmt_t * sfmt) {
    uint32_t r;
    uint32_t * psfmt32 = &sfmt->state[0].u[0];

    if (sfmt->idx >= SFMT_N32) {
        sfmt_gen_rand_all(sfmt);
        sfmt->idx = 0;
    }
    r = psfmt32[sfmt->idx++];
    return r;
}

static void sfmt_gen_rand_all(sfmt_t * sfmt) {
    int i;
    w128_t *r1, *r2;

    r1 = &sfmt->state[SFMT_N - 2];
    r2 = &sfmt->state[SFMT_N - 1];
    for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
        do_recursion(&sfmt->state[i], &sfmt->state[i],
                     &sfmt->state[i + SFMT_POS1], r1, r2);
        r1 = r2;
        r2 = &sfmt->state[i];
    }
    for (; i < SFMT_N; i++) {
        do_recursion(&sfmt->state[i], &sfmt->state[i],
                     &sfmt->state[i + SFMT_POS1 - SFMT_N], r1, r2);
        r1 = r2;
        r2 = &sfmt->state[i];
    }
}

inline static void do_recursion(w128_t *r, w128_t *a, w128_t *b, w128_t *c, w128_t *d)
{
    w128_t x;
    w128_t y;

    lshift128(&x, a, SFMT_SL2);
    rshift128(&y, c, SFMT_SR2);
    r->u[0] = a->u[0] ^ x.u[0] ^ ((b->u[0] >> SFMT_SR1) & SFMT_MSK1)
              ^ y.u[0] ^ (d->u[0] << SFMT_SL1);
    r->u[1] = a->u[1] ^ x.u[1] ^ ((b->u[1] >> SFMT_SR1) & SFMT_MSK2)
              ^ y.u[1] ^ (d->u[1] << SFMT_SL1);
    r->u[2] = a->u[2] ^ x.u[2] ^ ((b->u[2] >> SFMT_SR1) & SFMT_MSK3)
              ^ y.u[2] ^ (d->u[2] << SFMT_SL1);
    r->u[3] = a->u[3] ^ x.u[3] ^ ((b->u[3] >> SFMT_SR1) & SFMT_MSK4)
              ^ y.u[3] ^ (d->u[3] << SFMT_SL1);
}

inline static void lshift128(w128_t *out, w128_t const *in, int shift)
{
    uint64_t th, tl, oh, ol;

    th = ((uint64_t)in->u[3] << 32) | ((uint64_t)in->u[2]);
    tl = ((uint64_t)in->u[1] << 32) | ((uint64_t)in->u[0]);

    oh = th << (shift * 8);
    ol = tl << (shift * 8);
    oh |= tl >> (64 - shift * 8);
    out->u[1] = (uint32_t)(ol >> 32);
    out->u[0] = (uint32_t)ol;
    out->u[3] = (uint32_t)(oh >> 32);
    out->u[2] = (uint32_t)oh;
}

inline static void rshift128(w128_t *out, w128_t const *in, int shift)
{
    uint64_t th, tl, oh, ol;

    th = ((uint64_t)in->u[3] << 32) | ((uint64_t)in->u[2]);
    tl = ((uint64_t)in->u[1] << 32) | ((uint64_t)in->u[0]);

    oh = th >> (shift * 8);
    ol = tl >> (shift * 8);
    ol |= th << (64 - shift * 8);
    out->u[1] = (uint32_t)(ol >> 32);
    out->u[0] = (uint32_t)ol;
    out->u[3] = (uint32_t)(oh >> 32);
    out->u[2] = (uint32_t)oh;
}

double sfmt_genrand_real1(sfmt_t * sfmt)
{
    return sfmt_to_real1(sfmt_genrand_uint32(sfmt));
}

double sfmt_to_real1(uint32_t v)
{
    return v * (1.0/4294967295.0);
    /* divided by 2^32-1 */
}