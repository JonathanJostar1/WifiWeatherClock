/* u8g2_d_memory.c */
/* generated code, codebuild, u8g2 project */

#include "u8g2.h"

#if 0
uint8_t *u8g2_m_16_16_1(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 1;
  return 0;
  #else
  static uint8_t buf[128];
  *page_cnt = 1;
  return buf;
  #endif
}
uint8_t *u8g2_m_16_16_2(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 2;
  return 0;
  #else
  static uint8_t buf[256];
  *page_cnt = 2;
  return buf;
  #endif
}
#endif

uint8_t *u8g2_m_16_16_f(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 16;
  return 0;
  #else
  static uint8_t buf[2048];
  *page_cnt = 16;
  return buf;
  #endif
}

/* end of generated code */
