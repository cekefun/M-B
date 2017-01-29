#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Lexer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow),gram()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BroweGrammar_clicked()
{
    grammarfile = QFileDialog::getOpenFileName(this,tr("Open Grammar"), "/home/", tr("Json Files (*.json)"));
    ui->GrammarEdit->setText(grammarfile);
}

void MainWindow::on_BrowseInput_clicked()
{
    inputfile = QFileDialog::getOpenFileName(this,tr("Open Input"), "/home/");
    ui->InputEdit->setText(inputfile);
}

void MainWindow::on_ApplyButton_clicked(){

    gram = Grammar();
    grammarfile = ui->GrammarEdit->text();
    gram.ParseGrammar(grammarfile.toStdString());

    stringstream stream;
    gram.print(stream);
    QString qstr = QString::fromStdString(stream.str());
    ui->GrammarBrowser->setText(qstr);

    //TO CNF
    gram.convertToCNF();
    stringstream stream2;
    gram.print(stream2);
    qstr = QString::fromStdString(stream2.str());
    ui->CNFBrowser->setText(qstr);
}

void MainWindow::on_CYKParse_clicked()
{
    CYK ck;
    inputfile = ui->InputEdit->text();
    vector<string> vec = lexer::file_to_vec(inputfile.toStdString());


    if(ck.run(vec,gram)){

        ui->IsInGrammarLabel->setText("Is in Grammar");
        this->generate_tree(ck);
    }

    else{
        ui->IsInGrammarLabel->setText("Is not in Grammar");
    }

    QString convert = QString::fromStdString(ck.string_table());
    ui->CYKtable->setText(convert);


}


void MainWindow::on_CYKParse_2_clicked(){

    CYK ck;

    string conv = ui->StringInput->text().toStdString();
    if(ck(conv,gram)){

        ui->RealTimeLabel->setText("Is in Grammar");
        this->generate_tree(ck);
    }

    else{
        ui->RealTimeLabel->setText("Is not in Grammar");
    }

    QString convert = QString::fromStdString(ck.string_table());
    ui->CYKtable->setText(convert);


}

void MainWindow::on_LL1Parse_clicked(){

    Grammar* gr = &this->gram;
    LL1Parser alg(gr);

    inputfile = ui->InputEdit->text();
    vector<string> vec = lexer::file_to_vec(inputfile.toStdString());


    if(alg.Parse(vec)){

        ui->IsInGrammarLabel->setText("Is in Grammar");
        this->tree = *alg.getTree(vec);
        std::system("dot -Tpng -O tree.dot");
        //std::system("xdg-open tree.dot.png");
        QPixmap pixmap("tree.dot.png");
        this->ui->treeImage->setScaledContents(true);

        this->ui->treeImage->setPixmap(pixmap);
        ui->treeImage->setFixedSize(pixmap.size());

    }
    else{
        ui->IsInGrammarLabel->setText("Is not in Grammar");
    }

    stringstream ss;
    alg.Print(ss);
    string str = ss.str();
    QString convert = QString::fromStdString(str);
    ui->CYKtable->setText(convert);


}

void MainWindow::on_LL1Parse_2_clicked(){


    Grammar* gr = &this->gram;
    LL1Parser alg(gr);

    string conv = ui->StringInput->text().toStdString();
    vector<string> vec = lexer::string_to_vec(conv);

    if(alg.Parse(vec)){

        ui->RealTimeLabel->setText("Is in Grammar");
        this->tree = *alg.getTree(vec);
        std::system("dot -Tpng -O tree.dot");
        //std::system("xdg-open tree.dot.png");
        QPixmap pixmap("tree.dot.png");
        this->ui->treeImage->setScaledContents(true);

        this->ui->treeImage->setPixmap(pixmap);
        ui->treeImage->setFixedSize(pixmap.size());

    }
    else{
        ui->RealTimeLabel->setText("Is not in Grammar");
    }

    stringstream ss;
    alg.Print(ss);
    string str = ss.str();
    QString convert = QString::fromStdString(str);
    ui->CYKtable->setText(convert);

}

void MainWindow::generate_tree(CYK& alg){

    this->tree = alg.get_parseTrees(gram)[0];
    tree.to_dot("tree.dot");
    std::system("dot -Tpng -O tree.dot");
    //std::system("xdg-open tree.dot.png");
    QPixmap pixmap("tree.dot.png");
    this->ui->treeImage->setScaledContents(true);

    this->ui->treeImage->setPixmap(pixmap);
    ui->treeImage->setFixedSize(pixmap.size());
    //this->ui->treeImage->setMask(pixmap.mask());

}



void MainWindow::on_exportDOT_clicked()
{

    QString name  = QFileDialog::getSaveFileName(this,
            tr("Export to dot"), "",
            tr("Dot files (*.dot);;All Files (*)"));


    tree.to_dot(name.toStdString());
}


void MainWindow::on_ExportLispe_clicked(){

    QString name  = QFileDialog::getSaveFileName(this,
            tr("Export to Lisp"), "",
            tr("Lisp files (*.lis);;All Files (*)"));


    tree.to_lisp(name.toStdString());
}

void MainWindow::on_SaveCNF_clicked(){

    QString name  = QFileDialog::getSaveFileName(this,
            tr("Save CNF"), "",
            tr("json files (*.json);;All Files (*)"));

    gram.SaveGrammar(name.toStdString());
}
