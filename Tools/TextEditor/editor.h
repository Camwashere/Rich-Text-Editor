#ifndef EDITOR_H
#define EDITOR_H

#include <QFrame>
#include <QTextCharFormat>
#include <QFileDialog>
#include "Tools/ColorPicker/colorpicker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE


class Editor : public QFrame
{
    Q_OBJECT

private:
    Ui::Editor *ui;
    ColorPicker* textColor;
    ColorPicker* backgroundColor;
    QFileDialog fileChooser;




public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private slots:
    // Update all button visuals to reflect the format at the currently selected location
    void on_content_selectionChanged();


    void on_boldBtn_clicked();
    void on_italicBtn_clicked();
    void on_underlineBtn_clicked();
    void on_overlineBtn_clicked();
    void on_strikethroughBtn_clicked();
    void on_subscriptBtn_clicked();
    void on_superscriptBtn_clicked();

    void on_fontSelector_currentFontChanged(const QFont &f);
    void on_fontSizeSelector_valueChanged(int arg1);

    void on_textColor_changed(const QColor& color);
    void on_backgroundColor_changed(const QColor& color);













    void on_caseBtn_clicked();
    void on_clearFormatBtn_clicked();
    void on_alignCenterBtn_clicked();
    void on_alignLeftBtn_clicked();
    void on_alignJustifyBtn_clicked();
    void on_alignRightBtn_clicked();
    void on_bulletListBtn_clicked();
    void on_numberedListBtn_clicked();
    void on_tableBtn_clicked();
    void on_imgBtn_clicked();
};

#endif // EDITOR_H
