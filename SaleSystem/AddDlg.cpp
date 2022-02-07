// AddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"

// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(CAddDlg::IDD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT5, m_name2);
	DDX_Text(pDX, IDC_EDIT6, m_price2);
	DDX_Text(pDX, IDC_EDIT7, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CAddDlg ���

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg ��Ϣ�������


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

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

	// TODO:  �ڴ����ר�ô����/����û���
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			m_price1 = it->price;
			//ͬ�����ؼ���
			UpdateData(FALSE);
		}
	}

}


void CAddDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//�����Ʒ��ť����ʵ��
	//�õ���������
	UpdateData(TRUE);

	if (m_num1 <= 0)
	{
		MessageBox(TEXT("��ӵ�����Ҫ����0"));
		return;
	}


	//��ȡ����Ҫ��ӵ���Ʒ����
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			//��ӿ��
			it->num += m_num1;
			m_num1 = 0;
			UpdateData(FALSE);
			MessageBox(TEXT("��ӳɹ�"));

		}

	}
	//����Ʒͬ�����ļ�
	file.WirteDocline();




}


void CAddDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_num1 = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton5()
{
	//�õ����µ�����
	UpdateData(TRUE);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�������Ʒ
	//��֤���ݵ���Ч��
	if (m_name2.IsEmpty() || m_num2 <= 0 || m_price2 <= 0)
	{
		MessageBox(TEXT("������Ϣ����"));
		return;
	}

	CInfoFile file;
	file.ReadDocline();

	file.Addline(m_name2, m_num2, m_price2);
	file.WirteDocline();
	MessageBox(TEXT("����Ʒ��ӳɹ�"));


	//ͬ�������������
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//�����ӵ�������
	m_name2.Empty();
	m_num2 = 0; 
	m_price2 = 0;
	UpdateData(FALSE);


}


void CAddDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ȡ���������Ʒ��ť�¼�
	//�����ӵ�������
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}
