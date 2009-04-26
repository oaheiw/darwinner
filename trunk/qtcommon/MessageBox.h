#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <string>
using namespace std;

class MessageBox : public QMessageBox
{
public:
	MessageBox(QWidget *parent);
	~MessageBox();
	static QMessageBox::StandardButton showMessageBox(QWidget * parent, QMessageBox::Icon icon, string windowTitle, string title, string info = "");	
};

#endif // MESSAGEBOX_H
