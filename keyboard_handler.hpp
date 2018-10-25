#ifndef KEYBOARD_HANDLER_HPP
#define KEYBOARD_HANDLER_HPP

#include <QObject>

class keyboard_handler : public QObject
{
	Q_OBJECT
public:
	explicit keyboard_handler(QObject *parent = nullptr);

signals:

public slots:

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // KEYBOARD_HANDLER_HPP
