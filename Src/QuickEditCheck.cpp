#include "QuickEditCheck.h"
#include "RegOperator.h"
#include "ConsoleUI.h"
#include "ConsoleComCtrl.h"

using namespace GL;

void StringReplace(std::string &strBase, const std::string& strSrc, const std::string& strDes)
{
	std::string::size_type pos = 0;
	std::string::size_type srcLen = strSrc.size();
	std::string::size_type desLen = strDes.size();
	pos = strBase.find(strSrc, pos);
	while ((pos != std::string::npos))
	{
		strBase.replace(pos, srcLen, strDes);
		pos = strBase.find(strSrc, (pos + desLen));
	}
}

Timer timerPaoma;
std::atomic<bool> drawing = false;

class EventSelectMemu
	: public Event
{
public:
	EventSelectMemu(ConsoleUI *consoleUI = NULL)
	{
		setConsoleUI(consoleUI);
		m_nSel = 0;

		m_txtColorNormal = white;
		m_bkColorNormal = gray;

		m_txtColorSel = red;
		m_bkColorSel = blue;
	}

	void addControl(Control* pCtrl)
	{
		m_vctBts.push_back(pCtrl);
	}

	void refreshButtons()
	{
		timerPaoma.Pause();
		while (drawing) 
			Sleep(1);

		for (int i = 0; i<m_vctBts.size(); ++i)
		{
			if (i == m_nSel)
			{
				m_vctBts[i]->setTextColor(m_txtColorSel);
				m_vctBts[i]->setBkColor(m_bkColorSel);
			}
			else
			{
				m_vctBts[i]->setTextColor(m_txtColorNormal);
				m_vctBts[i]->setBkColor(m_bkColorNormal);
			}

			consoleUI()->redrawControl(m_vctBts[i]);
		}

		timerPaoma.Resume();
	}

protected:
	virtual EVENT_TYPE eventType()
	{
		return KEY_EVENT;
	}

	virtual void onEvent(INPUT_RECORD &input_record)
	{
		if (KEY_EVENT == input_record.EventType)
		{
			if (!input_record.Event.KeyEvent.bKeyDown)
			{
				return;
			}

			WORD k = (input_record.Event.KeyEvent.wVirtualKeyCode);
			switch (k)
			{
			case 38://��
			case 37://��
			{
				m_nSel = (m_nSel==0) ? m_vctBts.size()-1 : (m_nSel-1) % m_vctBts.size();
				refreshButtons();
				break;
			}
			case 40://��			
			case 39://��
			{
				m_nSel = (m_nSel + 1) % m_vctBts.size();
				refreshButtons();
				break;
			}
			case 13://�س�
			{
				if (m_nSel < 0 || m_nSel >= m_vctBts.size())
					break;

				if (m_vctBts[m_nSel]->getID() == "RESTART")
				{
					goto RESTART;
				}
				else if (m_vctBts[m_nSel]->getID() == "IGNORE")
				{
					goto CONTINUE;
				}				
				break;
			}
			case 82://R
			{
			RESTART:
				//MessageBoxA(NULL, "restart", "msg", 0);
				CRegOperator reg(HKEY_CURRENT_USER);
				std::string sExePath(MAX_PATH, '\0');
				GetModuleFileNameA(NULL, &(sExePath[0]), MAX_PATH);
				StringReplace(sExePath, "\\", "_");
				StringReplace(sExePath, "/", "_");
				sExePath = "Console\\" + sExePath;
				reg.CreateKey(sExePath.c_str());
				reg.Write("QuickEdit", (DWORD)0);
				reg.Close();
				
				//std::string sExe = GetCommandLineA();
				//STARTUPINFOA si;
				//PROCESS_INFORMATION pi;
				//ZeroMemory(&si, sizeof(si));
				//ZeroMemory(&pi, sizeof(pi));
				////����һ���½���  
				//if (::CreateProcessA(
				//	NULL,							  //  ָ��һ��NULL��β�ġ�����ָ����ִ��ģ��Ŀ��ֽ��ַ���  
				//	const_cast<char *>(sExe.c_str()), // �������ַ���  
				//	NULL,	//    ָ��һ��SECURITY_ATTRIBUTES�ṹ�壬����ṹ������Ƿ񷵻صľ�����Ա��ӽ��̼̳С�  
				//	NULL,	//    ���lpProcessAttributes����Ϊ�գ�NULL������ô������ܱ��̳С�<ͬ��>  
				//	false,	//    ָʾ�½����Ƿ�ӵ��ý��̴��̳��˾����   
				//	0,		//  ָ�����ӵġ���������������ͽ��̵Ĵ����ı�  
				//			//  CREATE_NEW_CONSOLE  �¿���̨���ӽ���  
				//			//  CREATE_SUSPENDED    �ӽ��̴��������ֱ������ResumeThread����  
				//	NULL,	//    ָ��һ���½��̵Ļ����顣����˲���Ϊ�գ��½���ʹ�õ��ý��̵Ļ���  
				//	NULL,	//    ָ���ӽ��̵Ĺ���·��  
				//	&si,	// �����½��̵������������ʾ��STARTUPINFO�ṹ��  
				//	&pi		// �����½��̵�ʶ����Ϣ��PROCESS_INFORMATION�ṹ��  
				//));
				//exit(0);

				ConsoleLabel* pLable = consoleUI()->getConsoleById("WARN_LABLE")->CAST_TO<ConsoleLabel>();
				pLable->setContent("�����ã���������������");
				pLable->setTextColor(green);
				break;
			}
			case 73://I
			{
			CONTINUE:
				//MessageBoxA(NULL, "continue", "msg", 0);
				timerPaoma.StopTimer();
				while (drawing)
					Sleep(1);
				consoleUI()->destory();
				break;
			}
			}
		}
	}

private:
	int m_nSel;
	std::vector<Control*> m_vctBts;

	COLOR m_txtColorNormal;
	COLOR m_bkColorNormal;
	COLOR m_txtColorSel;
	COLOR m_bkColorSel;
};

