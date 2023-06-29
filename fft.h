#ifndef _FFT_H
#define _FFT_H

//#ifndef _INSIDE_VISUAL_CPP_TRANSFORM
//#define _INSIDE_VISUAL_CPP_TRANSFORM
////#include"ImageCenterDib.h"


//�궨�壬PI
#define PI 3.1415926

//�������ͽṹ��
struct ComplexNumber
{
	float imag;// imaginary�鲿
	float real;//ʵ��
};

//���ٸ���Ҷ�任��
class Transform_FFT
{

public:
	//�����������캯��
	Transform_FFT();

	//��������
	~Transform_FFT();
	ComplexNumber *m_pFFTBuf;


	//һά���ٸ���Ҷ���任
	void FFT1D(ComplexNumber *arrayBuf, int n);

	//һά���ٸ���Ҷ���任
	void IFFT1D(ComplexNumber *arrayBuf, int n);


};

#endif 
