#ifndef STEPLIST_H
#define STEPLIST_H

#include <QWidget>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>

class StepList : public QWidget
{
    Q_OBJECT
public:
    static StepList *instance(QWidget *parent);
    ~StepList();

    void ClearStepList();

signals:
    void CurrentRow(int row1, int row2);

public slots:
    void ShowStepList(QString step);
    void ClearLastStep();    
    void SelectionStep(int row);

private:
    static StepList *INSTANCE;
    explicit StepList(QWidget *parent = 0);

    QListView *listView;
    QStandardItemModel *model;
};

#endif // STEPLIST_H
