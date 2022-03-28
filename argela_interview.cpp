#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cstdint>

#define SHIFT_RIGHT(x) x>>2 // => divide by 4
#define SHIFT_LEFT(x) x<<2 // => multiply by 4


#define ADD(x) x+x
#define SUB(x) x-x
//#define ADD_F(x) (x+x)
//#define SUB_F(x) (x-x)

int main() {
 //macro substition
 int y = SHIFT_RIGHT(8);
 int z = SHIFT_LEFT(8);
 printf("%d | %d\n", y, z); //=> 2 | 32
 
 //operator preceding
 //printf("%d\n",ADD(3)/SUB(3)); //=> 3+3/3-3 = 1
 //printf("%d\n",ADD_F(3)/SUB_F(3)); //=> 3+3/3-3 = 1
 
 uint32_t num = -1;
 printf("uint32 num : %u\n", num);
 printf("uint32 num : %d\n", num);
}