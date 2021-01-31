#include <arm_neon.h>
#include <chrono>
#include <iostream>

uint32_t add(uint16_t p0){
  uint16_t src0[] = { p0+8,p0+9, p0+10, p0+11, p0+12, p0+13, p0+14, p0+15};
  uint16_t src1[] = {108,109,110,111,112,113,114,115};
  uint16_t src2[] = { p0+8,p0+9, p0+10, p0+11, p0+12, p0+13, p0+14, p0+15};
  // uint16_t dst [8] = {};

  
  uint16x8_t s0 = vld1q_u16(src0);
  uint16x8_t s1 = vld1q_u16(src1);
  uint16x8_t s2 = vld1q_u16(src2);
  uint16x8_t d  = vmlaq_u16(s0, s1, s2);
  uint16x8_t d2  = vmlaq_u16(s0, s1, d);

  auto sum1 = vpaddlq_u16(d2); // 8 -> 4
  auto sum2 = vpaddlq_u32(sum1); // 4 -> 2
  auto sum3 = sum2[0] + sum2[1];

  // vst1q_u16(dst, d);
  // for( auto i = 0;i < 8;i++)
  //   {
  //     std::cout << i << '\t' << (int)src0[i] << '\t' << (int)src1[i] << '\t' << (int)dst[i] << std::endl;
  //   }
  return sum3;
}

uint32_t add_arm(uint16_t p0){
  uint16_t src0[] = { p0+8,p0+9, p0+10, p0+11, p0+12, p0+13, p0+14, p0+15};
  uint16_t src1[] = {108,109,110,111,112,113,114,115};
  uint16_t src2[] = { p0+8,p0+9, p0+10, p0+11, p0+12, p0+13, p0+14, p0+15};
  uint16_t dst [8] = {};
  uint16_t dst2 [8] = {};
  
  for (int i = 0; i < 8; i++){
    dst[i] = src0[i] + src1[i] * src2[i];
  }
  for (int i = 0; i < 8; i++){
    dst2[i] = src0[i] + src1[i] * dst[i];
  }
    
  uint32_t sum = 0;
  for (int i = 0; i < 8; i++){
    sum += dst2[i];
  }
  return sum;
}


int main(int argc, char** argv){
  std::cout << "Hello neon" << std::endl;

  static constexpr auto COUNT =  10000000;
  static constexpr auto LOOP = 10;

  uint64_t dummy_sum = 0;
    
  for (int j = 0; j < LOOP; j++){
    auto t0 = std::chrono::system_clock::now();
    for (int i = 0; i < COUNT; i++){
      dummy_sum +=  add(i*j);
    }
    auto t1 = std::chrono::system_clock::now();
    double d0 = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << d0 << "\t";
  }

  std::cout << std::endl;

  for (int j = 0; j < LOOP; j++){
    auto t0 = std::chrono::system_clock::now();
    for (int i = 0; i < COUNT; i++){
      dummy_sum += add_arm(i*j);
    }
    auto t1 = std::chrono::system_clock::now();
    double d1 = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << d1 << "\t";
  }

  std::cout << std::endl;
  std::cout << dummy_sum << std::endl;
  
  return 0;
}
