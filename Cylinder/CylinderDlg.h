
// CylinderDlg.h : ͷ�ļ�
//

#pragma once
#include "opencv2/opencv.hpp"
using namespace cv;

// CCylinderDlg �Ի���
class CCylinderDlg : public CDialogEx
{
// ����
public:
	CCylinderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CYLINDER_DIALOG };

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
