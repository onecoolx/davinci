/* popmenu - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#include <QImage>
#include <QPainter>
#include <QSize>
#include <QPoint>
#include <QMenu>
#include <QResizeEvent>
#include <QMainWindow>

#include <QDebug>
#include "macross.h"
extern QMainWindow* getMainWindow();
extern int get_virtual_key(int pk);

class PopMenu : public QMenu
{
public:
	PopMenu(QWidget* parent, int width, int height, MC_POPUP_MENU* menu)
		: QMenu(parent)
	{
		setMouseTracking(true);
		setFocusPolicy(Qt::StrongFocus);
		popmenu = menu;
    	image = QImage(width, height, QImage::Format_RGB32);
		image.fill(0xFFFFFFFF);
		popmenu->pitch = image.bytesPerLine();
		popmenu->buffer = image.bits();
	}

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent * event);
    void focusOutEvent(QFocusEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent * event);
private:
    QImage image;
	MC_POPUP_MENU* popmenu;
};

inline void PopMenu::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
	int width = event->size().width()-2;
	int height = event->size().height()-2;
	if (width < 1) width = 1;
	if (height < 1) height = 1;
    image = QImage(width, height, QImage::Format_RGB32);
	image.fill(0xFFFFFFFF);
	popmenu->pitch = image.bytesPerLine();
	popmenu->buffer = image.bits();
	macross_menu_resize(popmenu, width, height);
}

inline void PopMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
	MC_RECT rc = {0, 0, image.width(), image.height()};
	macross_menu_update(popmenu, &rc);
	QRect rect(1, 1, image.width(), image.height());
	painter.drawImage(rect, image);
}

inline void PopMenu::focusOutEvent(QFocusEvent * event)
{
	macross_menu_hide(popmenu);
}

inline void PopMenu::keyPressEvent(QKeyEvent * event)
{
	unsigned int key = 0;
	if (event->modifiers() & Qt::ShiftModifier)
		key |= MF_SHIFT;
	if (event->modifiers() & Qt::ControlModifier)
		key |= MF_CTRL;
	MC_KEY_EVENT e = {EVT_KEY_DOWN, (MC_VIRTUAL_KEY)get_virtual_key(event->key()), key};
	macross_menu_keyboard_event(popmenu, &e);
}
inline void PopMenu::mousePressEvent(QMouseEvent *event)
{
	MC_MOUSE_BUTTON btn = MOUSE_BTN_NONE;
	unsigned int key = 0;
	if (event->buttons() & Qt::LeftButton) {
		btn = MOUSE_BTN_LEFT;
	if (event->buttons() & Qt::SHIFT)
		key |= MF_SHIFT;
	if (event->buttons() & Qt::CTRL)
		key |= MF_CTRL;

	MC_MOUSE_EVENT e = {EVT_MOUSE_DOWN, btn, {event->x(), event->y()}, key};
	macross_menu_mouse_event(popmenu, &e);
	}
}

inline void PopMenu::mouseReleaseEvent(QMouseEvent *event)
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

	MC_MOUSE_EVENT e = {EVT_MOUSE_UP, btn, {event->x(), event->y()}, key};
	macross_menu_mouse_event(popmenu, &e);
}

inline void PopMenu::mouseMoveEvent(QMouseEvent *event)
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

	MC_MOUSE_EVENT e = {EVT_MOUSE_MOVE, btn, {event->x(), event->y()}, key};
	macross_menu_mouse_event(popmenu, &e);
}

static void Show(MC_POPUP_MENU* m)
{
	PopMenu* p = (PopMenu*)m->data;
	p->show();
}

static void Hide(MC_POPUP_MENU* m)
{
	PopMenu* p = (PopMenu*)m->data;
	p->hide();
}

static void Move(MC_POPUP_MENU* m, const MC_RECT* r)
{
	PopMenu* p = (PopMenu*)m->data;
	QMainWindow * w = getMainWindow();
	QPoint gp = w->mapToGlobal(QPoint(r->x, r->y));
	p->move(gp);
	p->resize(r->w+2, r->h+2);
	m->rect = *r;
}

static void Update(MC_POPUP_MENU* m)
{
	PopMenu* p = (PopMenu*)m->data;
	p->update();
}

static void Dirty(MC_POPUP_MENU* m, const MC_RECT* r)
{
	PopMenu* p = (PopMenu*)m->data;
	if (r)
		p->update(r->x, r->y, r->w, r->h);
	else
		p->update();
}

static void Capture(MC_POPUP_MENU* m)
{
	PopMenu* p = (PopMenu*)m->data;
	p->setFocus();
}

extern MC_POPUP_MENU* create_popmenu(const MC_RECT* r)
{
	MC_POPUP_MENU * p = (MC_POPUP_MENU*)malloc(sizeof(MC_POPUP_MENU));
	memset(p, 0, sizeof(MC_POPUP_MENU));

	QMainWindow * w = getMainWindow();
	QPoint gp = w->mapToGlobal(QPoint(r->x, r->y));

	p->rect = *r;
	PopMenu* pop = new PopMenu(0, r->w, r->h, p);
	pop->move(gp);
	pop->resize(r->w+2, r->h+2);
	p->data = pop;

	p->show = Show;
	p->hide = Hide;
	p->move = Move;
	p->dirty = Dirty;
	p->update = Update;
	p->capture = Capture;

	return p;
}

extern void destroy_popmenu(MC_POPUP_MENU* m)
{
	PopMenu* p = (PopMenu*)m->data;
	delete p;
	free(m);
}
