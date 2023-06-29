
// MFCrador_2017080511_LYLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCrador_2017080511_LYL.h"
#include "MFCrador_2017080511_LYLDlg.h"
#include "afxdialogex.h"
#include "ChartCtrl/ChartCtrl.h"  
#include "ChartCtrl/ChartTitle.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartXYSerie.h"
#include "ChartCtrl/ChartBarSerie.h"
#include "ChartCtrl/ChartAxisLabel.h"
#include "fft.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
float n[1024];
float hd[1024];
float w_lb[1024];
float h[1024];
float Rn[1024];
float fftdata0[1024];
float fftdatashow[1024];
float Decodedata[1024];
float Im[1024];
float FirResult[2048];
float cc[2048];
float hint[1024];
float fftdata1[2048];
float FreResult[2048];
float dataed1[1024];
float f_max = 0;
float max = 0;
float wp = 0, ws = 0, B = 0, centerfre = 0;
int num2 = 0;
int num[500];
int index;
int digitp[3];
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCrador_2017080511_LYLDlg 对话框



CMFCrador_2017080511_LYLDlg::CMFCrador_2017080511_LYLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCrador_2017080511_LYLDlg::IDD, pParent)
	, m_Vpp(0)
	, m_VMax(0)
	, m_Vmin(0)
	, m_Ave(0)
	, m_Var(0)
	, m_Std_Dev(0)
	, m_centerFre(0)
	, m_bandWide(0)
	, m_wp(0)
	, m_ws(0)
	, m_sampleFre(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCrador_2017080511_LYLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITvpp, m_Vpp);
	DDX_Text(pDX, IDC_EDITmax, m_VMax);
	DDX_Text(pDX, IDC_EDITvMin, m_Vmin);
	DDX_Text(pDX, IDC_EDITAve, m_Ave);
	DDX_Text(pDX, IDC_EDITvariance, m_Var);
	DDX_Text(pDX, IDC_EDITstd_dev, m_Std_Dev);

	DDX_Control(pDX, IDC_CTMshowPic, m_ChartCtrl);
	DDX_Text(pDX, IDC_EDITcenterFre, m_centerFre);
	DDX_Text(pDX, IDC_EDITbandWide, m_bandWide);
	DDX_Text(pDX, IDC_EDITwp, m_wp);
	DDX_Text(pDX, IDC_EDITws, m_ws);
	DDX_Text(pDX, IDC_EDITsampleFre, m_sampleFre);
}

BEGIN_MESSAGE_MAP(CMFCrador_2017080511_LYLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNopenFile, &CMFCrador_2017080511_LYLDlg::OnBnClickedBtnopenfile)
	ON_BN_CLICKED(IDC_BTNreadFile, &CMFCrador_2017080511_LYLDlg::OnBnClickedBtnreadfile)
	ON_BN_CLICKED(IDC_BTNfreAna, &CMFCrador_2017080511_LYLDlg::OnBnClickedBtnfreana)
	ON_BN_CLICKED(IDC_BTNpaintPic, &CMFCrador_2017080511_LYLDlg::OnBnClickedBtnpaintpic)
	ON_STN_CLICKED(IDC_STATICpic, &CMFCrador_2017080511_LYLDlg::OnStnClickedStaticpic)
	ON_BN_CLICKED(IDC_BTNfilter, &CMFCrador_2017080511_LYLDlg::OnBnClickedBtnfilter)
	ON_BN_CLICKED(IDC_RADIOhamming, &CMFCrador_2017080511_LYLDlg::OnBnClickedRadiohamming)
	ON_EN_CHANGE(IDC_EDITcenterFre, &CMFCrador_2017080511_LYLDlg::OnEnChangeEditcenterfre)
	ON_BN_CLICKED(IDC_RADIOinitFreWave, &CMFCrador_2017080511_LYLDlg::OnBnClickedRadioinitfrewave)
	ON_BN_CLICKED(IDC_RADIOcompare, &CMFCrador_2017080511_LYLDlg::OnBnClickedRadiocompare)
	ON_BN_CLICKED(IDC_BTNclear, &CMFCrador_2017080511_LYLDlg::OnBnClickedBtnclear)
