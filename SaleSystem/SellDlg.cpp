// SellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(CSellDlg::IDD)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_left);
	DDX_Text(pDX, IDC_EDIT5, m_num);
	DDX_Text(pDX, IDC_EDIT4, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSellDlg ���

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg ��Ϣ�������


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	//��ʼ����Ϣ��������

	//��ʼ��������
	
	CInfoFile file;
	//����Ʒ����file������
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		//������Ʒ����  ���������Ʒŵ���������

		//it->name �� string  AddString(CString )
		// string  -> CString

		m_combo.AddString(CString(it->name.c_str()));
	}

	//Ĭ��ѡ�е�һ����Ʒ
	m_combo.SetCurSel(0);

	OnCbnSelchangeCombo1();//���µ�һ����Ʒ�������

}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�л���Ʒ �������¼�


	//�Ȼ�ȡ����Ʒ������

	int index = m_combo.GetCurSel();
	//����������ȡ����������
	CString name;
	m_combo.GetLBText(index, name);

	//������Ʒ���ƻ�ȡ������Ʒ�ļ۸�Ϳ�� ������ʾ���ؼ���
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{
			m_price = it->price;
			m_left = it->num;
			//ͬ�����ؼ���
			UpdateData(FALSE);
		}
	}



}


void CSellDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//����Ĺ���ʵ��
	if (m_num <= 0)
	{
		MessageBox(TEXT("��������Ҫ����0"));
		return;
	}
	//��������� ���ܴ��ڿ��
	if (m_num > m_left)
	{
		MessageBox(TEXT("�����������ܴ��ڿ����"));
		return;
	}
	//��鹺�������Ƿ�ΪС��
	if (m_num-(int)m_num)
	{
		MessageBox(TEXT("������������ΪС��"));
		return;
	}

	//����
	//��ȡ������Ҫ�����Ʒ����
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ( (CString)it->name.c_str() == name)
		{
			//ͬ�������
			it->num -= m_num;
			m_left = it->num; //�ؼ��ϵĿ����
			//�����û�����Ĺ�����Ϣ

			CString str;
			str.Format(_T("��Ʒ��%s \r\n���ۣ�%d \r\n������%d \r\n�ܼۣ�%d"), name, m_price, m_num, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(TEXT("����ɹ�"));
		}
	}
	
	//�����µ�����д���ļ���
	file.WirteDocline();

	//�������
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);

	 
}


void CSellDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ȡ����ť
	m_num = 0;
	UpdateData(FALSE);
	//Ĭ��ѡ�е�һ��
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();//���µ�һ����Ʒ�������

}
