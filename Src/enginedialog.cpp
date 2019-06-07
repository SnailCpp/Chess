#include "enginedialog.h"
#include "ui_enginedialog.h"
#include "chesslog.h"

EngineDialog * EngineDialog::INSTANCE = 0;
EngineDialog * EngineDialog::instance(QWidget *parent)
{
    if(!INSTANCE)
    {
        INSTANCE = new EngineDialog(parent);
    }
    return INSTANCE;
}

EngineDialog::EngineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EngineDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    Chess_Trace("new EngineDialog");
}

EngineDialog::~EngineDialog()
{
    Chess_Trace("delete EngineDialog");
    delete ui;
}

void EngineDialog::ShowEngineName(QString *engineName)
{
    ui->checkBox->setText(engineName[0]);
    ui->checkBox_2->setText(engineName[1]);    
}

void EngineDialog::on_buttonBox_accepted()
{
    int id;
    if(ui->checkBox->isChecked()){
        qDebug() << ui->checkBox->text();
        id = 0;
        emit checked_checkBox(id);
    }
    if(ui->checkBox_2->isChecked()){
        qDebug() << ui->checkBox_2->text();
        id = 1;
        emit checked_checkBox(id);
    }
}
