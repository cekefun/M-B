/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_10;
    QTabWidget *tabWidget;
    QWidget *GrammarTab;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *GrammarLabel;
    QLineEdit *GrammarEdit;
    QPushButton *BroweGrammar;
    QVBoxLayout *verticalLayout;
    QPushButton *ApplyButton;
    QPushButton *SaveCNF;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *GrammarBrowser;
    QTextBrowser *CNFBrowser;
    QWidget *ParserTab;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QLabel *InputLabelParse;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *InputLabel;
    QLineEdit *InputEdit;
    QPushButton *BrowseInput;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *CYKParse;
    QPushButton *LL1Parse;
    QLabel *IsInGrammarLabel;
    QFrame *line;
    QVBoxLayout *verticalLayout_8;
    QLabel *CommandLineLabel;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *InputLabel_2;
    QLineEdit *StringInput;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *CYKParse_2;
    QPushButton *LL1Parse_2;
    QLabel *RealTimeLabel;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *ExportLispe;
    QPushButton *exportDOT;
    QTextBrowser *CYKtable;
    QWidget *ParseTree;
    QVBoxLayout *verticalLayout_11;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_12;
    QLabel *treeImage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(689, 460);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_10 = new QVBoxLayout(centralWidget);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        GrammarTab = new QWidget();
        GrammarTab->setObjectName(QString::fromUtf8("GrammarTab"));
        verticalLayout_5 = new QVBoxLayout(GrammarTab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        GrammarLabel = new QLabel(GrammarTab);
        GrammarLabel->setObjectName(QString::fromUtf8("GrammarLabel"));

        horizontalLayout->addWidget(GrammarLabel);

        GrammarEdit = new QLineEdit(GrammarTab);
        GrammarEdit->setObjectName(QString::fromUtf8("GrammarEdit"));

        horizontalLayout->addWidget(GrammarEdit);

        BroweGrammar = new QPushButton(GrammarTab);
        BroweGrammar->setObjectName(QString::fromUtf8("BroweGrammar"));

        horizontalLayout->addWidget(BroweGrammar);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ApplyButton = new QPushButton(GrammarTab);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));

        verticalLayout->addWidget(ApplyButton);

        SaveCNF = new QPushButton(GrammarTab);
        SaveCNF->setObjectName(QString::fromUtf8("SaveCNF"));

        verticalLayout->addWidget(SaveCNF);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(GrammarTab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        label_2 = new QLabel(GrammarTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        GrammarBrowser = new QTextBrowser(GrammarTab);
        GrammarBrowser->setObjectName(QString::fromUtf8("GrammarBrowser"));

        horizontalLayout_2->addWidget(GrammarBrowser);

        CNFBrowser = new QTextBrowser(GrammarTab);
        CNFBrowser->setObjectName(QString::fromUtf8("CNFBrowser"));

        horizontalLayout_2->addWidget(CNFBrowser);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);

        tabWidget->addTab(GrammarTab, QString());
        ParserTab = new QWidget();
        ParserTab->setObjectName(QString::fromUtf8("ParserTab"));
        verticalLayout_13 = new QVBoxLayout(ParserTab);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        InputLabelParse = new QLabel(ParserTab);
        InputLabelParse->setObjectName(QString::fromUtf8("InputLabelParse"));

        verticalLayout_7->addWidget(InputLabelParse);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        InputLabel = new QLabel(ParserTab);
        InputLabel->setObjectName(QString::fromUtf8("InputLabel"));

        horizontalLayout_3->addWidget(InputLabel);

        InputEdit = new QLineEdit(ParserTab);
        InputEdit->setObjectName(QString::fromUtf8("InputEdit"));

        horizontalLayout_3->addWidget(InputEdit);

        BrowseInput = new QPushButton(ParserTab);
        BrowseInput->setObjectName(QString::fromUtf8("BrowseInput"));

        horizontalLayout_3->addWidget(BrowseInput);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        CYKParse = new QPushButton(ParserTab);
        CYKParse->setObjectName(QString::fromUtf8("CYKParse"));

        horizontalLayout_4->addWidget(CYKParse);

        LL1Parse = new QPushButton(ParserTab);
        LL1Parse->setObjectName(QString::fromUtf8("LL1Parse"));

        horizontalLayout_4->addWidget(LL1Parse);

        IsInGrammarLabel = new QLabel(ParserTab);
        IsInGrammarLabel->setObjectName(QString::fromUtf8("IsInGrammarLabel"));

        horizontalLayout_4->addWidget(IsInGrammarLabel);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout_2);


        verticalLayout_9->addLayout(verticalLayout_7);

        line = new QFrame(ParserTab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        CommandLineLabel = new QLabel(ParserTab);
        CommandLineLabel->setObjectName(QString::fromUtf8("CommandLineLabel"));

        verticalLayout_8->addWidget(CommandLineLabel);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        InputLabel_2 = new QLabel(ParserTab);
        InputLabel_2->setObjectName(QString::fromUtf8("InputLabel_2"));

        horizontalLayout_7->addWidget(InputLabel_2);

        StringInput = new QLineEdit(ParserTab);
        StringInput->setObjectName(QString::fromUtf8("StringInput"));

        horizontalLayout_7->addWidget(StringInput);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        CYKParse_2 = new QPushButton(ParserTab);
        CYKParse_2->setObjectName(QString::fromUtf8("CYKParse_2"));

        horizontalLayout_8->addWidget(CYKParse_2);

        LL1Parse_2 = new QPushButton(ParserTab);
        LL1Parse_2->setObjectName(QString::fromUtf8("LL1Parse_2"));

        horizontalLayout_8->addWidget(LL1Parse_2);

        RealTimeLabel = new QLabel(ParserTab);
        RealTimeLabel->setObjectName(QString::fromUtf8("RealTimeLabel"));

        horizontalLayout_8->addWidget(RealTimeLabel);


        verticalLayout_6->addLayout(horizontalLayout_8);


        verticalLayout_8->addLayout(verticalLayout_6);


        verticalLayout_9->addLayout(verticalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        ExportLispe = new QPushButton(ParserTab);
        ExportLispe->setObjectName(QString::fromUtf8("ExportLispe"));

        horizontalLayout_6->addWidget(ExportLispe);

        exportDOT = new QPushButton(ParserTab);
        exportDOT->setObjectName(QString::fromUtf8("exportDOT"));

        horizontalLayout_6->addWidget(exportDOT);


        verticalLayout_9->addLayout(horizontalLayout_6);

        CYKtable = new QTextBrowser(ParserTab);
        CYKtable->setObjectName(QString::fromUtf8("CYKtable"));

        verticalLayout_9->addWidget(CYKtable);


        verticalLayout_13->addLayout(verticalLayout_9);

        tabWidget->addTab(ParserTab, QString());
        ParseTree = new QWidget();
        ParseTree->setObjectName(QString::fromUtf8("ParseTree"));
        verticalLayout_11 = new QVBoxLayout(ParseTree);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        scrollArea = new QScrollArea(ParseTree);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 647, 355));
        verticalLayout_12 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        treeImage = new QLabel(scrollAreaWidgetContents);
        treeImage->setObjectName(QString::fromUtf8("treeImage"));

        verticalLayout_12->addWidget(treeImage);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_11->addWidget(scrollArea);

        tabWidget->addTab(ParseTree, QString());

        verticalLayout_10->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Parser", 0, QApplication::UnicodeUTF8));
        GrammarLabel->setText(QApplication::translate("MainWindow", "Grammar", 0, QApplication::UnicodeUTF8));
        BroweGrammar->setText(QApplication::translate("MainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        ApplyButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        SaveCNF->setText(QApplication::translate("MainWindow", "SaveCNF", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Grammar", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "CNF", 0, QApplication::UnicodeUTF8));
        GrammarBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">The grammar will be printed here</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        CNFBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">The Grammar  in CNF will be printed here</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(GrammarTab), QApplication::translate("MainWindow", "Grammar", 0, QApplication::UnicodeUTF8));
        InputLabelParse->setText(QApplication::translate("MainWindow", "File Input", 0, QApplication::UnicodeUTF8));
        InputLabel->setText(QApplication::translate("MainWindow", "Input", 0, QApplication::UnicodeUTF8));
        InputEdit->setText(QApplication::translate("MainWindow", "Enter a filename here", 0, QApplication::UnicodeUTF8));
        BrowseInput->setText(QApplication::translate("MainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        CYKParse->setText(QApplication::translate("MainWindow", "CYKParse", 0, QApplication::UnicodeUTF8));
        LL1Parse->setText(QApplication::translate("MainWindow", "LL1Parse", 0, QApplication::UnicodeUTF8));
        IsInGrammarLabel->setText(QString());
        CommandLineLabel->setText(QApplication::translate("MainWindow", "RealTime Input", 0, QApplication::UnicodeUTF8));
        InputLabel_2->setText(QApplication::translate("MainWindow", "Input", 0, QApplication::UnicodeUTF8));
        StringInput->setText(QApplication::translate("MainWindow", "A string, to be evaluated", 0, QApplication::UnicodeUTF8));
        CYKParse_2->setText(QApplication::translate("MainWindow", "CYKParse", 0, QApplication::UnicodeUTF8));
        LL1Parse_2->setText(QApplication::translate("MainWindow", "LL1Parse", 0, QApplication::UnicodeUTF8));
        RealTimeLabel->setText(QString());
        ExportLispe->setText(QApplication::translate("MainWindow", "ExportLisp", 0, QApplication::UnicodeUTF8));
        exportDOT->setText(QApplication::translate("MainWindow", "ExportDOT", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(ParserTab), QApplication::translate("MainWindow", "Parser", 0, QApplication::UnicodeUTF8));
        treeImage->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(ParseTree), QApplication::translate("MainWindow", "Tree", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
