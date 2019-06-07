#include "steplist.h"
#include "chessbase.h"
#include "chesslog.h"

StepList * StepList::INSTANCE = 0;
StepList * StepList::instance(QWidget *parent)
{
    if(!INSTANCE)
    {
        INSTANCE = new StepList(parent);
    }
    return INSTANCE;
}

StepList::StepList(QWidget *parent) : QWidget(parent)
{
    resize(300, 235);
    move(619/*STEPLIST_STARTX*/, 145);

    listView = new QListView(this);
    model = new QStandardItemModel();

    listView->resize(205,235);
    listView->setModel(model);

    Chess_Trace("new StepList");
}

StepList::~StepList()
{
    Chess_Trace("delete StepList");
}

void StepList::ShowStepList(QString step)
{
    QStandardItem *item = new QStandardItem(step);
    item->setEditable(false);
    item->setTextAlignment(Qt::AlignCenter);
    model->appendRow(item);
    listView->setCurrentIndex(model->indexFromItem(item));
}

void StepList::ClearLastStep()
{
    int last = model->rowCount() - 1;
    model->removeRow(last);
}

void StepList::ClearStepList()
{
    model->clear();
}

void StepList::SelectionStep(int row)
{
    listView->setCurrentIndex(model->index(row - 1,0));
}
