#include <math.h>
#include "remap.h"


/**
 * @fn  float fastSin(float x)
 *
 * @brief   自定义快速变换 sin  cos  函数  定义 而外精度 更高拟合效果 参考链接
 *          https://www.cnblogs.com/sun11086/archive/2009/03/20/1417944.html
 *
 * @author  IRIS_Chen
 * @date    2019/6/17
 *
 * @param   x   The x coordinate
 *
 * @return  A float
 */
//本质上是利用了一个已经拟合好的二次函数近似三角函数
float fastSin(float x)
{
    // 限定 x 在 -Pi  到 pi
    while (x < - PI)
    {
        x += (float)(2 * PI);
    }
    while (x > PI)
    {
        x -= (float)(2 * PI);
    }

    const float B = 1.2732f; // 4 / CV_PI;
    const float C = -0.4053f; // -4 / (CV_PI*CV_PI);
    float y = B * x + C * x * abs(x);
    const float P = 0.225f;
    y = P * (y * abs(y) - y) + y;
    return y;
}


/**
 * @fn  float fastCos(float x)
 *
 * @brief   Fast cosine
 *
 * @author  IRIS_Chen
 * @date    2019/6/17
 *
 * @param   x   The x coordinate
 *
 * @return  A float
 */
float fastCos(float x)
{
    return fastSin(x + 1.570796f);
}


