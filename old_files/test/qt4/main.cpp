/* main.cpp - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */
#include <QApplication>
#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include <QPainter>
#include <QSize>
#include <QDebug>
#include <QResizeEvent>

#include "macross.h"
#include "interface.h"

static int g_width;
static int g_height;
static const char *home_url;

extern void init_callback(void);
int get_virtual_key(int pk);

class MsgTimer : public QTimer
{
protected:
void timerEvent(QTimerEvent * timer)
{
	macross_event_dispatch();
}
};

class UserTimer : public QTimer
{
public:
	UserTimer(void(*func)(void*), void* data)
		: m_func(func)
		, m_data(data)
	{
	}
protected:
void timerEvent(QTimerEvent * timer)
{
	m_func(m_data);
}
private:
	void(*m_func)(void*);
	void* m_data;
};

class MainWindow : public QMainWindow 
{
public:
	MainWindow(QWidget* parent = 0)
		: QMainWindow(parent, 0)
		, view(0)
	{
		setMouseTracking(true);
    	image = QImage(g_width, g_height, QImage::Format_RGB32);
		image.fill(0xFFFFFFFF);
		view = on_init(image.bits(), g_width, g_height, g_width*4, this);		
	}

	virtual ~MainWindow()
	{
		on_term(view);
		macross_shutdown();
	}

	void loadUrl(const char* url)
	{
		load_url(view, home_url);
	}

	MaCrossView * getView(void) 
	{
		return view;
	}

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent * event);
    void contextMenuEvent(QContextMenuEvent * event);
	void closeEvent(QCloseEvent * event);
private:
	MaCrossView* view;
    QImage image;
};

inline void MainWindow::closeEvent(QCloseEvent *event)
{
	on_term(view);
	view = 0;
}

inline void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
	QRect rect = event->rect();
	on_draw(view, rect.x(), rect.y(), rect.width(), rect.height());
	painter.drawImage(rect, image, rect);
}

inline void MainWindow::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
	g_width = event->size().width();
	g_height = event->size().height();
	if (g_width < 1) g_width = 1;
	if (g_height < 1) g_height = 1;
    image = QImage(g_width, g_height, QImage::Format_RGB32);
	image.fill(0xFFFFFFFF);
	on_size(view, image.bits(), g_width, g_height, g_width*4);
}

inline void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	unsigned int key = 0;
	on_context_menu(view, event->x(), event->y(), key);
}

inline void MainWindow::mousePressEvent(QMouseEvent *event)
{
	MC_MOUSE_BUTTON btn = MOUSE_BTN_NONE;
	unsigned int key = 0;
	if (event->buttons() & Qt::LeftButton) {
		btn = MOUSE_BTN_LEFT;
	if (event->buttons() & Qt::SHIFT)
		key |= MF_SHIFT;
	if (event->buttons() & Qt::CTRL)
		key |= MF_CTRL;

	on_mouse(view, EVT_MOUSE_DOWN, btn, event->x(), event->y(), key);
	}
}

inline void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	MC_MOUSE_BUTTON btn = MOUSE_BTN_NONE;
	unsigned int key = 0;
	if (event->buttons() & Qt::LeftButton)
		btn = MOUSE_BTN_LEFT;
	if (event->buttons() & Qt::MidButton)
		btn = MOUSE_BTN_MIDDLE;
	if (event->buttons() & Qt::RightButton)
		btn = MOUSE_BTN_RIGHT;
	if (event->buttons() & Qt::SHIFT)
		key |= MF_SHIFT;
	if (event->buttons() & Qt::CTRL)
		key |= MF_CTRL;

	on_mouse(view, EVT_MOUSE_UP, btn, event->x(), event->y(), key);
}

inline void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	unsigned int key = 0;
	MC_MOUSE_BUTTON btn = MOUSE_BTN_NONE;
	if (event->buttons() & Qt::SHIFT)
		key |= MF_SHIFT;
	if (event->buttons() & Qt::CTRL)
		key |= MF_CTRL;

	if (event->buttons() & Qt::LeftButton)
		btn = MOUSE_BTN_LEFT;
	if (event->buttons() & Qt::MidButton)
		btn = MOUSE_BTN_MIDDLE;
	if (event->buttons() & Qt::RightButton)
		btn = MOUSE_BTN_RIGHT;

	on_mouse(view, EVT_MOUSE_MOVE, btn, event->x(), event->y(), key);
}