END_MESSAGE_MAP()


// CMFCrador_2017080511_LYLDlg 消息处理程序

BOOL CMFCrador_2017080511_LYLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	CChartAxis *pAxis = NULL;
	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);

	pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);
	//坐标轴

	


	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	UpdateData(true);
	m_wp = 22.5;
	m_ws = 30;
	TChartString str3;

	str3 = _T("WAVE");
	m_ChartCtrl.GetTitle()->AddString(str3);
	UpdateData(false);
	CheckRadioButton(IDC_RADIOhamming, IDC_RADIOhanning, IDC_RADIOhamming);
	CheckRadioButton(IDC_RADIOinitTimeWave, IDC_RADIOcompare, IDC_RADIOinitFreWave);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCrador_2017080511_LYLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCrador_2017080511_LYLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCrador_2017080511_LYLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
const int N = 1024;
float round1(float r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

inline void swap(float &a, float &b)
{
	float t;
	t = a;
	a = b;
	b = t;
}


void ideal_lp(float wc, float M)
{
	double tao = (M - 1) / 2;//延迟相位
	
	for (int i = 0; i<M; i++)
	{
		n[i] = i - tao;
		if ((n[i]) == 0)
		{
			hd[i] = wc / PI;
		}
		else
		{
			hd[i] = sin(wc*n[i]) / (PI*n[i]);
		}
	}

}
void hamming(float N)
{
	for (int i = 0; i<N; i++)
	{
		w_lb[i] = (0.54 - 0.46*cos(2 * PI*i / (N - 1)));
	}

}

void hanning(float N)
{
	for (int i = 0; i<N; i++)
	{
		w_lb[i] = (sin(i*PI / (N - 1)))*(sin(i*PI / (N - 1)));
	}
}

void blackman(float N)
{
	for (int i = 0; i<N; i++)
	{
		w_lb[i] = (0.42 - 0.5*cos(2 * PI*i / (N - 1)) + 0.08*cos(4 * PI*i / (N - 1)));
	}
}


void CMFCrador_2017080511_LYLDlg::OnBnClickedBtnopenfile()
{
	CString path;
	OPENFILENAME open;                     //  公共对话框。
	char file[MAX_PATH];                    // 保存文件名称的缓冲区。 
	ZeroMemory(&open, sizeof(OPENFILENAME));  // 初始化选择文件对话框
	open.lStructSize = sizeof(OPENFILENAME);  //指定这个结构的大小，以字节为单位。
	open.lpstrFile = file;                   //打开的文件的全路径
	open.lpstrFile[0] = '\0';                //第一个字符串是过滤器描述的显示字符串
	open.nMaxFile = MAX_PATH;               //指定lpstrFile缓冲的大小，以TCHARs为单位
	open.lpstrFilter = "数据文件(*.dat)\0*.dat\0所有文件(*.*)\0*.*\0\0";  //打开文件类型
	open.nFilterIndex = 1;                  //指定在文件类型控件中当前选择的过滤器的索引
	open.lpstrFileTitle = NULL;              // 指向接收选择的文件的文件名和扩展名的缓冲（不带路径信息）。这个成员可以是NULL。
	open.nMaxFileTitle = 0;                 //指定lpstrFileTitle缓冲的大小，以TCHARs为单位
	open.lpstrInitialDir = NULL;             //指向以空字符结束的字符串，可以在这个字符串中指定初始目录。
	open.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//位标记的设置，你可以使用来初始化对话框
	
	if (GetOpenFileName(&open))              // 显示打开选择文件对话框。  
	{
		path = file;
		UpdateData(TRUE);
		m_strpath = path;
		GetDlgItem(IDC_EDITfilePath)->SetWindowTextA(path);
		UpdateData(FALSE);
	}
	else
	{
		UpdateData(TRUE);
		m_strpath = "选择文件失败";
		UpdateData(FALSE);
	}

}


void CMFCrador_2017080511_LYLDlg::OnBnClickedBtnreadfile()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	float VPP[1];
	
	unsigned short data[1024];

	FILE *FF = fopen(m_strpath, "rb");
	UpdateData(FALSE);
	if (FF == NULL)
	{
		MessageBox(_T("文件内容读取失败"));
		return;
	}

	fread(VPP, 4, 1, FF);
	fread(digitp, 4, 3, FF);
	fread(data, 2, 1024, FF);

	if (digitp[0] == 3 || digitp[0] == 1)
	{
		for (int i = 0; i<1024; i++)
		{
			
			Decodedata[i] = (data[i] * VPP[0]) / 65536 - 1.6;//解码后的电压

		}
		MessageBox(_T("数据已处理。"));
	}
	else
	{
		MessageBox(_T("无法识别。"));
		return;
	}
	fclose(FF);
	
	float temp = 0, temp2 = 0, total = 0, average=0, vari=0,stddev=0;
	for (int i = 0; i < 1024; i++)
	{
		Decodedata[i]>temp ? temp = Decodedata[i]: temp = temp;//求最大值
		Decodedata[i]<temp2 ? temp2 = Decodedata[i] : temp2 = temp2;//求最小值
		total += Decodedata[i];
	}
	average = total / 1024;//求平均值
	for (int i = 0; i < 1024; i++)
	{
		vari += (Decodedata[i] - average)*(Decodedata[i] - average);
		
	}
	vari = vari / 1024;//求方差
	stddev = sqrt(vari);//求标准差

	UpdateData(TRUE);
	m_Vpp = VPP[0];//vpp显示
	m_VMax = temp;//显示最大值
	m_Vmin = temp2;//显示最小值
	m_Ave = average;//显示平均值
	m_Var = vari;//显示方差
	m_Std_Dev = stddev;//显示标准差
	UpdateData(FALSE);
	
	for (int i = 0; i<1024; i++)
	{
		dataed1[i] = Decodedata[i];
	}

}


