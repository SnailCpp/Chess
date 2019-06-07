#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "gamesettings.h"
#include "chesslog.h"
#include <QDesktopWidget>
#include <QStringList>


SettingsDialog * SettingsDialog::INSTANCE = 0;
SettingsDialog * SettingsDialog::instance(QWidget *parent)
{
    if(!INSTANCE)
    {
        INSTANCE = new SettingsDialog(parent);
    }
    return INSTANCE;
}

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    // 隐藏帮助按钮和关闭按钮
    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);

    QDesktopWidget *desk=QApplication::desktop();
    this->setModal(true);
    this->move( (desk->width() - this->width()) / 2,
                          (desk->height() - this->height()) /2 );
    this->show();
    UpdateDialog();

    connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(Apply()));
    connect(ui->btnConfirm, SIGNAL(clicked()), this, SLOT(Confirm()));

    Chess_Trace("new SettingDialog");
}

SettingsDialog::~SettingsDialog()
{
    Chess_Trace("delete SettingDialog");
    delete ui;
}

void SettingsDialog::UpdateDialog()
{
    QStringList stringList;

    stringList << "人人对战" << "人机对战" << "机机对战";
    ui->cmbGameType->addItems(stringList);
    ui->cmbGameType->setCurrentIndex(g_gameSettings.GetGameType());

    stringList.clear();
    stringList << "红" << "黑";
    ui->cmbCompetitorSide->addItems(stringList);
    ui->cmbCompetitorSide->setCurrentIndex(g_gameSettings.GetCompetitorSide());

    stringList.clear();
    stringList << "红" << "黑";
    ui->cmbAhead->addItems(stringList);
    ui->cmbAhead->setCurrentIndex(g_gameSettings.GetAhead());

    ui->ledStepTime->setText(QString::number(g_gameSettings.GetStepTime(), 10));
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void SettingsDialog::Apply()            // 保存配置
{
    g_gameSettings.SetGameType(ui->cmbGameType->currentIndex());
    g_gameSettings.SetCompetitorSide(ui->cmbCompetitorSide->currentIndex());
    g_gameSettings.SetAhead(ui->cmbAhead->currentIndex());
    g_gameSettings.SetStepTime(ui->ledStepTime->text().toInt());
    g_gameSettings.SaveSettings();
}

void SettingsDialog::Confirm()
{
    Apply();
    QDialog::accept();
    emit SetOk();
}
