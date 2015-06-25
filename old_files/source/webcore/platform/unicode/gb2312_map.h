#ifndef GB2312_MAP_H_
#define GB2312_MAP_H_

#if ENABLE(GB2312_SUPPORT)
extern const unsigned short gb2312_map[];
const unsigned char* map_uc16_to_gb2312(unsigned short uc16);
#endif

#endif
