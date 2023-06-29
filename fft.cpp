#include "stdafx.h"
#include "FFT.h"
#include "math.h"
/***********************************************************************
* �������ƣ�
* Transform_FFT()
*
*˵�����޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
***********************************************************************/
Transform_FFT::Transform_FFT()
{

	m_pFFTBuf = NULL;//����Ҷ�任������Ϊ��

}



/***********************************************************************
* �������ƣ�
*   ~Transform_FFT()

*
*˵���������������ͷ���Դ
***********************************************************************/
Transform_FFT::~Transform_FFT()
{

	//�ͷŸ���Ҷ�任������
	if (m_pFFTBuf != NULL){
		delete m_pFFTBuf;
		m_pFFTBuf = NULL;
	}
}

/***********************************************************************
* �������ƣ�
* FFT1D()
*
*����������
*  ComplexNumber *arrayBuf  -�����ṹ����������
*  int n  -����arrayBuf�ĳ��ȣ�����Ϊ2���ݴη�
*
*����ֵ��
*   ��
*
*˵�����Ը����ṹ������arrayBuf����һά���ٸ���Ҷ�任���任��Ľ����
*      ���arrayBuf��
***********************************************************************/
void Transform_FFT::FFT1D(ComplexNumber *arrayBuf, int n)
{
	//ѭ������
	int i, k, r;

	//������ʱ����������buf1������Ϊn
	ComplexNumber *buf1 = new ComplexNumber[n];

	//��arrayBuf������buf1
	memcpy(buf1, arrayBuf, sizeof(ComplexNumber)*n);

	//������ʱ����������buf2������Ϊn
	ComplexNumber *buf2 = new ComplexNumber[n];

	//��arrayBuf����Ԫ�ػ�2��ȡ����������
	//��0��1��2��3��4��5��6��7�˵����жԵ������0��4��2��6��1��5��3��7
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


	//���õ����㷨���п��ٸ���Ҷ�任
	//buf1�ǵ�r�������룬buf2��ŵ�r�������
	float c, s;
	for (r = 1; pow(2.0, r) <= n; r++){
		t1 = pow(2.0, r);
		for (k = 0; k<n / t1; k++){
			for (i = t1 / 2; i<t1; i++){
				//��Ȩ����
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

		//��r�����������buf1,��Ϊ��һ������������
		memcpy(buf1, buf2, sizeof(ComplexNumber)*n);
	}


	//����Ҷ�任�Ľ������arrayBuf
	memcpy(arrayBuf, buf2, sizeof(ComplexNumber)*n);

	//�ͷŻ�����
	delete[]buf2;
	delete[]buf1;

}


/***********************************************************************
* �������ƣ�
* IFFT1D()
*
*����������
*  ComplexNumber *arrayBuf  -�����ṹ����������
*  int n  -����arrayBuf�ĳ��ȣ�����Ϊ2���ݴη�
*
*����ֵ��
*   ��
*
*˵�����Ը����ṹ������arrayBuf����һά���ٸ���Ҷ���任���任��Ľ����
*      ���arrayBuf��
***********************************************************************/
void Transform_FFT::IFFT1D(ComplexNumber *arrayBuf, int n)
{
	//����
	int i;

	//������arrayBuf����
	for (i = 0; i<n; i++)
		arrayBuf[i].imag = -arrayBuf[i].imag;

	//һά���ٸ���Ҷ�任
	FFT1D(arrayBuf, n);

	//ʱ���������������N
	for (i = 0; i<n; i++){
		arrayBuf[i].real = arrayBuf[i].real / n;
		arrayBuf[i].imag = -arrayBuf[i].imag / n;
	}

}

