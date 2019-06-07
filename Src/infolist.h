#ifndef INFOLIST_H
#define INFOLIST_H

#include <QWidget>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>

class InfoList : public QWidget
{
    Q_OBJECT
public:
    static InfoList *instance(QWidget *parent);
    ~InfoList();

    void ClearInfoList();
    void ShowInfoList(QString info);

private:
    static InfoList *INSTANCE;
    explicit InfoList(QWidget *parent = 0);

    QListView *view;
    QStandardItemModel *model;
};

#endif // INFOLIST_H
