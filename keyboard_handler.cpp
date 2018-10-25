#include "keyboard_handler.hpp"

#include <cstdio>
#include <QEvent>
#include <QKeyEvent>

keyboard_handler::keyboard_handler(QObject *parent) : QObject(parent)
{

}

bool keyboard_handler::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		printf("Ate key press %d", keyEvent->key());
		fflush(stdout);
		return true;
	}
	else
	{
		// standard event processing
		return QObject::eventFilter(obj, event);
	}
}
