
// MFCrador_2017080511_LYLDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ChartCtrl/ChartCtrl.h"  
#include "ChartCtrl/ChartTitle.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartXYSerie.h"
#include "ChartCtrl/ChartBarSerie.h"
#include "ChartCtrl/ChartAxisLabel.h"

#define PI 3.1415926


// CMFCrador_2017080511_LYLDlg �Ի���
class CMFCrador_2017080511_LYLDlg : public CDialogEx
{
// ����
public:
	CMFCrador_2017080511_LYLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCRADOR_2017080511_LYL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnopenfile();
	CString m_strpath;
	afx_msg void OnBnClickedBtnreadfile();
	float m_Vpp;
	float m_VMax;
	float m_Vmin;
	float m_Ave;
	float m_Var;
	float m_Std_Dev;
	afx_msg void OnBnClickedBtnfreana();
	afx_msg void OnBnClickedBtnpaintpic();

	
	afx_msg void OnStnClickedStaticpic();
	
	CChartCtrl m_ChartCtrl;
	float m_centerFre;
	float m_bandWide;
	afx_msg void OnBnClickedBtnfilter();
	afx_msg void OnBnClickedRadiohamming();
	float m_wp;
	float m_ws;
	afx_msg void OnEnChangeEditcenterfre();
	afx_msg void OnBnClickedRadioinitfrewave();
	afx_msg void OnBnClickedRadiocompare();
	afx_msg void OnBnClickedBtnclear();
	float m_sampleFre;
};
