#include "editor.h"
#include "ui_editor.h"
#include <iostream>
#include <QTextDocumentFragment>
#include <QTextTable>
#include "Tools/TextEditor/Logic/lexer.h"


Editor::Editor(QWidget *parent) :
    QFrame(parent), ui(new Ui::Editor), textColor(new ColorPicker(this)), backgroundColor(new ColorPicker(this))
{
    ui->setupUi(this);
    //ui->overlineBtn->font().overline();
    //ui->content->currentFont().setFixedPitch(false);



    textColor->setStandardColors();
    backgroundColor->setStandardColors();


    QObject::connect(textColor, &ColorPicker::colorChanged,
                     this, &Editor::on_textColor_changed);

    QObject::connect(backgroundColor, &ColorPicker::colorChanged,
                     this, &Editor::on_backgroundColor_changed);


    ui->fontStyle->addWidget(textColor);
    ui->fontStyle->addWidget(backgroundColor);


    Lex lexer;
    QString equation = "{-2.45 + -2 - 4++ * -5}";
    QList<AbstractToken> list = lexer.toTokens(equation);
    //std::cout << "Original: " << equation.toStdString() << std::endl;
    //std::cout << "Parsed: ";
    for (AbstractToken t : list)
    {
        //std::cout << t.toString() << " ";
    }
    //std::cout << std::endl;









}

Editor::~Editor()
{
    delete ui;
}

// Update all button visuals to reflect the format at the currently selected location
void Editor::on_content_selectionChanged()
{

    QTextCharFormat format = ui->content->currentCharFormat();
    ui->boldBtn->setChecked(format.fontWeight() == QFont::Bold);
    ui->italicBtn->setChecked(format.fontItalic());
    ui->underlineBtn->setChecked(format.fontUnderline());
    ui->strikethroughBtn->setChecked(format.fontStrikeOut());
    ui->subscriptBtn->setChecked(format.verticalAlignment() == QTextCharFormat::VerticalAlignment::AlignSubScript);
    ui->superscriptBtn->setChecked(format.verticalAlignment() == QTextCharFormat::VerticalAlignment::AlignSuperScript);


    ui->fontSelector->setFont(format.font().family());
    ui->fontSelector->setCurrentText(format.font().family());

    ui->fontSizeSelector->setValue((format.fontPointSize() < 1) ? ui->content->font().pointSize() : ui->content->fontPointSize());

    textColor->setCurrentColor(ui->content->textColor());
    backgroundColor->setCurrentColor(ui->content->textBackgroundColor());

    switch(ui->content->alignment())
    {
        case Qt::AlignLeft:
            ui->alignLeftBtn->setChecked(true);
        break;
        case Qt::AlignRight:
            ui->alignRightBtn->setChecked(true);
        break;
        case Qt::AlignCenter:
            ui->alignCenterBtn->setChecked(true);
        break;
        case Qt::AlignJustify:
            ui->alignJustifyBtn->setChecked(true);
        break;
        default:
            break;
    }












}



void Editor::on_boldBtn_clicked()
{
    ui->content->setFontWeight(ui->boldBtn->isChecked()? QFont::Bold : QFont::Normal);
}

void Editor::on_italicBtn_clicked()
{
    ui->content->setFontItalic(ui->italicBtn->isChecked());
}

void Editor::on_underlineBtn_clicked()
{
    QTextCharFormat f = ui->content->currentCharFormat();
    f.setFontUnderline(ui->underlineBtn->isChecked());
    ui->content->mergeCurrentCharFormat(f);

}
void Editor::on_overlineBtn_clicked()
{
     QTextCharFormat f = ui->content->currentCharFormat();
     f.setFontOverline(ui->overlineBtn->isChecked());
     ui->content->mergeCurrentCharFormat(f);

}
void Editor::on_strikethroughBtn_clicked()
{
    QTextCharFormat f = ui->content->currentCharFormat();
    f.setFontStrikeOut(ui->strikethroughBtn->isChecked());
    ui->content->mergeCurrentCharFormat(f);
}
void Editor::on_subscriptBtn_clicked()
{
    ui->superscriptBtn->setChecked(false);
    QTextCharFormat format;
    format.setVerticalAlignment(ui->subscriptBtn->isChecked() ? QTextCharFormat::VerticalAlignment::AlignSubScript : QTextCharFormat::VerticalAlignment::AlignNormal);
    ui->content->mergeCurrentCharFormat(format);
}
void Editor::on_superscriptBtn_clicked()
{
    ui->subscriptBtn->setChecked(false);
    QTextCharFormat format;
    format.setVerticalAlignment(ui->superscriptBtn->isChecked() ? QTextCharFormat::VerticalAlignment::AlignSuperScript : QTextCharFormat::VerticalAlignment::AlignNormal);
    ui->content->mergeCurrentCharFormat(format);

}








void Editor::on_fontSelector_currentFontChanged(const QFont &f)
{
    ui->fontSelector->setFont(f);
    QTextCharFormat format;
    format.setFontFamilies(f.families());
    ui->content->mergeCurrentCharFormat(format);
}


void Editor::on_fontSizeSelector_valueChanged(int arg1)
{
    ui->content->setFontPointSize(arg1);


}


void Editor::on_textColor_changed(const QColor& color)
{
    ui->content->setTextColor(color);
}

void Editor::on_backgroundColor_changed(const QColor& color)
{
    ui->content->setTextBackgroundColor(color);
}


void Editor::on_caseBtn_clicked()
{
    ui->content->textCursor().insertText(ui->content->textCursor().selectedText().toUpper());
}




void Editor::on_clearFormatBtn_clicked()
{
    QTextCharFormat cleared;
    ui->content->setCurrentCharFormat(cleared);
}


void Editor::on_alignCenterBtn_clicked()
{
    ui->content->setAlignment(Qt::AlignCenter);

}


void Editor::on_alignLeftBtn_clicked()
{
    ui->content->setAlignment(Qt::AlignLeft);

}


void Editor::on_alignJustifyBtn_clicked()
{
    ui->content->setAlignment(Qt::AlignJustify);

}


void Editor::on_alignRightBtn_clicked()
{
    ui->content->setAlignment(Qt::AlignRight);
}


void Editor::on_bulletListBtn_clicked()
{
    ui->content->textCursor().createList(QTextListFormat::ListDisc);

}


void Editor::on_numberedListBtn_clicked()
{
    ui->content->textCursor().createList(QTextListFormat::ListDecimal);
}


void Editor::on_tableBtn_clicked()
{
    QTextTableFormat format;
    format.setCellPadding(10);
    QTextTable* table = ui->content->textCursor().insertTable(2, 2, format);

}


void Editor::on_imgBtn_clicked()
{
    fileChooser.setNameFilter(tr("Images (*.png *.xpm *.jpg"));
    fileChooser.show();

}

