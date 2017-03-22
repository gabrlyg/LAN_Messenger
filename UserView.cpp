#include "stdafx.h"
#include "UserView.h"
#include "MainFrm.h"
#include <iostream>

IMPLEMENT_DYNCREATE(UserView, CListView)

UserView::UserView(){
}


UserView::~UserView(){}

BEGIN_MESSAGE_MAP(UserView, CListView)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void UserView::OnDraw(CDC* pDC) {
	CDocument* pDoc = GetDocument();

	return ;
}

// ��ֹ�϶���ͷ
BOOL UserView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class   
	//����������Ϣ֪ͨ�룬ʹ�ý�ֹ�϶�List��ͷ   
	NMHEADER* pNMHeader = (NMHEADER*)lParam;
	if (((pNMHeader->hdr.code == HDN_BEGINTRACKW) |
		(pNMHeader->hdr.code == HDN_DIVIDERDBLCLICKW)))
	{
		*pResult = TRUE;
		return TRUE;
	}

	return CWnd::OnNotify(wParam, lParam, pResult);
}

// ��������
int UserView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CListView::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}

	// ������ʽ
	ModifyStyle(0, LVS_REPORT);

	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES);
	theCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 40);
	theCtrl.InsertColumn(1, _T("���������"), LVCFMT_LEFT, 300);
	theCtrl.InsertColumn(2, _T("IP��ַ"), LVCFMT_LEFT, 300);

	SetTimer(2, 10000, NULL); // ���ö�ʱ��idΪ2
	
	return 0;
}

// ���յ�����Ϣ��ӵ��û���Ϣ�б�
void UserView::AddUser(CString strName, CString strIp) {
	CListCtrl& theCtrl = GetListCtrl();
	int iItem = theCtrl.GetItemCount(); // ��ȡ��ǰ�б������
	
	// ����б��д��ڵ�ǰ�û�������heartbeat����Ϊ1����ʾ���
	if (FindUser(strIp) != -1) {
		theCtrl.SetItemData(iItem, 1);
		return;
	}
	/////////////////////
	//AfxMessageBox(strName);
	/////////////////////
	iItem = theCtrl.InsertItem(iItem, NULL);
	theCtrl.SetItemText(iItem, 1, strName);
	theCtrl.SetItemText(iItem, 2, strIp);
	//�¼ӵ��û�  heartbeat��Ϊ1  ��ʾ���
	theCtrl.SetItemData(iItem, 1);

	return ;
}

// ��ѯ�û�
int UserView::FindUser(CString strIp) {
	CListCtrl& theCtrl = GetListCtrl();
	int iCount = theCtrl.GetItemCount();

	for (int iItem = 0; iItem < iCount; ++iItem) {
		// ��ȡIP��ַ
		CString strItmIp = theCtrl.GetItemText(iItem, 2);
		if (strItmIp.CompareNoCase(strIp) == 0) {
			return iItem;
		}
	}

	return -1;
}

// ɾ�����ھ������ڵ��û�
void UserView::DelUser(CString strIp) {
	// ����ָ��IP���û�
	int iItem = FindUser(strIp);
	if (iItem == -1) {
		return;
	}
	// ɾ���û�
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.DeleteItem(iItem);

	return;
}

// ����heartbeat
void UserView::OnTimer(UINT nIdEvent) { // ����heartbeat�ı��
	if (nIdEvent != 2) {
		return;
	}

	CListCtrl& theCtrl = GetListCtrl();
	int iCount = theCtrl.GetItemCount();

	for (int iItem = iCount - 1; iItem >= 0; --iItem) {
		// ��ȡheartbeat״̬
		DWORD nData = theCtrl.GetItemData(iItem);
		if (nData > 0) { // ���heartbeatֵΪ1 ��ʾ����Ϊ0
			theCtrl.SetItemData(iItem, 0);
		}
		else { // ����ϴ�heartbeatֵΪ0�����λ���0��˵���Ѿ��Ͽ���ɾ��
			theCtrl.DeleteItem(iItem);
		}
	}
	CListView::OnTimer(nIdEvent);

	return ;
}

//int* UserView::GetNumber()
//{
//	CListCtrl& theCtrl = GetListCtrl();
//	int iCount = theCtrl.GetItemCount();
//	int res[128] = {0};
//	int cnt = 0;
//
//	for (int iItem = 0; iItem < iCount; ++iItem) {
//		//int charge = theCtrl.GetCheck(iItem);
//		if (theCtrl.GetCheck(iItem)) {
//			res[cnt++] = iItem;
//		}
//	}
//
//	return res;
//}

//void UserView::OnNMClickCheckbox(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	CListCtrl& theCtrl = GetListCtrl();
//	//��ȡ�������ڵ��к�   
//	//�ҳ����λ��   
//	DWORD dwPos = GetMessagePos();
//	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
//	theCtrl.ScreenToClient(&point);
//	//����ṹ��   
//	LVHITTESTINFO lvinfo;
//	lvinfo.pt = point;
//	//��ȡ�к���Ϣ   
//	int nItem = theCtrl.HitTest(&lvinfo);
//	if (nItem != -1)
//		m_itemSel = lvinfo.iItem;   //��ǰ�к�   
//
//									//�ж��Ƿ�����CheckBox��   
//	if (lvinfo.flags == LVHT_ONITEMSTATEICON)
//		m_bHit = TRUE;
//
//	*pResult = 0;
//}

//void UserView::OnLvnItemchangedCheckbox(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	CListCtrl& theCtrl = GetListCtrl();
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	//�ж�m_bHit�����Ƿ�����CheckBox   
//	if (m_bHit)
//	{
//		m_bHit = FALSE;     //��λ   
//
//		if (theCtrl.GetCheck(m_itemSel))
//		{       //CheckBox��ѡ��   
//				//do your own processing    
//		}
//		else
//		{      //CheckBoxȡ��ѡ��   
//			   //do your own processing    
//		}
//	}
//
//	*pResult = 0;
//}