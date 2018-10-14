#ifndef GL_WIDGET_HPP
#define GL_WIDGET_HPP

#include <QOpenGLWidget>

class gl_widget : public QOpenGLWidget
{
public:
	gl_widget(QWidget *parent = nullptr);

public slots:
	/**
	 * @brief Update the scene
	 */
	void animate();

protected:
	void initializeGL() override;
	//void resizeGL(int w, int h) override;
	//void paintGL() override;
	void paintEvent(QPaintEvent *event) override;
};

#endif // GL_WIDGET_HPP
