#include "infolist.h"
#include "chessbase.h"
#include "chesslog.h"

InfoList * InfoList::INSTANCE = 0;
InfoList * InfoList::instance(QWidget *parent)
{
    if(!INSTANCE)
    {
        INSTANCE = new InfoList(parent);
    }
    return INSTANCE;
}

InfoList::InfoList(QWidget *parent) : QWidget(parent)
{
    resize(205,235);
    move(619, 435);

    view = new QListView(this);
    model = new QStandardItemModel();

    view->resize(205,235);
    view->setModel(model);

    Chess_Trace("new InfoList");
}

InfoList::~InfoList()
{
    Chess_Trace("delete InfoList");
}

void InfoList::ShowInfoList(QString info)
{
    QStringList strList = info.split("\r\n", QString::SkipEmptyParts);

    QStringList::const_iterator const_iter;
    for(const_iter = strList.cbegin(); const_iter != strList.cend();
        ++const_iter){
        QStandardItem *item =  new QStandardItem();
        item->setText(*const_iter);
        item->setEditable(false);
        model->appendRow(item);
        view->scrollToBottom();
    }
}

void InfoList::ClearInfoList()
{
    model->clear();
}
