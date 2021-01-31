#include <arm_neon.h>
#include <iostream>

int main(int argc, char** argv){
  std::cout << "Hello neon" << std::endl;
  unsigned char src0[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15};
  unsigned char src1[] = {100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115};
  unsigned char dst [] = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
  uint8x16_t s0 = vld1q_u8(src0);
  uint8x16_t s1 = vld1q_u8(src1);
  uint8x16_t d  = vaddq_u8(s0, s1); // ここで足し算
  vst1q_u8(dst, d);
  for( auto i = 0;i < 16;i++)
    {
      std::cout << i << '\t' << (int)src0[i] << '\t' << (int)src1[i] << '\t' << (int)dst[i] << std::endl;
    }
  
  return 0;
}
