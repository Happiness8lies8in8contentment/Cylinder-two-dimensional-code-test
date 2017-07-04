
// CylinderDlg.cpp : 实现文件
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


// CCylinderDlg 对话框




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


// CCylinderDlg 消息处理程序

BOOL CCylinderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCylinderDlg::OnPaint()
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
HCURSOR CCylinderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCylinderDlg::ShowImage(Mat& img, int nID)//在图片控件中显示一张图片
{
	CWnd* pimgShowCtrl = this->GetDlgItem(nID); //获得nID控件的句柄
	CRect ctrlRect;		//定义变量用以保存picture控件的大小
	pimgShowCtrl->GetClientRect(&ctrlRect); //获得picture控件的大小

	CDC* pDC = pimgShowCtrl->GetDC(); //获得设备上下文，因为后面显示函数的参数中需要它

	//初始化一个位图信息头
	BITMAPINFOHEADER BHEADER = {40, 0, 0, 1, 0, BI_RGB, 0, 0, 0, 0};

	//获得传入图像的相关信息（赋值给位图信息头）
	int width, height, depth, channel, width1;
	width = img.cols;
	height = img.rows;
	depth = img.depth();
	channel = img.channels();

	int bits, colors, i;
	bits = ( 8<< (depth/2) )*channel;//8左移0、1、2、3分别代表8、16、32、64，每个像素所占的位数
	if(bits > 8)
	{
		colors = 0;//真彩色位图没有颜色表
	}
	else
	{
		colors = ( 1<<bits );//非真彩色的位图有相应的颜色表
	}

	//当真彩色图像时，让每个像素占四个字节，这样就解决了真彩色图像的4字节边界对齐问题
	if (bits == 24)
	{
		bits = 32;
	}

	//给位图信息头赋值
	//当灰度图像时，由于每个像素占一个字节，所以让每行像素（即图像的宽度）进行4字节边界对齐
	if(bits == 8)
	{
		width1 = (width*8 + 31)/32 * 4; //4字节边界对齐后的图像的宽度
		BHEADER.biWidth = width1;
	}
	else
	{
		BHEADER.biWidth = width;//真彩色图像时，图像的像素宽度还是原来图像的像素宽度
	}
	BHEADER.biHeight = height;			
	BHEADER.biBitCount = bits;

	LPBITMAPINFO lpBitsInfo = (LPBITMAPINFO) malloc(40 + 4*colors);//创建位图信息指针变量并分配内存

	memcpy(lpBitsInfo, &BHEADER, 40);//将位图信息头的数据复制到位图信息里

	//对位图信息进行颜色表的赋值
	if(colors == 256)
	{
		RGBQUAD* colorsTab = lpBitsInfo->bmiColors;
		for(i=0; i<256; i++)
		{	
			colorsTab[i].rgbBlue = colorsTab[i].rgbGreen = colorsTab[i].rgbRed = (BYTE)i;
			colorsTab[i].rgbReserved = 0;
		}	
	}

	//======颠倒数据
	//======Mat 中从上往下存，而bitmap中从下往上存。  都是从左往右，并且bitmap每一个点多占一个保留字节（针对真彩色图像，为了4字节对齐），
	//		默认255，灰度图像则不用这种对齐方法
	unsigned char *m_pDibBits;//存储图像中的数据，从下向上，从左向右
	//x行 * Y列
	int x,y; 
	unsigned char * bmpdata; // 负责行搬运
	unsigned char * imgData = img.data;
	if (bits == 8)
	{	
		m_pDibBits = new unsigned char[width1 * height];//注意此处用的是width1（对齐后的图像的像素宽度）而不是width

		//把imgData中的第一行复制到  m_pDibBits 的最后一行,依次颠倒
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width1;
			memcpy(bmpdata,imgData,width); // Mat中拷贝width个字节，不是width1
			imgData = imgData + width; // Mat中拷贝width个字节，不是width1
		}
	} 
	else if (bits == 32)
	{
		m_pDibBits = new unsigned char[ width * height*4 ];

		//把imgData中的第一行复制到  m_pDibBits 的最后一行,依次颠倒
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width*4;
			for (y = 0; y<width; y++)
			{
				memcpy(bmpdata,imgData,3);
				bmpdata[3] = 255;   // 注释掉 没有影响
				bmpdata = bmpdata+4;
				imgData = imgData+3;
			}    
		}
	}

	//显示图像部分
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

	//释放相关资源
	pimgShowCtrl->ReleaseDC(pDC);
	free(lpBitsInfo);
	delete []m_pDibBits;
}



void CCylinderDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	m_srcImg = (0,0,CV_8UC1);
	CFileDialog dlg(TRUE,_T(".bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件 (*.bmp)|*.bmp|JPEG文件 (*.jpg)|*.jpg|PNG文件 (*.png)|*.png||"));//选择图片
	if (IDOK==dlg.DoModal())//打开选择的图片
	{
		string filename=dlg.GetPathName();//获取图片的路径及文件名
		m_srcImg = imread(filename);//将图片保存至全局变量theImage对象中
	}
	ShowImage(m_srcImg, IDC_SRC_IMG);
}


void CCylinderDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE,_T(".bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件 (*.bmp)|*.bmp|JPEG文件 (*.jpg)|*.jpg|PNG文件 (*.png)|*.png||"));
	if (IDOK==dlg.DoModal())
	{
		string filename=dlg.GetPathName();//获取图片的路径及文件名
		imwrite(filename,AfterImg);//将图片保存
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
	// TODO: 在此添加控件通知处理程序代码
	Mat src = m_srcImg;

	n_imgWidth = GetDlgItemInt(IDC_EDIT1);
	n_Diameter = GetDlgItemInt(IDC_EDIT2);
	int pixel = src.cols * (n_Diameter/n_imgWidth ) ;


		 cvtColor(src, src, CV_RGB2GRAY);
		 AfterImg = Cylinder(src, pixel);

	ShowImage(AfterImg, IDC_SRC_IMG2 );
}
