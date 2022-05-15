#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "records.h"
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Records TableRecords;
    QString key = "1234";
    int turns = 0;
    QString CountBulls(QString, QString);
    QString CountCows(QString, QString);
    void Victory();
    void StartGame();
    void RestartGame();
    void GiveUp();
    bool Check(QString str);
    bool gived_up = true;
    QString Answer();

private slots:
    void on_pbEnter_clicked();
    void on_pbRecords_clicked();
    void on_pbNewGame_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
