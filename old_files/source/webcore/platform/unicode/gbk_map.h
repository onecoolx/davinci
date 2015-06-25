#ifndef GBK_MAP_H_
#define GBK_MAP_H_

#if ENABLE(GBK_SUPPORT)
extern const unsigned short gbk_map[];
const unsigned char* map_uc16_to_gbk(unsigned short uc16);
#endif

#endif
