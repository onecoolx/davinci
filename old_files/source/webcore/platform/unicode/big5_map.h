#ifndef BIG5_MAP_H_
#define BIG5_MAP_H_

#if ENABLE(BIG5_SUPPORT)
extern const unsigned short big5_map[];
const unsigned char* map_uc16_to_big5(unsigned short uc16);
#endif

#endif
