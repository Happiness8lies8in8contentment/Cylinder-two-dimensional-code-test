
// CylinderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cylinder.h"
#include "CylinderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCylinderDlg �Ի���




CCylinderDlg::CCylinderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCylinderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCylinderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCylinderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCylinderDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCylinderDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BTN_JC, &CCylinderDlg::OnBnClickedBtnJc)
END_MESSAGE_MAP()


// CCylinderDlg ��Ϣ�������

BOOL CCylinderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCylinderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCylinderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCylinderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCylinderDlg::ShowImage(Mat& img, int nID)//��ͼƬ�ؼ�����ʾһ��ͼƬ
{
	CWnd* pimgShowCtrl = this->GetDlgItem(nID); //���nID�ؼ��ľ��
	CRect ctrlRect;		//����������Ա���picture�ؼ��Ĵ�С
	pimgShowCtrl->GetClientRect(&ctrlRect); //���picture�ؼ��Ĵ�С

	CDC* pDC = pimgShowCtrl->GetDC(); //����豸�����ģ���Ϊ������ʾ�����Ĳ�������Ҫ��

	//��ʼ��һ��λͼ��Ϣͷ
	BITMAPINFOHEADER BHEADER = {40, 0, 0, 1, 0, BI_RGB, 0, 0, 0, 0};

	//��ô���ͼ��������Ϣ����ֵ��λͼ��Ϣͷ��
	int width, height, depth, channel, width1;
	width = img.cols;
	height = img.rows;
	depth = img.depth();
	channel = img.channels();

	int bits, colors, i;
	bits = ( 8<< (depth/2) )*channel;//8����0��1��2��3�ֱ����8��16��32��64��ÿ��������ռ��λ��
	if(bits > 8)
	{
		colors = 0;//���ɫλͼû����ɫ��
	}
	else
	{
		colors = ( 1<<bits );//�����ɫ��λͼ����Ӧ����ɫ��
	}

	//�����ɫͼ��ʱ����ÿ������ռ�ĸ��ֽڣ������ͽ�������ɫͼ���4�ֽڱ߽��������
	if (bits == 24)
	{
		bits = 32;
	}

	//��λͼ��Ϣͷ��ֵ
	//���Ҷ�ͼ��ʱ������ÿ������ռһ���ֽڣ�������ÿ�����أ���ͼ��Ŀ�ȣ�����4�ֽڱ߽����
	if(bits == 8)
	{
		width1 = (width*8 + 31)/32 * 4; //4�ֽڱ߽������ͼ��Ŀ��
		BHEADER.biWidth = width1;
	}
	else
	{
		BHEADER.biWidth = width;//���ɫͼ��ʱ��ͼ������ؿ�Ȼ���ԭ��ͼ������ؿ��
	}
	BHEADER.biHeight = height;			
	BHEADER.biBitCount = bits;

	LPBITMAPINFO lpBitsInfo = (LPBITMAPINFO) malloc(40 + 4*colors);//����λͼ��Ϣָ������������ڴ�

	memcpy(lpBitsInfo, &BHEADER, 40);//��λͼ��Ϣͷ�����ݸ��Ƶ�λͼ��Ϣ��

	//��λͼ��Ϣ������ɫ��ĸ�ֵ
	if(colors == 256)
	{
		RGBQUAD* colorsTab = lpBitsInfo->bmiColors;
		for(i=0; i<256; i++)
		{	
			colorsTab[i].rgbBlue = colorsTab[i].rgbGreen = colorsTab[i].rgbRed = (BYTE)i;
			colorsTab[i].rgbReserved = 0;
		}	
	}

	//======�ߵ�����
	//======Mat �д������´棬��bitmap�д������ϴ档  ���Ǵ������ң�����bitmapÿһ�����ռһ�������ֽڣ�������ɫͼ��Ϊ��4�ֽڶ��룩��
	//		Ĭ��255���Ҷ�ͼ���������ֶ��뷽��
	unsigned char *m_pDibBits;//�洢ͼ���е����ݣ��������ϣ���������
	//x�� * Y��
	int x,y; 
	unsigned char * bmpdata; // �����а���
	unsigned char * imgData = img.data;
	if (bits == 8)
	{	
		m_pDibBits = new unsigned char[width1 * height];//ע��˴��õ���width1��������ͼ������ؿ�ȣ�������width

		//��imgData�еĵ�һ�и��Ƶ�  m_pDibBits �����һ��,���εߵ�
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width1;
			memcpy(bmpdata,imgData,width); // Mat�п���width���ֽڣ�����width1
			imgData = imgData + width; // Mat�п���width���ֽڣ�����width1
		}
	} 
	else if (bits == 32)
	{
		m_pDibBits = new unsigned char[ width * height*4 ];

		//��imgData�еĵ�һ�и��Ƶ�  m_pDibBits �����һ��,���εߵ�
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width*4;
			for (y = 0; y<width; y++)
			{
				memcpy(bmpdata,imgData,3);
				bmpdata[3] = 255;   // ע�͵� û��Ӱ��
				bmpdata = bmpdata+4;
				imgData = imgData+3;
			}    
		}
	}

	//��ʾͼ�񲿷�
	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	int w = min(img.cols,ctrlRect.Width());
	int h = min(img.rows,ctrlRect.Height());

	StretchDIBits(pDC->GetSafeHdc(),
		0,
		0,
		w,
		h,
		0,
		0,
		width,
		height,
		m_pDibBits,
		lpBitsInfo,
		DIB_RGB_COLORS,
		SRCCOPY);

	//�ͷ������Դ
	pimgShowCtrl->ReleaseDC(pDC);
	free(lpBitsInfo);
	delete []m_pDibBits;
}



void CCylinderDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_srcImg = (0,0,CV_8UC1);
	CFileDialog dlg(TRUE,_T(".bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ� (*.bmp)|*.bmp|JPEG�ļ� (*.jpg)|*.jpg|PNG�ļ� (*.png)|*.png||"));//ѡ��ͼƬ
	if (IDOK==dlg.DoModal())//��ѡ���ͼƬ
	{
		string filename=dlg.GetPathName();//��ȡͼƬ��·�����ļ���
		m_srcImg = imread(filename);//��ͼƬ������ȫ�ֱ���theImage������
	}
	ShowImage(m_srcImg, IDC_SRC_IMG);
}


void CCylinderDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE,_T(".bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ� (*.bmp)|*.bmp|JPEG�ļ� (*.jpg)|*.jpg|PNG�ļ� (*.png)|*.png||"));
	if (IDOK==dlg.DoModal())
	{
		string filename=dlg.GetPathName();//��ȡͼƬ��·�����ļ���
		imwrite(filename,AfterImg);//��ͼƬ����
	}
}
Mat CCylinderDlg::Cylinder(Mat &image,double d)
{

	int nr = image.rows;//hang
	int nc = image.cols;//lie
	double r = d / 2;
	double x =r * asin(nc/(2*r));
	int dr = nr;
	int dc = 2 * x;

	Mat dst(dr,dc,CV_8UC1);

	for (int j = 0; j < dr; j++)

	{
		uchar* data = dst.ptr<uchar>(j);
		uchar* data1 = image.ptr<uchar>(j);
		for (int i = 0; i < x; i ++)
		{
			int m ;
			double gap;
			gap = x - i;
			m = r * sin(gap/r);
			data[i] = data1[nc/2 - m]; 
		}
		for (int i = x; i < dc; i++)
		{
			int n = r * sin((i - x)/r);
			data[i] = data1[nc/2 + n];
		}

	}
	return dst;
}


void CCylinderDlg::OnBnClickedBtnJc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Mat src = m_srcImg;

	n_imgWidth = GetDlgItemInt(IDC_EDIT1);
	n_Diameter = GetDlgItemInt(IDC_EDIT2);
	int pixel = src.cols * (n_Diameter/n_imgWidth ) ;


		 cvtColor(src, src, CV_RGB2GRAY);
		 AfterImg = Cylinder(src, pixel);

	ShowImage(AfterImg, IDC_SRC_IMG2 );
}
