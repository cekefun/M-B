#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>


#include "Grammar.h"
#include "ParseTree.h"
#include "CYK.h"
#include "ll1parser.h"

#include <sstream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BroweGrammar_clicked();

    void on_BrowseInput_clicked();

    void on_ApplyButton_clicked();

    void on_CYKParse_clicked();

    void on_CYKParse_2_clicked();

    void on_exportDOT_clicked();

    void on_LL1Parse_clicked();

    void on_LL1Parse_2_clicked();

    void on_ExportLispe_clicked();

    void on_SaveCNF_clicked();

private:
    Ui::MainWindow *ui;

    QString grammarfile;
    QString inputfile;

    Grammar gram;
    Grammar gram_origin;
    ParseTree tree;

    void generate_tree(CYK& alg);
};

#endif // MAINWINDOW_H
