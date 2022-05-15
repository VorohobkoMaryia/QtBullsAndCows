#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QTableWidget>

class Records : public QTableWidget
{
public:
    Records();
    void AddItem(int,QString);
};

#endif // RECORDS_H
