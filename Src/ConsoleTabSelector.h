#pragma once
#include "ConsoleUI.h"
#include "ConsoleComCtrl.h"

NS_START��

class ConsoleTabSelector
	: public Event
{
public:
	ConsoleTabSelector(ConsoleUI *consoleUI = NULL);

	std::vector<ControlSelectable*> getSelectableControls();

	//��ÿ�ѡ��ؼ������nStartLayerId����ControlSelectable���������ң������β��ص��ײ���ʼ������
	ControlSelectable* getSelectableControl(int nStartLayerId);

	int getSelectedId(Control* pControl);

	void beginShowTab();

	void endShowTab();

protected:
	virtual EVENT_TYPE eventType() { return KEY_EVENT; }

	virtual void onEvent(INPUT_RECORD &input_record);

private:
	int m_nSelectedLayerId;
	ControlSelectable* m_pCurSelCtrl;
	bool m_bHasShowTab;
};


��NS_END