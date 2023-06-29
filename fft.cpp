#include "stdafx.h"
#include "FFT.h"
#include "math.h"
/***********************************************************************
* 函数名称：
* Transform_FFT()
*
*说明：无参数的构造函数，对成员变量进行初始化
***********************************************************************/
Transform_FFT::Transform_FFT()
{

	m_pFFTBuf = NULL;//傅立叶变换缓冲区为空

}



/***********************************************************************
* 函数名称：
*   ~Transform_FFT()

*
*说明：析构函数，释放资源
***********************************************************************/
Transform_FFT::~Transform_FFT()
{

	//释放傅立叶变换缓冲区
	if (m_pFFTBuf != NULL){
		delete m_pFFTBuf;
		m_pFFTBuf = NULL;
	}
}

/***********************************************************************
* 函数名称：
* FFT1D()
*
*函数参数：
*  ComplexNumber *arrayBuf  -复数结构体类型数组
*  int n  -数组arrayBuf的长度，必须为2的幂次方
*
*返回值：
*   无
*
*说明：对复数结构体数组arrayBuf进行一维快速傅立叶变换，变换后的结果仍
*      存回arrayBuf中
***********************************************************************/
void Transform_FFT::FFT1D(ComplexNumber *arrayBuf, int n)
{
	//循环变量
	int i, k, r;

	//申请临时复数缓冲区buf1，长度为n
	ComplexNumber *buf1 = new ComplexNumber[n];

	//将arrayBuf拷贝进buf1
	memcpy(buf1, arrayBuf, sizeof(ComplexNumber)*n);

	//申请临时复数缓冲区buf2，长度为n
	ComplexNumber *buf2 = new ComplexNumber[n];

	//将arrayBuf数组元素基2抽取并重新排列
	//若0、1、2、3、4、5、6、7八点序列对调后变作0、4、2、6、1、5、3、7
	int t1, t2;
	for (r = 1; pow(2.0, r)<n; r++){
		t1 = pow(2.0, r);
		t2 = pow(2.0, r - 1);
		for (k = 0; k<t1; k++){
			for (i = 0; i<n / t1; i++){
				buf2[k*n / t1 + i].real = buf1[k / 2 * n / t2 + i * 2 + k % 2].real;
				buf2[k*n / t1 + i].imag = buf1[k / 2 * n / t2 + i * 2 + k % 2].imag;
			}
		}
		memcpy(buf1, buf2, sizeof(ComplexNumber)*n);
	}


	//采用蝶型算法进行快速傅立叶变换
	//buf1是第r级的输入，buf2存放第r级的输出
	float c, s;
	for (r = 1; pow(2.0, r) <= n; r++){
		t1 = pow(2.0, r);
		for (k = 0; k<n / t1; k++){
			for (i = t1 / 2; i<t1; i++){
				//加权因子
				c = cos(-2 * PI*(i - t1 / 2) / t1);
				s = sin(-2 * PI*(i - t1 / 2) / t1);
				buf1[k*t1 + i].real = buf2[k*t1 + i].real*c - buf2[k*t1 + i].imag*s;
				buf1[k*t1 + i].imag = buf2[k*t1 + i].imag*c + buf2[k*t1 + i].real*s;
			}
		}
		for (k = 0; k<n / t1; k++){
			for (i = 0; i<t1 / 2; i++){
				buf2[k*t1 + i].real = buf1[k*t1 + i].real + buf1[k*t1 + i + t1 / 2].real;
				buf2[k*t1 + i].imag = buf1[k*t1 + i].imag + buf1[k*t1 + i + t1 / 2].imag;
			}
			for (i = t1 / 2; i<t1; i++){
				buf2[k*t1 + i].real = buf1[k*t1 + i - t1 / 2].real - buf1[k*t1 + i].real;
				buf2[k*t1 + i].imag = buf1[k*t1 + i - t1 / 2].imag - buf1[k*t1 + i].imag;
			}
		}

		//第r级的输出存入buf1,作为下一级的输入数据
		memcpy(buf1, buf2, sizeof(ComplexNumber)*n);
	}


	//傅立叶变换的结果存入arrayBuf
	memcpy(arrayBuf, buf2, sizeof(ComplexNumber)*n);

	//释放缓冲区
	delete[]buf2;
	delete[]buf1;

}


/***********************************************************************
* 函数名称：
* IFFT1D()
*
*函数参数：
*  ComplexNumber *arrayBuf  -复数结构体类型数组
*  int n  -数组arrayBuf的长度，必须为2的幂次方
*
*返回值：
*   无
*
*说明：对复数结构体数组arrayBuf进行一维快速傅立叶反变换，变换后的结果仍
*      存回arrayBuf中
***********************************************************************/
void Transform_FFT::IFFT1D(ComplexNumber *arrayBuf, int n)
{
	//变量
	int i;

	//对数组arrayBuf求共轭
	for (i = 0; i<n; i++)
		arrayBuf[i].imag = -arrayBuf[i].imag;

	//一维快速傅立叶变换
	FFT1D(arrayBuf, n);

	//时域数据求共轭，并除以N
	for (i = 0; i<n; i++){
		arrayBuf[i].real = arrayBuf[i].real / n;
		arrayBuf[i].imag = -arrayBuf[i].imag / n;
	}

}

