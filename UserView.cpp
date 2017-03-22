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

// 禁止拖动表头
BOOL UserView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class   
	//屏蔽两个消息通知码，使得禁止拖动List表头   
	NMHEADER* pNMHeader = (NMHEADER*)lParam;
	if (((pNMHeader->hdr.code == HDN_BEGINTRACKW) |
		(pNMHeader->hdr.code == HDN_DIVIDERDBLCLICKW)))
	{
		*pResult = TRUE;
		return TRUE;
	}

	return CWnd::OnNotify(wParam, lParam, pResult);
}

// 创建界面
int UserView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CListView::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}

	// 定义样式
	ModifyStyle(0, LVS_REPORT);

	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES);
	theCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 40);
	theCtrl.InsertColumn(1, _T("计算机名称"), LVCFMT_LEFT, 300);
	theCtrl.InsertColumn(2, _T("IP地址"), LVCFMT_LEFT, 300);

	SetTimer(2, 10000, NULL); // 设置定时器id为2
	
	return 0;
}

// 把收到的信息添加到用户信息列表
void UserView::AddUser(CString strName, CString strIp) {
	CListCtrl& theCtrl = GetListCtrl();
	int iItem = theCtrl.GetItemCount(); // 获取当前列表的行数
	
	// 如果列表中存在当前用户，则将其heartbeat设置为1，表示存活
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
	//新加的用户  heartbeat置为1  表示存活
	theCtrl.SetItemData(iItem, 1);

	return ;
}

// 查询用户
int UserView::FindUser(CString strIp) {
	CListCtrl& theCtrl = GetListCtrl();
	int iCount = theCtrl.GetItemCount();

	for (int iItem = 0; iItem < iCount; ++iItem) {
		// 获取IP地址
		CString strItmIp = theCtrl.GetItemText(iItem, 2);
		if (strItmIp.CompareNoCase(strIp) == 0) {
			return iItem;
		}
	}

	return -1;
}

// 删除不在局域网内的用户
void UserView::DelUser(CString strIp) {
	// 查找指定IP的用户
	int iItem = FindUser(strIp);
	if (iItem == -1) {
		return;
	}
	// 删除用户
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.DeleteItem(iItem);

	return;
}

// 处理heartbeat
void UserView::OnTimer(UINT nIdEvent) { // 处理heartbeat的标记
	if (nIdEvent != 2) {
		return;
	}

	CListCtrl& theCtrl = GetListCtrl();
	int iCount = theCtrl.GetItemCount();

	for (int iItem = iCount - 1; iItem >= 0; --iItem) {
		// 获取heartbeat状态
		DWORD nData = theCtrl.GetItemData(iItem);
		if (nData > 0) { // 如果heartbeat值为1 表示存活，置为0
			theCtrl.SetItemData(iItem, 0);
		}
		else { // 如果上次heartbeat值为0，本次还是0，说明已经断开，删除
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
//	//获取单击所在的行号   
//	//找出鼠标位置   
//	DWORD dwPos = GetMessagePos();
//	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
//	theCtrl.ScreenToClient(&point);
//	//定义结构体   
//	LVHITTESTINFO lvinfo;
//	lvinfo.pt = point;
//	//获取行号信息   
//	int nItem = theCtrl.HitTest(&lvinfo);
//	if (nItem != -1)
//		m_itemSel = lvinfo.iItem;   //当前行号   
//
//									//判断是否点击在CheckBox上   
//	if (lvinfo.flags == LVHT_ONITEMSTATEICON)
//		m_bHit = TRUE;
//
//	*pResult = 0;
//}

//void UserView::OnLvnItemchangedCheckbox(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	CListCtrl& theCtrl = GetListCtrl();
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	//判断m_bHit，即是否点击了CheckBox   
//	if (m_bHit)
//	{
//		m_bHit = FALSE;     //复位   
//
//		if (theCtrl.GetCheck(m_itemSel))
//		{       //CheckBox被选中   
//				//do your own processing    
//		}
//		else
//		{      //CheckBox取消选择   
//			   //do your own processing    
//		}
//	}
//
//	*pResult = 0;
//}