#ifndef DESIGNERFTTAXU_H
#define DESIGNERFTTAXU_H
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *FrameBase;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QFrame *FrameDown;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *SendButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(636, 640);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        FrameBase = new QFrame(Form);
        FrameBase->setObjectName(QString::fromUtf8("FrameBase"));
        FrameBase->setFrameShape(QFrame::StyledPanel);
        FrameBase->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(FrameBase);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(FrameBase);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"background-color: rgb(46, 52, 54);\n"
"color:white;\n"
"}\n"
"QScrollBar:vertical {\n"
"                border: none;\n"
"                width:4px;\n"
"                background-color: #333333;\n"
"                border-top-right-radius: 2px;\n"
"                border-bottom-right-radius: 2px;\n"
"            }\n"
"\n"
"            QScrollBar::handle:vertical {\n"
"                border:none;\n"
"                background-color: #333333;\n"
"                border-top-right-radius: 2px;\n"
"                border-bottom-right-radius: 2px;\n"
"            }\n"
"\n"
"            QScrollBar::add-line:vertical {\n"
"                border: none;\n"
"                height: 20px;\n"
"                background: transparent;\n"
"            }\n"
"\n"
"            QScrollBar::sub-line:vertical {\n"
"                border: none;\n"
"                height: 20px;\n"
"                background: #1a1a1a;\n"
"                border-top-right-radius: 2px;\n"
"            }\n"
"            \n"
"      "
                        "      QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
"                background-color: none;\n"
"            }\n"
"\n"
"            QScrollBar::sub-page:vertical {\n"
"                background-color: #1a1a1a;\n"
"            }"));

        verticalLayout_2->addWidget(textEdit);

        FrameDown = new QFrame(FrameBase);
        FrameDown->setObjectName(QString::fromUtf8("FrameDown"));
        FrameDown->setStyleSheet(QString::fromUtf8("QFrame{\n"
"background-color: rgb(57, 57, 58);\n"
"\n"
"}\n"
""));
        FrameDown->setFrameShape(QFrame::StyledPanel);
        FrameDown->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(FrameDown);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        lineEdit = new QLineEdit(FrameDown);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 22));
        lineEdit->setStyleSheet(QString::fromUtf8(" QLineEdit{\n"
"        border:none;\n"
"        color:white;\n"
"        border-top-left-radius: 10px;\n"
"        border-bottom-left-radius: 10px;\n"
"        background-color: #2a2a2a;\n"
"		padding: 20px;\n"
"        font: 14px;}\n"
"QLineEdit:focus{\n"
"              border: 1px solid #0084d9;}"));

        horizontalLayout->addWidget(lineEdit);

        SendButton = new QPushButton(FrameDown);
        SendButton->setObjectName(QString::fromUtf8("SendButton"));
        SendButton->setMinimumSize(QSize(70, 20));
        SendButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:rgb(46, 121, 240);\n"
"border:none;\n"
"border-top-right-radius: 10px;\n"
"border-bottom-right-radius: 10px;\n"
"color: white;\n"
"\n"
"}\n"
"QPushButton:pressed {\n"
"background-color:rgb(0, 172, 254);\n"
"}"));

        horizontalLayout->addWidget(SendButton);


        verticalLayout_2->addWidget(FrameDown);


        verticalLayout->addWidget(FrameBase);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        SendButton->setText(QApplication::translate("Form", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERFTTAXU_H
