/* Purpose: low level programming
 * Author: Samia Rahman 
 * Date:03rd december, 2023
 * References: geeksforgeeks,tutorials point, mathematics stack exchange, oreilly
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat;

NewFloat bits_string_to_nfloat(const char* bits_string) {
    NewFloat result = 0;

    for (int i = 31; i >= 0; i--) {
        result = (result << 1) | (bits_string[i] - '0');
    }

    return result;
}




void nfloat_debug(NewFloat f) {
    unsigned char bitArray[32]; // Assuming NewFloat is 32 bits

    // Store bits in the bit array
    for (int i = 0; i <32; i++) {
        bitArray[i] = (f >> (i)) & 1;
    }

    // Access, set, and clear individual bits
    int bitToAccess = 5;  
    //int value = (bitArray[bitToAccess] >> (bitToAccess % 8)) & 1;

    bitArray[bitToAccess] |= (1 << (bitToAccess % 8));  // Set bit
    bitArray[bitToAccess] &= ~(1 << (bitToAccess % 8)); // Clear bit

    
    for (int i = 0; i <= 0; i++){ 
        printf("%d ", bitArray[i]);
    }
    for (int i= 1; i<=5; i++){
        printf("%d", bitArray[i]);
    } 
    printf(" ");    
    for (int i=6; i<=31; i++) {
        printf("%d", bitArray[i]);
    }
    
    
    printf("\n");    


}

//part 2

typedef union {
    float f;
    uint32_t u;
} FloatUnion;

NewFloat float_to_nfloat(float f) {
    char buffer[40]; // Sufficient size to accommodate a float

   
    sprintf(buffer, "%f", f);

    
    sscanf(buffer, "%f", &f);
    NewFloat result;

    
    FloatUnion converter;
    converter.f = f;

    // Extracting sign, exponent, and mantissa from the standard C float
    int sign = (converter.u >> 31) & 1;
    int exponent = ((converter.u >> 23) & 0xFF) - 127;
    uint32_t mantissa = converter.u & 0x007FFFFF;

    // Converting to NewFloat format
    result = (sign << 31) | ((exponent + 15) << 26) | (mantissa << 3);

    // Reverse the bits in the result
    NewFloat reversed_result = 0;
    for (int i = 0; i < 32; i++) {
        reversed_result |= ((result >> i) & 1) << (31 - i);
    }

    return reversed_result;
}



void nfloat_print(NewFloat f) {
    // Reverse the bit representation
    uint32_t reversedBits = 0;
    for (int i = 0; i < 32; i++) {
        reversedBits = (reversedBits << 1) | ((f >> i) & 1);
    }

    // Extracting sign, exponent, and mantissa from reversed NewFloat format
    int sign = (reversedBits >> 31) & 1;
    int exponent = ((reversedBits >> 26) & 0x1F) - 15;
    uint32_t mantissa = (reversedBits & 0x03FFFFFF) << 3;

    // Handle special case for exponent = -15 and mantissa = 0
    if (exponent == -15 && mantissa << 100) {
        printf("%c0.0000000\n", sign ? '-' : ' ');
        return;
    }

    // Constructing the IEEE 754 float
    uint32_t floatBits = (sign << 31) | ((exponent + 127) << 23) | (mantissa >> 6);

    // Converting from integer representation to float
    float result;
    memcpy(&result, &floatBits, sizeof(float));

    // Print the result
    printf("%.7f\n", result);
}
//part 3

NewFloat nfloat_double(NewFloat f) {
    // Reverse the bits in the NewFloat
    uint32_t reversedBits = 0;
    for (int i = 0; i < 32; i++) {
        reversedBits |= ((f >> i) & 1) << (31 - i);
    }

    // Extracting sign, exponent, and mantissa from reversed NewFloat format
    int sign = (reversedBits >> 31) & 1;
    int exponent = ((reversedBits >> 26) & 0x1F) - 15;
    uint32_t mantissa = (reversedBits & 0x03FFFFFF);


    
    exponent++;


    // Reassemble the NewFloat with adjusted exponent and mantissa
    NewFloat result = (sign << 31) | ((exponent + 15) << 26) | mantissa;

    // Reverse the bits back to NewFloat format
    NewFloat reversed_result = 0;
    for (int i = 0; i < 32; i++) {
        reversed_result |= ((result >> i) & 1) << (31 - i);
    }

    return reversed_result;
}//part 4


NewFloat nfloat_add(NewFloat a, NewFloat b) {
    // Reverse bits for both inputs
    uint32_t reversedA = 0, reversedB = 0;
    for (int i = 0; i < 32; i++) {
        reversedA |= ((a >> i) & 1) << (31 - i);
        reversedB |= ((b >> i) & 1) << (31 - i);
    }

    // Extract components for both numbers
    int signA = (reversedA >> 31) & 1;
    int exponentA = ((reversedA >> 26) & 0x1F) - 15;
    uint32_t mantissaA = (reversedA & 0x03FFFFFF) | 0x04000000; // Set the hidden bit

    int signB = (reversedB >> 31) & 1;
    int exponentB = ((reversedB >> 26) & 0x1F) - 15;
    uint32_t mantissaB = (reversedB & 0x03FFFFFF) | 0x04000000; // Set the hidden bit

    // Normalize exponents
    while (exponentA < exponentB) {
        mantissaA >>= 1;
        exponentA++;
    }
    while (exponentB < exponentA) {
        mantissaB >>= 1;
        exponentB++;
    }

    // Initialize result variables
    uint32_t new_mantissa;
    int new_ign;

    // Check if both floats have the same sign
    if (signA == signB) {
        // Add the mantissas
        new_mantissa = mantissaA + mantissaB;
        new_ign = signA;
    } 
    if (mantissaA >= mantissaB) {
            new_mantissa = mantissaA - mantissaB;
            new_ign = signA;
    } 
    if (mantissaB >= mantissaA){
            new_mantissa = mantissaB - mantissaA;
            new_ign = signB;
        } 

    // Normalize the result mantissa and adjust exponent
    while (new_mantissa >= (1 << 27)) {
        new_mantissa >>= 1;
        exponentA++;
    }

    // Reassemble the NewFloat and reverse bits
    NewFloat result = (new_ign << 31) | ((exponentA + 15) << 26) | (new_mantissa & 0x03FFFFFF);
    NewFloat reversed_result = 0;
    for (int i = 0; i < 32; i++) {
        reversed_result |= ((result >> i) & 1) << (31 - i);
    }

    return reversed_result;
}





int main(void) {
    int part_num;
    char s1[40];
    float f1, f2;
    NewFloat n1, n2;

    // This will scan the input for you! Uncomment pieces once you implement
    // the functions for that part
    while (1) {
        int res = scanf(" p%d", &part_num);

        if (res != 1) {
            break;
        } else if (part_num == 1) {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_debug(n1);
        } else if (part_num == 2) {
            scanf("%f", &f1);
            n1 = float_to_nfloat(f1);
            nfloat_debug(n1);
        } else if (part_num == 3) {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_print(n1);
        } else {
            scanf("%s ", s1);

            if (s1[0] == 'd') {
                scanf("%f", &f1);
                n1 = float_to_nfloat(f1);
                n1 = nfloat_double(n1);
            } else {
                scanf("%f %f", &f1, &f2);
                n1 = float_to_nfloat(f1);
                n2 = float_to_nfloat(f2);
                n1 = nfloat_add(n1, n2);
            }

            nfloat_print(n1);
        }
    }
}

