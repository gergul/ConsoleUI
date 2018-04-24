#include "ConsoleComEvent.h"
#include "ConsoleComCtrl.h"
#include "QuickEditCheck.h"

using namespace GL;

class MyButton
	:public ConsoleButton
{
public:
	MyButton(ConsoleUI *consoleUI)
		: ConsoleButton(consoleUI)
	{

	}

protected:
	virtual void onInitEvent()
	{

	}

	virtual void onClicked()
	{
		ConsoleInputBox* pInputBox = consoleUI()->getConsoleById("MY_INPUT_BOX")->CAST_TO<ConsoleInputBox>();
		ConsoleListBox* pListBox = consoleUI()->getConsoleById("MY_LIST_BOX")->CAST_TO<ConsoleListBox>();
		std::string sTxt = pInputBox->getContent();
		int nSelRow = pListBox->getSelectedItem();
		pListBox->setItemText(nSelRow, sTxt.c_str());
	}

	virtual void onResize()
	{

	}
};

void main(int argc, char** argv)
{
	QuickEditCheck qec;	

	ConsoleUI consoleUI/*(GL::COLOR::dark_cyan)*/;
	consoleUI.setTitle("Console UI ��ʾ");

	//EventMouseFollow mev(&consoleUI);
	//consoleUI.addEvent(&mev);
	EventResizeWindow rw(&consoleUI);
	consoleUI.addEvent(&rw);
	EventTabSelect ts(&consoleUI);
	consoleUI.addEvent(&ts);

	ConsolePlane titlePlane(&consoleUI);
	Rect rectTitle;
	rectTitle.X = 0;
	rectTitle.Y = 0;
	rectTitle.nWidth = consoleUI.getConsoleScreenInfo().dwSize.X;
	rectTitle.nHeight = 2;
	consoleUI.setControlRect(&titlePlane, rectTitle, false);
	titlePlane.setBkColor(dark_white);
	consoleUI.addControl(&titlePlane);
	consoleUI.addEvent(&titlePlane);

	ConsoleLabel titleLabel(&consoleUI);
	titleLabel.setWidth(consoleUI.getConsoleScreenInfo().dwSize.X);
	titleLabel.setAlign(ConsoleLabel::center);
	titleLabel.setPosition(0, 0);
	titleLabel.setTextColor(GL::red);
	titleLabel.setContent("Console UI v0.01 ��Դ�� - Author: Gergul");
	consoleUI.addControl(&titleLabel);

	ConsoleListBox listBox(&consoleUI);
	Rect rectList;
	rectList.X = 2;
	rectList.Y = 3;
	rectList.nWidth = 60;
	rectList.nHeight = 20;
	consoleUI.setControlRect(&listBox, rectList, false);
	listBox.setID("MY_LIST_BOX");
	consoleUI.addControl(&listBox);
	consoleUI.addEvent(&listBox);

	char txt[256];
	for (int i = 0; i < 100; ++i)
	{
		sprintf(txt, "���%d", i);
		listBox.insertItem(txt, -1, false);
	}
	listBox.draw();

	ConsoleLabel tipLabel(&consoleUI);
	tipLabel.setWidth(8);
	tipLabel.setPosition(65, 4);
	tipLabel.setContent("�����룺");
	consoleUI.addControl(&tipLabel);

	ConsoleInputBox inputBox(&consoleUI);
	inputBox.setPosition(73, 4);
	inputBox.setWidth(15);
	inputBox.setID("MY_INPUT_BOX");
	inputBox.setSelectable(true);
	consoleUI.addEvent(&inputBox);
	consoleUI.addControl(&inputBox);

	MyButton btSetText(&consoleUI);
	btSetText.setCaption("�����ı�");
	btSetText.setSelectable(true);
	Rect rect;
	rect.nWidth = 8;
	rect.nHeight = 1;
	rect.X = 90;
	rect.Y = 4;
	consoleUI.setControlRect(&btSetText, rect, false);
	consoleUI.addEvent(&btSetText);
	consoleUI.addControl(&btSetText);

	ConsoleLabel txtLabel(&consoleUI);
	txtLabel.setWidth(23);
	txtLabel.setPosition(65, 6);
	txtLabel.setTextColor(GL::red);
	txtLabel.setContent("");
	txtLabel.setTransparent(false);
	consoleUI.addControl(&txtLabel);

	std::function<void(void)> onGetTextClick = [&](void) -> void {
		txtLabel.setContent(listBox.getSelectedItemText().c_str());
		consoleUI.redrawControl(&txtLabel);
	};
	ConsoleButton btGetText(&consoleUI);
	btGetText.setCaption("����ı�");
	btGetText.setSelectable(true);
	Rect rectGetText;
	rectGetText.nWidth = 8;
	rectGetText.nHeight = 1;
	rectGetText.X = 90;
	rectGetText.Y = 6;
	consoleUI.setControlRect(&btGetText, rectGetText, false);
	btGetText.setClickedEvent(onGetTextClick);
	consoleUI.addEvent(&btGetText);
	consoleUI.addControl(&btGetText);

	ConsoleCheckBox cb(&consoleUI);
	cb.setCheck(false);
	cb.setPosition(65, 8);
	cb.setAutoWidth(true);
	cb.setContent("��ѡ���Ұ�");
	cb.setSelectable(true);
	consoleUI.addControl(&cb);
	consoleUI.addEvent(&cb);

	ConsoleRadioBox::Group rbg;
	ConsoleRadioBox rb1(&consoleUI);
	rb1.setPosition(65, 10);
	rb1.setAutoWidth(true);
	rb1.setContent("��ѡ���Ұ�1");
	rb1.setSelectable(true);
	consoleUI.addControl(&rb1);
	consoleUI.addEvent(&rb1);
	rbg.addRadioBox(&rb1);
	ConsoleRadioBox rb2(&consoleUI);
	rb2.setPosition(80, 10);
	rb2.setAutoWidth(true);
	rb2.setContent("��ѡ���Ұ�2");
	rb2.setSelectable(true);
	consoleUI.addControl(&rb2);
	consoleUI.addEvent(&rb2);
	rb2.setGroup(&rbg);
	rbg.addRadioBox(&rb2);
	ConsoleRadioBox rb3(&consoleUI);
	rb3.setPosition(65, 11);
	rb3.setAutoWidth(true);
	rb3.setContent("��ѡ���Ұ�3");
	rb3.setSelectable(true);
	consoleUI.addControl(&rb3);
	consoleUI.addEvent(&rb3);
	rbg.addRadioBox(&rb3);
	ConsoleRadioBox rb4(&consoleUI);
	rb4.setPosition(80, 11);
	rb4.setAutoWidth(true);
	rb4.setContent("��ѡ���Ұ�4");
	rb4.setSelectable(true);
	consoleUI.addControl(&rb4);
	consoleUI.addEvent(&rb4);
	rb4.setGroup(&rbg);
	rbg.addRadioBox(&rb4);
	
	consoleUI.loopEvent();
}