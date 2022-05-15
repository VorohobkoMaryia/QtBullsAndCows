#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QInputDialog>
#include <QDir>
#include <QRandomGenerator>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->vlInterface);
    setWindowTitle("Быки и коровы");
    ui->twResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartGame(){
    key = Answer();
    gived_up = false;
    ui->leInput->setEnabled(true);
    ui->pbNewGame->setText("Сдаться(");
    ui->lbStart->setText("Начните игру, введите число");
    for (int i = ui->twResults->rowCount(); i >= 0; i--) {
        ui->twResults->removeRow(i);
    }
}

void MainWindow::on_pbNewGame_clicked()
{
    if (!gived_up)
    {
        GiveUp();
    }
    else {
        StartGame();
    }
}


QString MainWindow::Answer() {
    QRandomGenerator* rnd = new QRandomGenerator;
    QString str = "", result = "";
    int step = 0;
    while (step < 4){
        str.setNum(rnd->global()->bounded(0,9));
        if (!result.contains(str)) {
            ++step;
            result += str;
        }
    }
    return result;
}

QString MainWindow::CountBulls(QString key, QString value) {
    int bulls = 0;
    for (int i = 0; i < 4; i++) {
        if (key.at(i) == value.at(i)) {
            ++bulls;
        }
    }
    return value.setNum(bulls);
}

QString MainWindow::CountCows(QString key, QString value) {
    int cows = 0;
    for (int i = 0; i < 4; i++) {
        if (key.contains(value.at(i),Qt::CaseInsensitive)) {
            ++cows;
        }
    }
    return value.setNum(cows);
}

void MainWindow::on_pbEnter_clicked()
{
    QString str = ui->leInput->text();
    if (Check(str)) {
        ui->leInput->clear();
        ui->twResults->insertRow(ui->twResults->rowCount());
        ui->twResults->setItem(ui->twResults->rowCount()-1, 0, new QTableWidgetItem(str));
        turns++;

        QString bulls = CountBulls(key, str), cows = CountCows(key, str);
        QString answer =" Быки: "+bulls+ ", Коровы: " + cows ;
        ui->twResults->setItem(ui->twResults->rowCount()-1, 1, new QTableWidgetItem(answer));
        ui->lbStart->setText(answer);
        if (bulls == "4") {
            Victory();
        }
    }
    else {
        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setWindowTitle("Ошибка :_(");
        error.setText("Введены некорректные данные");
        error.exec();
    }
}

bool MainWindow::Check(QString str) {
    if (str.length()!=4)
    {
        return false;
    }
    for (int i = 0; i < 4; i++)
    {
        if ((!str.at(i).isDigit())||(str.count(str.at(i))!=1)) { return false; }
    }
    return true;
}



void MainWindow::Victory() {
    ui->pbNewGame->setText("Попробовать ещё раз");
    ui->lbStart->setText("Вы победили!!!");
    bool ok;
    QString text = QInputDialog::getText(this, tr("Введите"),tr("Имя:"), QLineEdit::Normal,QDir::home().dirName(), &ok);
    TableRecords.show();
    if (ok && !text.isEmpty()) {
        TableRecords.AddItem(turns, text);
    }
    turns = 0;
    ui->leInput->setEnabled(false);
}
void MainWindow::GiveUp() {
    gived_up = true;
    ui->leInput->setEnabled(false);
    ui->lbStart->setText("Ответом было число " + key);
    ui->pbNewGame->setText("Попробовать ещё раз");
}
void MainWindow::on_pbRecords_clicked()
{
    TableRecords.show();
}
