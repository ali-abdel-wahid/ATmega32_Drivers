/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<       BIT_MATH.h        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*
*Author: Ali Abdelwahed
*Layar :LIB
*
*/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg,bit)             reg |= (1<<bit)
#define CLR_BIT(reg,bit)             reg &= (~ (1<<bit)) 
#define TOG_BIT(reg,bit)             reg ^= (1<<bit)
#define GET_BIT(reg,bit)             (((reg) & (1 << (bit))) >> (bit))


#define IS_BIT_SET(reg, bit)   (((reg) >> (bit)) & 1)
#define IS_BIT_CLR(reg, bit)   (!(((reg) >> (bit)) & 1))


#define ROR(reg, num)   ((reg) = ((reg) >> (num)) | ((reg) << (REGISTER_SIZE - (num))))
#define ROL(reg, num)   ((reg) = ((reg) << (num)) | ((reg) >> (REGISTER_SIZE - (num))))

#endif /*BIT_MATH_H_*/