inline void MainWindow::wheelEvent(QWheelEvent* event)
{
	unsigned int key = 0;
	MC_MOUSE_BUTTON btn = MOUSE_BTN_NONE;
	if (event->buttons() & Qt::SHIFT)
		key |= MF_SHIFT;
	if (event->buttons() & Qt::CTRL)
		key |= MF_CTRL;

	if (event->delta() > 0)
		btn = MOUSE_WHEEL_DOWN;
	else
		btn = MOUSE_WHEEL_UP;

	on_mouse(view, EVT_MOUSE_WHEEL, btn, event->x(), event->y(), key);
}

inline void MainWindow::keyPressEvent(QKeyEvent * event)
{
	unsigned int key = 0;
	if (event->modifiers() & Qt::ShiftModifier)
		key |= MF_SHIFT;
	if (event->modifiers() & Qt::ControlModifier)
		key |= MF_CTRL;

	on_key(view, EVT_KEY_DOWN, (MC_VIRTUAL_KEY)get_virtual_key(event->key()), key);
}

inline void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
	unsigned int key = 0;
	if (event->modifiers() & Qt::ShiftModifier)
		key |= MF_SHIFT;
	if (event->modifiers() & Qt::ControlModifier)
		key |= MF_CTRL;

	MC_VIRTUAL_KEY code = (MC_VIRTUAL_KEY)get_virtual_key(event->key());
	on_key(view, EVT_KEY_UP, code, key);
	if (!key && (code >= 0x30 && code <= 0x5A) && !event->text().isEmpty())
		on_chars(view, event->text().toUtf8().data());
}

inline void MainWindow::focusInEvent(QFocusEvent * event)
{
	on_focus(view);
}

inline void MainWindow::focusOutEvent(QFocusEvent * event)
{
	on_lose_focus(view);
}

MainWindow* window = 0;

QMainWindow* getMainWindow()
{
	return window;
}

extern "C" MaCrossView* getMainView(void)
{
	return window->getView();
}

MaCrossView* OpenWindow(const char* url, int w, int h)
{
   	MainWindow* win = new MainWindow;
    win->setWindowTitle("MaCross Browser");
	win->resize(w, h);
	win->loadUrl(url);
	win->show();

	return win->getView();
}

int main(int argc, char* argv[])
{
    if (argv[1])
        home_url = argv[1];

	g_width = 640;
	g_height = 480;
	macross_initialize(PIXEL_FORMAT_BGRA32, 1024, 768);
	init_callback();

	QApplication app(argc, argv);
	MsgTimer * timer = new MsgTimer;
	timer->start(10);
   	window = new MainWindow;
    window->setWindowTitle("MaCross Browser");
	window->resize(g_width, g_height);
	window->loadUrl(home_url);
	window->show();
	return app.exec();
}

typedef struct {
	int vk;
	int pk;
}KeyEntities;