void CMFCrador_2017080511_LYLDlg::OnBnClickedBtnfreana()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	for (int i = 0; i<1024; i++)
	{
		fftdata0[i] = 0;//取模	
	}
	
	ComplexNumber arrayBuf[1024];
	for (int i = 0; i<1024; i++)
	{
		arrayBuf[i].real = Decodedata[i];//模拟量
		arrayBuf[i].imag = 0;//取其幅度，舍弃相位
	}
	Transform_FFT fftdata;
	fftdata.FFT1D(arrayBuf, 1024);
	for (int i = 0; i<1024; i++)
	{
		fftdata0[i] = sqrt(pow(arrayBuf[i].real, 2) + pow(arrayBuf[i].imag, 2));//取模	
	}


	
	
	for (int i = 1; i<512; i++)
		//根据快速傅里叶变换（FFT）蝶形算法，计算得到的频域数据的每个点的绝对值是中心对称的，不同的是后面的e因子
	{
		fftdata0[i]>f_max ? f_max = fftdata0[i], index = i : f_max = f_max;
		
	}
	
	for (int i = 5; i < 512; i++)
	{
		
		if (fftdata0[i]>0.707*f_max&&fftdata0[i - 5]>0.707*f_max&&fftdata0[i + 5]>0.707*f_max)
		{
			num2++;
			num[num2-1] = i;
		}
		
	}
	centerfre = (100.0 / 1024.0)*num[num2 / 2];
	float sum3 = 0;
	for (int i = 0; i <512; i++)
	{
		if (fftdata0[i]>fftdata0[num[num2 / 2]] * 0.707)
			sum3++;
	}
	m_bandWide = sum3 * 100 / 1024;
	m_centerFre = centerfre;
	m_sampleFre = digitp[2]/1000000;
	for (int i = 0; i < 1024; i++)
	{

		fftdatashow[i] = fftdata0[i];
	}
	UpdateData(FALSE);
}


