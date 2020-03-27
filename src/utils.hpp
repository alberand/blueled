#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define get_u8(d) ((uint8_t)(d[0]))
#define get_u16(d) ((uint16_t)((d[0] << 8) | d[1]))
#define get_u32(d) ((uint32_t)(((uint32_t)d[0] << 24) + \
	((uint32_t)d[1] << 16) + \
	((uint32_t)d[2] << 8) + \
	d[3]))

#endif // __UTILS_HPP__