QuickEditCheck::QuickEditCheck(bool requireRestart/* = false*/)
{
	if (isQuickEditMode())
	{
		ConsoleUI consoleUI;
		consoleUI.setTitle("ע�⣺�����ٱ༭ģʽ���ѿ���,�ᵼ�������������");

		EventSelectMemu sel(&consoleUI);
		sel.setGlobalEvent(true);
		consoleUI.addEvent(&sel);

		ConsolePlane warnPlan(&consoleUI);
		warnPlan.setBkColor(dark_cyan);
		Rect rectPlan;
		rectPlan.X = 2;
		rectPlan.Y = 1;
		rectPlan.nWidth = consoleUI.getConsoleScreenInfo().srWindow.Right - rectPlan.X*2+1;
		rectPlan.nHeight = consoleUI.getConsoleScreenInfo().srWindow.Bottom - rectPlan.Y - 5;
		consoleUI.setControlRect(&warnPlan, rectPlan, false);
		consoleUI.addControl(&warnPlan);

		const char* szWarnTxt = "\"���ٱ༭ģʽ\"�ѿ���,�ᵼ�������������,�Ƿ�ر� ?";
		ConsoleLabel warnLable(&consoleUI);
		warnLable.setID("WARN_LABLE");
		warnLable.setTextColor(red);
		warnLable.setPosition(rectPlan.X + 2, rectPlan.Y);
		warnLable.setContent(szWarnTxt);
		warnLable.setAutoWidth(true);
		consoleUI.addControl(&warnLable);

		ConsoleButton restart(&consoleUI);
		restart.setID("RESTART");
		restart.setCaption("�ر�\"���ٱ༭ģʽ\"(R)");
		Rect rectButton;
		rectButton.X = 0;
		rectButton.Y = rectPlan.Y + rectPlan.nHeight + 1;
		rectButton.nWidth = 23;
		rectButton.nHeight = 3;
		consoleUI.setControlRect(&restart, rectButton, false);
		consoleUI.addControl(&restart);
		consoleUI.addEvent(&restart);

		ConsoleButton ignore(&consoleUI);
		ignore.setID("IGNORE");
		ignore.setCaption("���ԣ������(I)");
		rectButton.X += rectButton.nWidth + 2;
		consoleUI.setControlRect(&ignore, rectButton, false);
		consoleUI.addControl(&ignore);
		consoleUI.addEvent(&ignore);
		
		int moveX = (consoleUI.getConsoleScreenInfo().srWindow.Right - (rectButton.X + rectButton.nWidth)) / 2;
		Rect rect = restart.getRect();
		rect.X += moveX;
		consoleUI.setControlRect(&restart, rect, true);
		rect = ignore.getRect();
		rect.X += moveX;
		consoleUI.setControlRect(&ignore, rect, true);

		sel.addControl(&restart);
		sel.addControl(&ignore);

		sel.refreshButtons();

		srand((unsigned)time(NULL));
		timerPaoma.StartTimer(1000, [&](void)->void {
			drawing = true;

			warnPlan.draw();
			int nStartX = rectPlan.X + (rand() % (rectPlan.nWidth - warnLable.getRect().nWidth));
			int nStartY = rectPlan.Y + (rand() % (rectPlan.nHeight));
			warnLable.setPosition(nStartX, nStartY);
			warnLable.draw();

			drawing = false;
		});

		consoleUI.loopEvent();
	}
}


QuickEditCheck::~QuickEditCheck()
{
}

bool QuickEditCheck::isQuickEditMode()
{
	std::string sExePath(MAX_PATH, '\0');
	GetModuleFileNameA(NULL, &(sExePath[0]), MAX_PATH);
	StringReplace(sExePath, "\\", "_");
	StringReplace(sExePath, "/", "_");

	sExePath = "Console\\" + sExePath;

	//{
	//	DWORD dwVerison = 0;
	//	DWORD dwMajorVersion = 0;
	//	DWORD dwMinorVersion = 0;
	//	DWORD dwBuild = 0;
	//	dwVerison = GetVersion();
	//	// Get the Windows version   
	//	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVerison)));
	//	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVerison)));
	//	// Get the build number.  
	//	if (dwVerison < 0x80000000)
	//	{
	//		dwBuild = (DWORD)(HIWORD(dwVerison));
	//	}
	//	printf("Version is %d.%d (%d)\n",
	//		dwMajorVersion,
	//		dwMinorVersion,
	//		dwBuild
	//	);
	//}

	CRegOperator reg;
	reg.SetHKEY("HKEY_CURRENT_USER");
	if (!reg.OpenKey(sExePath.c_str()))
	{
		return true;
	}

	DWORD dwIsQuickEdit = 1;
	reg.Read("QuickEdit", dwIsQuickEdit);
	reg.Close();

	return (dwIsQuickEdit == 1);
}
