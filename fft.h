#ifndef _FFT_H
#define _FFT_H

//#ifndef _INSIDE_VISUAL_CPP_TRANSFORM
//#define _INSIDE_VISUAL_CPP_TRANSFORM
////#include"ImageCenterDib.h"


//宏定义，PI
#define PI 3.1415926

//复数类型结构体
struct ComplexNumber
{
	float imag;// imaginary虚部
	float real;//实部
};

//快速傅立叶变换类
class Transform_FFT
{

public:
	//不带参数构造函数
	Transform_FFT();

	//析构函数
	~Transform_FFT();
	ComplexNumber *m_pFFTBuf;


	//一维快速傅立叶正变换
	void FFT1D(ComplexNumber *arrayBuf, int n);

	//一维快速傅立叶反变换
	void IFFT1D(ComplexNumber *arrayBuf, int n);


};

#endif 