static KeyEntities key_map[] = {
	{KEY_BACK, Qt::Key_Backspace},
	{KEY_TAB, Qt::Key_Tab},
	{KEY_CLEAR, Qt::Key_Clear},
	{KEY_ENTER, Qt::Key_Return},
	{KEY_SHIFT, Qt::Key_Shift},
	{KEY_CTRL, Qt::Key_Control},
	{KEY_ALT, Qt::Key_Menu},
	{KEY_PAUSE, Qt::Key_Pause},
	{KEY_CAPSLOCK, Qt::Key_CapsLock},
	{KEY_ESCAPE, Qt::Key_Escape},
	{KEY_SPACE, Qt::Key_Space},
	{KEY_PAGEUP, Qt::Key_PageUp},
	{KEY_PAGEDOWN, Qt::Key_PageDown},
	{KEY_END, Qt::Key_End},
	{KEY_HOME, Qt::Key_Home},
	{KEY_LEFT, Qt::Key_Left},
	{KEY_UP, Qt::Key_Up},
	{KEY_RIGHT, Qt::Key_Right},
	{KEY_DOWN, Qt::Key_Down},
	{KEY_SELECT, Qt::Key_Select},
	{KEY_PRINT, Qt::Key_Print},
	{KEY_EXEC, Qt::Key_Execute},
	{KEY_INSERT, Qt::Key_Insert},
	{KEY_DELETE, Qt::Key_Delete},
	{KEY_HELP, Qt::Key_Help},
	{KEY_0, Qt::Key_0},
	{KEY_1, Qt::Key_1},
	{KEY_2, Qt::Key_2},
	{KEY_3, Qt::Key_3},
	{KEY_4, Qt::Key_4},
	{KEY_5, Qt::Key_5},
	{KEY_6, Qt::Key_6},
	{KEY_7, Qt::Key_7},
	{KEY_8, Qt::Key_8},
	{KEY_9, Qt::Key_9},
	{KEY_A, Qt::Key_A},
	{KEY_B, Qt::Key_B},
	{KEY_C, Qt::Key_C},
	{KEY_D, Qt::Key_D},
	{KEY_E, Qt::Key_E},
	{KEY_F, Qt::Key_F},
	{KEY_G, Qt::Key_G},
	{KEY_H, Qt::Key_H},
	{KEY_I, Qt::Key_I},
	{KEY_J, Qt::Key_J},
	{KEY_K, Qt::Key_K},
	{KEY_L, Qt::Key_L},
	{KEY_M, Qt::Key_M},
	{KEY_N, Qt::Key_N},
	{KEY_O, Qt::Key_O},
	{KEY_P, Qt::Key_P},
	{KEY_Q, Qt::Key_Q},
	{KEY_R, Qt::Key_R},
	{KEY_S, Qt::Key_S},
	{KEY_T, Qt::Key_T},
	{KEY_U, Qt::Key_U},
	{KEY_V, Qt::Key_V},
	{KEY_W, Qt::Key_W},
	{KEY_X, Qt::Key_X},
	{KEY_Y, Qt::Key_Y},
	{KEY_Z, Qt::Key_Z},
	{KEY_LWIN, Qt::Key_Meta},
	{KEY_RWIN, Qt::Key_Meta},
	{KEY_EQUAL, Qt::Key_Equal},
	{KEY_MINUS, Qt::Key_Minus},
	{KEY_DECIMAL, Qt::Key_Greater},
	{KEY_SLASH, Qt::Key_Question},
	{KEY_F1, Qt::Key_F1},
	{KEY_F2, Qt::Key_F2},
	{KEY_F3, Qt::Key_F3},
	{KEY_F4, Qt::Key_F4},
	{KEY_F5, Qt::Key_F5},
	{KEY_F6, Qt::Key_F6},
	{KEY_F7, Qt::Key_F7},
	{KEY_F8, Qt::Key_F8},
	{KEY_F9, Qt::Key_F9},
	{KEY_F10, Qt::Key_F10},
	{KEY_F11, Qt::Key_F11},
	{KEY_F12, Qt::Key_F12},
	{KEY_F13, Qt::Key_F13},
	{KEY_F14, Qt::Key_F14},
	{KEY_F15, Qt::Key_F15},
	{KEY_F16, Qt::Key_F16},
	{KEY_F17, Qt::Key_F17},
	{KEY_F18, Qt::Key_F18},
	{KEY_F19, Qt::Key_F19},
	{KEY_F20, Qt::Key_F20},
	{KEY_F21, Qt::Key_F21},
	{KEY_F22, Qt::Key_F22},
	{KEY_F23, Qt::Key_F23},
	{KEY_F24, Qt::Key_F24},
};

int get_virtual_key(int pk)
{
	int i;
	for(i = 0; i < (sizeof(key_map)/sizeof(KeyEntities)); i++)
		if (key_map[i].pk == pk)
			return key_map[i].vk;
	return KEY_UNKNOWN; 
}

void platform_exception(void(*dump)(int))
{
}

extern "C" unsigned int set_timer(unsigned int mscend, void(*func)(void*), void* data)
{
	UserTimer* timer = new UserTimer(func, data);
	timer->start(mscend);
	return reinterpret_cast<unsigned int>(timer);
}

extern "C" void kill_timer(unsigned int id)
{
	UserTimer* timer = reinterpret_cast<UserTimer*>(id);
	delete timer;
}
