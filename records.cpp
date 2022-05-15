#include "records.h"
#include <QHeaderView>


Records::Records(){
    resize(400,350);
    setMaximumSize(400,400);
    setMinimumSize(120,120);
    setColumnCount(2);
    QStringList strlist;
    strlist << "Попыток" << "Имя";
    setHorizontalHeaderLabels(strlist);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setWindowTitle("Топ 10 игроков");
    AddItem(4, "Маша");
    AddItem(24, "Ворохобко");
    AddItem(8, "MV");
    AddItem(2, "mvv2201");
    AddItem(4, "Миша");
}
void Records::AddItem(int turns, QString name){
    QString str;
    insertRow(rowCount());
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setData(Qt::EditRole, turns);

    setItem(rowCount()-1, 0, item);
    setItem(rowCount()-1, 1, new QTableWidgetItem(name));
    sortItems(0);
    if (rowCount()>10) {
        removeRow(10);
    }


}

