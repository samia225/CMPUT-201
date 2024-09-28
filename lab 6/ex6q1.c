New! Keyboard shortcuts … Drive keyboard shortcuts have been updated to give you first-letters navigation
/* Purpose: Program organization, recursive calls
 * Author: Samia Rahman 
 * Date:25th october
 * References:
 */


#include <stdio.h>
#include "ex6q1.h"

#define LEN 200000000
uint32_t MEMO[LEN];

// This function should be pure recursion - no dynamic programming allowed
uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo) {
    EXP_MOD_1_CALL_COUNT++;
    if (exp == 0) {
        return 1 % modulo;
    } else if (exp  == 1) {
        return base % modulo;
    } else if (exp % 2 == 0) {
        return (exp_mod_1(base, exp / 2, modulo) * exp_mod_1(base, exp / 2, modulo)) % modulo;
    } else {
        return (base % modulo * exp_mod_1(base, exp - 1, modulo)) % modulo;
    }
}

// This function should store the values of previous calls to exp_mod_2 in an array and use them for later calculations.
uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo) {
    if (exp < LEN && MEMO[exp] != 0) {
        return MEMO[exp]; // If total is memoized, return it
    }

    EXP_MOD_2_CALL_COUNT++; // Increment call count

    uint32_t total;

    if (exp == 0) {
        total = 1 % modulo;
    } else if (exp % 2 == 0) {
        uint32_t semi = exp_mod_2(base, exp / 2, modulo);
        total = (semi * semi) % modulo;
    } else {
        total = (base % modulo * exp_mod_2(base, exp - 1, modulo)) % modulo;
    }

    if (exp < LEN) {
        MEMO[exp] = total; // Store the total in the memoization array
    }

    return total;
}


int main(void) {
    uint32_t base, exp, modulo;

    if (scanf("%d %d %d", &base, &exp, &modulo) != 3) {
        return 1;
    }

    uint32_t mod_1 = exp_mod_1(base, exp, modulo);
    uint32_t mod_2 = exp_mod_2(base, exp, modulo);

    fprintf(stdout, "exp_mod_1 calls: %d\n", EXP_MOD_1_CALL_COUNT);
    fprintf(stdout, "exp_mod_2 calls: %d\n", EXP_MOD_2_CALL_COUNT);
    fprintf(stdout, "%d == %d\n", mod_1, mod_2);

    return 0;
}