void CMFCrador_2017080511_LYLDlg::OnBnClickedBtnpaintpic()
{

	int id = GetCheckedRadioButton(IDC_RADIOinitTimeWave, IDC_RADIOcompare);
	switch (id)
	{
	case IDC_RADIOinitTimeWave:
	{	MessageBox(_T("时域波形"));
	double x[1024], y[1024];
	for (int i = 0; i < 1024; i++)
	{
		x[i] = (1.0/100.0)*i;
		y[i] = dataed1[i];

	}

	m_ChartCtrl.EnableRefresh(true);
	CChartAxisLabel* pLabel = NULL;
	CChartAxis *pAxis = NULL;
	TChartString str1 = _T("mag/V");
	pAxis = m_ChartCtrl.GetLeftAxis();
	if (pAxis)
		pLabel = pAxis->GetLabel();
	if (pLabel)
		pLabel->SetText(str1);
	str1 = _T("Time/us");
	pAxis = m_ChartCtrl.GetBottomAxis();
	if (pAxis)
		pLabel = pAxis->GetLabel();
	if (pLabel)
		pLabel->SetText(str1);
	CChartLineSerie *pLineSerie1;
	m_ChartCtrl.RemoveAllSeries();//先清空  
	pLineSerie1 = m_ChartCtrl.CreateLineSerie();
	pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序  
	pLineSerie1->AddPoints(x, y, 1024);
	break; 
	}
	case IDC_RADIOinitFreWave:
		MessageBox(_T("频域波形"));
		{

			double x[512], y[512];
			for (int i = 0; i < 512; i++)
			{
				x[i] = (100.0 / 1024.0)*(i);
				y[i] = 20 * log(fftdatashow[i] / f_max);
				
			}

			m_ChartCtrl.EnableRefresh(true);
			CChartAxisLabel* pLabel = NULL;
			CChartAxis *pAxis = NULL;
			TChartString str1 = _T("mag/db");
			pAxis = m_ChartCtrl.GetLeftAxis();
			if (pAxis)
				pLabel = pAxis->GetLabel();
			if (pLabel)
				pLabel->SetText(str1);
			str1 = _T("frequence/MHz");
			pAxis = m_ChartCtrl.GetBottomAxis();
			if (pAxis)
				pLabel = pAxis->GetLabel();
			if (pLabel)
				pLabel->SetText(str1);
			CChartLineSerie *pLineSerie1;
			m_ChartCtrl.RemoveAllSeries();//先清空  
			pLineSerie1 = m_ChartCtrl.CreateLineSerie();
			pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序  
			pLineSerie1->AddPoints(x, y, 512);







		}
		break;
	case IDC_RADIOfilterOutWave:
		MessageBox(_T("滤波后频域波形"));

		{
		
			double x[512], y[512];
			for (int i = 0; i < 512; i++)
			{
				x[i] = (100.0 / 1024.0)*(i);
				y[i] = 20 * log(FreResult[i] / max);
				
			}

			m_ChartCtrl.EnableRefresh(true);
			CChartAxisLabel* pLabel = NULL;
			CChartAxis *pAxis = NULL;
			TChartString str1 = _T("mag/db");
			pAxis = m_ChartCtrl.GetLeftAxis();
			if (pAxis)
				pLabel = pAxis->GetLabel();
			if (pLabel)
				pLabel->SetText(str1);
			str1 = _T("frequence/MHz");
			pAxis = m_ChartCtrl.GetBottomAxis();
			if (pAxis)
				pLabel = pAxis->GetLabel();
			if (pLabel)
				pLabel->SetText(str1);
			CChartLineSerie *pLineSerie1;
			m_ChartCtrl.RemoveAllSeries();//先清空  
			pLineSerie1 = m_ChartCtrl.CreateLineSerie();
			pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序  
			pLineSerie1->AddPoints(x, y, 512);

		
		}


		break;

	

	case IDC_RADIOcompare:
		MessageBox(_T("两频域比较"));
		{
			
		
			double x[512], y[512];
			for (int i = 0; i < 512; i++)
			{
				x[i] = (100.0 / 1024.0)*(i);
				y[i] = 20 * log(FreResult[i] / max);
				
			}
			CChartLineSerie *pLineSerie1;
			
			pLineSerie1 = m_ChartCtrl.CreateLineSerie();
			pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序
			pLineSerie1->AddPoints(x, y, 512);
			TChartStringStream strs1;
			strs1 << _T("这是IDC_ChartCtrl1的第")
				<< m_ChartCtrl.GetSeriesCount()
				<< _T("条曲线");
			pLineSerie1->SetName(strs1.str());

		

		
		}
		break;
	}
	
}


