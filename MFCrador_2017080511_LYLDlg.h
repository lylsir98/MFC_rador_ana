
// MFCrador_2017080511_LYLDlg.h : 头文件
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


// CMFCrador_2017080511_LYLDlg 对话框
class CMFCrador_2017080511_LYLDlg : public CDialogEx
{
// 构造
public:
	CMFCrador_2017080511_LYLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCRADOR_2017080511_LYL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
