#ifndef COLORPICKER_H
#define COLORPICKER_H
#include <QPushButton>
#include <QtCore/QString>
#include <QColor>

#include <QLabel>
#include <QtCore/QEvent>
#include <QFocusEvent>

#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QColorDialog>
#include <QtCore/QMap>
#include <QLayout>
#include <QStyle>
#include <QLabel>
#include <QToolTip>
#include <QPixmap>
#include <QFocusEvent>
#include <QPaintEvent>
#include <QGridLayout>
#include <QHideEvent>
#include <QKeyEvent>
#include <QShowEvent>
#include <QMouseEvent>
#include <math.h>

class ColorPickerButton : public QFrame
{
    Q_OBJECT

public:
    ColorPickerButton(QWidget *parent);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
};

class ColorPickerItem : public QFrame
{
    Q_OBJECT

public:
    ColorPickerItem(const QColor &color = Qt::white, const QString &text = QString(),
              QWidget *parent = 0);
    ~ColorPickerItem();

    QColor color() const;
    QString text() const;

    void setSelected(bool);
    bool isSelected() const;
signals:
    void clicked();
    void selected();

public slots:
    void setColor(const QColor &color, const QString &text = QString());

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    QColor c;
    QString t;
    bool sel;
};

class ColorPickerPopup : public QFrame
{
    Q_OBJECT

public:
    ColorPickerPopup(int width, bool withColorDialog,
               QWidget *parent = 0);
    ~ColorPickerPopup();

    void insertColor(const QColor &col, const QString &text, int index);
    void exec();

    void setExecFlag();

    QColor lastSelected() const;

    ColorPickerItem *find(const QColor &col) const;
    QColor color(int index) const;

signals:
    void selected(const QColor &);
    void hid();

public slots:
    void getColorFromDialog();

protected slots:
    void updateSelected();

protected:
    void keyPressEvent(QKeyEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void regenerateGrid();

private:
    QMap<int, QMap<int, QWidget *> > widgetAt;
    QList<ColorPickerItem *> items;
    QGridLayout *grid;
    ColorPickerButton *moreButton;
    QEventLoop *eventLoop;

    int lastPos;
    int cols;
    QColor lastSel;
};

class ColorPicker : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool colorDialog READ colorDialogEnabled WRITE setColorDialogEnabled)

public:
    ColorPicker(QWidget *parent = 0, int columns = -1, bool enableColorDialog = true);

    ~ColorPicker();

    void insertColor(const QColor &color, const QString &text = QString(), int index = -1);

        QColor currentColor() const;

        QColor color(int index) const;

        void setColorDialogEnabled(bool enabled);
        bool colorDialogEnabled() const;

        void setStandardColors();

        static QColor getColor(const QPoint &pos, bool allowCustomColors = true);

    public Q_SLOTS:
        void setCurrentColor(const QColor &col);

    Q_SIGNALS:
        void colorChanged(const QColor &);

    protected:
        void paintEvent(QPaintEvent *e);

    private Q_SLOTS:
        void buttonPressed(bool toggled);
        void popupClosed();

    private:
        ColorPickerPopup *popup;
        QColor col;
        bool withColorDialog;
        bool dirty;
        bool firstInserted;
};







//#include "colorpicker.moc"

#endif // COLORPICKER_H

