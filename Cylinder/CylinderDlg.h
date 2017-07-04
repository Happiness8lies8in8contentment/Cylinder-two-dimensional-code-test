
// CylinderDlg.h : 头文件
//

#pragma once
#include "opencv2/opencv.hpp"
using namespace cv;

// CCylinderDlg 对话框
class CCylinderDlg : public CDialogEx
{
// 构造
public:
	CCylinderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CYLINDER_DIALOG };

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
	Mat m_srcImg, AfterImg;
public:
	void ShowImage(Mat& img, int nID);

	afx_msg void OnBnClickedButtonOpen();

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedBtnJc();
	Mat Cylinder(Mat &image,double d);
	int n_Diameter;
	int n_imgWidth;
};
