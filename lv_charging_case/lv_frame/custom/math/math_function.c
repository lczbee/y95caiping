#include "custom.h"

#define _POW	_quick_pow
#define _SQRT	_quick_sqrt

float _pow(float num, int n)
{
    float powfloat = 1.0;
    int i;
    for (i = 1; i <= n; i++) {
        powfloat *= num;
    }
    return powfloat;
}

float _quick_pow(float x, int n) 
{
    if (n < 0) {
        if (x == 0) {
            return 0; // 0的负数次幂没有数学意义
        }
        x = 1 / x;
        n = -n;
    }
    
    float result = 1.0;
    float base = x;
    
    while (n > 0) {
        if (n % 2 == 1) {
            result *= base;
        }
        base *= base; // 指数每次翻倍
        n /= 2;       // 指数每次减半
    }
    
    return result;
}

float _quick_sqrt(float x) 
{
    if (x <= 0.0) {
        return 0.0; // 对于非正数，返回0或处理为错误情况
    }

    float tolerance = 1e-10; // 定义精度
    float result = x; // 初始猜测值
    float last_result;

    do {
        last_result = result;
        result = (result + x / result) / 2.0; // 牛顿迭代公式
    } while (fabs(result - last_result) > tolerance); // 检查是否达到所需精度

    return result;
}

#if 0
float easeOutSine(float x)
{
  	return sin_float((x * PI) / 2);
}

float easeInSine(float x)
{
  	return 1 - cos_float((x * PI) / 2);
}

float easeInOutSine(float x)
{
	return -(cos_float(PI * x) - 1) / 2;
}
#endif

float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float easeInQuad(float x)
{
	return x * x;
}

float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : 1 - _POW(-2 * x + 2, 2) / 2;
}

float easeOutCubic(float x)
{
	return 1 - _POW(1 - x, 3);
}

float easeInCubic(float x)
{
	return x * x * x;
}

float easeInOutCubic(float x)
{
	return x < 0.5 ? 4 * x * x * x : 1 - _POW(-2 * x + 2, 3) / 2;
}

float easeOutQuart(float x)
{
    return 1 - _POW(1 - x, 4);
}

float easeInQuart(float x)
{
	return x * x * x * x;
}

float easeInOutQuart(float x)
{
	return x < 0.5 ? 8 * x * x * x * x : 1 - _POW(-2 * x + 2, 4) / 2;
}

float easeOutQuint(float x)
{
	return 1 - _POW(1 - x, 5);
}

float easeInQuint(float x)
{
	return x * x * x * x * x;
}

float easeInOutQuint(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : 1 - _POW(-2 * x + 2, 5) / 2;
}

float easeOutExpo(float x)
{
	return x == 1 ? 1 : 1 - _POW(2, -10 * x);
}

float easeInExpo(float x)
{
	return x == 0 ? 0 : _POW(2, 10 * x - 10);
}

float easeInOutExpo(float x)
{
	float result;
	if(x == 0) {
		result = 0;
	} else if(x == 1) {
		result = 1;
	} else if(x < 0.5) {
		result = _POW(2, 20 * x - 10) / 2;
	} else {
		result = (2 - _POW(2, -20 * x + 10)) / 2;
	}

	return result;
}

float easeOutCirc(float x)
{
	return _SQRT(1 - _POW(x - 1, 2));
}

float easeInCirc(float x)
{
	return 1 - _SQRT(1 - _POW(x, 2));
}

float easeInOutCirc(float x)
{
	return x < 0.5 ? (1 - _SQRT(1 - _POW(2 * x, 2))) / 2 : (_SQRT(1 - _POW(-2 * x + 2, 2)) + 1) / 2;
}

float easeOutBack(float x)
{
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return 1 + c3 * _POW(x - 1, 3) + c1 * _POW(x - 1, 2);
}

float easeInBack(float x)
{
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return c3 * x * x * x - c1 * x * x;
}

float easeInOutBack(float x)
{
	const float c1 = 1.70158;
	const float c2 = c1 * 1.525;

	return x < 0.5 ? (_POW(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2 : (_POW(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

#if 0
float easeOutElastic(float x)
{
	const float c4 = (2 * PI) / 3;

	float result;

	if(x == 0) {
		result = 0;
	} else if(x == 1) {
		result =1;
	} else {
		result = _POW(2, -10 * x) * sin_float((x * 10 - 0.75) * c4) + 1;
	}

	return result;
}

float easeInElastic(float x)
{
	const float c4 = (2 * PI) / 3;

	float result;

	if(x == 0) {
		result = 0;
	} else if(x == 1) {
		result = 1;
	} else {
		result = -_POW(2, 10 * x - 10) * sin_float((x * 10 - 10.75) * c4);
	}

	return result;
}

float easeInOutElastic(float x)
{
	const float c5 = (2 * PI) / 4.5;

	float result;

	if(x == 0) {
		result = 0;
	} else if(x == 1) {
		result = 1;
	} else if(x < 0.5) {
		result = -(_POW(2, 20 * x - 10) * sin_float((20 * x - 11.125) * c5)) / 2;
	} else {
		result = (_POW(2, -20 * x + 10) * sin_float((20 * x - 11.125) * c5)) / 2 + 1;
	}

	return result;
}
#endif

float easeOutBounce(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	} else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	} else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	} else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

float easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float easeInOutBounce(float x)
{
	return x < 0.5 ? (1 - easeOutBounce(1 - 2 * x)) / 2 : (1 + easeOutBounce(2 * x - 1)) / 2;
}