void CMFCrador_2017080511_LYLDlg::OnStnClickedStaticpic()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CMFCrador_2017080511_LYLDlg::OnBnClickedBtnfilter()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	float wp = (m_wp / 100) * 2 * PI, ws = (m_ws / 100) * 2*PI;   //需要根据实际信号频率重新设置
	UpdateData(FALSE);
	float trwidth = ws - wp;                        //过渡带宽度
	int nid = GetCheckedRadioButton(IDC_RADIOhamming, IDC_RADIOhanning);
	int N1=0;
	switch (nid)
	{

	case IDC_RADIOhamming:
		 N1 = ceil(6.64*PI / trwidth) ;            //滤波器的长度;
		 if (N1 / 2 == 0)
		 {
			 N1 + 1;
		 }
		 break;
	case IDC_RADIOblackman:
		 N1 = ceil(11*PI / trwidth);
		 if (N1 / 2 == 0)
		 {
			 N1 + 1;
		 }
		break;
	case IDC_RADIOhanning:
		 N1 = ceil(6.2* PI / trwidth) ;
		 if (N1 / 2 == 0)
		 {
			 N1 + 1;
		 }
		break;
	default:
		break;
	}


	
	
	
	float wc = (ws + wp) / 2;
	ideal_lp(wc, N1);
	
	//开始选择滤波器
	switch (nid)
	{

	case IDC_RADIOhamming:
		hamming(N1);
		break;
	case IDC_RADIOblackman:
		blackman(N1);;
		break;
	case IDC_RADIOhanning:
		hanning(N1);
		break;
	default:
		break;
	}
	for (int i = 0; i < N1; i++)
	{

		Rn[i] = 1;
	}
	//选择完毕
	for (int i = 0; i<N1; i++)
	{
		h[i] = hd[i] * w_lb[i] *100000 ;//*10^5
	}
	for (int i = 0; i<N1; i++)
	{
		hint[i] = round(h[i]);
	}
	//卷积
	for (int n = 0; n<2048; n++)
	{
		FirResult[n] = 0;
	}
	int j = 0;
	for (int n = 0; n<1024 + N1 - 1; n++)
	{
		FirResult[n] = 0;
		for (j = 0; j<1024; j++)
		{
			if ((n - j) >= 0 && (n - j)<N1)//
			{
				FirResult[n] = dataed1[j] * hint[n - j] + FirResult[n];
			}
		}
	}
	ComplexNumber arrayBuf[2048];
	for (int i = 0; i<2048; i++)
	{
		arrayBuf[i].real = FirResult[i];//模拟量
		arrayBuf[i].imag = 0;//取其幅度，舍弃相位
	}
	Transform_FFT fftdata;
	fftdata.FFT1D(arrayBuf, 1024);
	for (int i = 0; i<1024; i++)
	{
		FreResult[i] = sqrt(pow(arrayBuf[i].real, 2) + pow(arrayBuf[i].imag, 2));//取模	
	}
	
	int index;

	for (int i = 1; i<512; i++)
		//根据快速傅里叶变换（FFT）蝶形算法，计算得到的频域数据的每个点的绝对值是中心对称的，不同的是后面的e因子
	{
		FreResult[i]>max ? max = FreResult[i], index = i : max = max;

	}

	

}


void CMFCrador_2017080511_LYLDlg::OnBnClickedRadiohamming()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCrador_2017080511_LYLDlg::OnEnChangeEditcenterfre()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCrador_2017080511_LYLDlg::OnBnClickedRadioinitfrewave()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCrador_2017080511_LYLDlg::OnBnClickedRadiocompare()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCrador_2017080511_LYLDlg::OnBnClickedBtnclear()
{
	// TODO:  在此添加控件通知处理程序代码

	m_ChartCtrl.EnableRefresh(true);
	CChartLineSerie *pLineSerie1;
	m_ChartCtrl.RemoveAllSeries();//先清空  
	pLineSerie1 = m_ChartCtrl.CreateLineSerie();
	pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序  
	
}
