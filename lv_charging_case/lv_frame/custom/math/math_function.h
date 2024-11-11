#ifndef __MATH_FUNCTION__
#define __MATH_FUNCTION__
#ifdef __cplusplus
extern "C" {
#endif

#include "asm/math_fast_function.h"

#define PI  (float)3.1415926

#define ABS(x) (((x) > 0) ? (x):(-x))

float _pow(float num, int n);
float _quick_pow(float x, int n);
float _quick_sqrt(float x);

float easeOutQuad(float x);
float easeInQuad(float x);
float easeInOutQuad(float x);

float easeOutCubic(float x);
float easeInCubic(float x);
float easeInOutCubic( float x);

float easeOutQuart(float x);
float easeInQuart(float x);
float easeInOutQuart(float x);

float easeOutQuint(float x);
float easeInQuint(float x);
float easeInOutQuint(float x);

float easeOutExpo(float x);
float easeInExpo(float x);
float easeInOutExpo(float x);

float easeOutCirc(float x);
float easeInCirc(float x);
float easeInOutCirc(float x);

float easeOutBack(float x);
float easeInBack(float x);
float easeInOutBack(float x);

float easeOutBounce(float x);
float easeInBounce(float x);
float easeInOutBounce(float x);

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_LIGHT_H_ */
