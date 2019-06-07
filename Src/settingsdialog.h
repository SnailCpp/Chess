#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    static SettingsDialog *instance(QWidget *parent);
    ~SettingsDialog();
    void UpdateDialog();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void SetOk();

private slots:
    void Apply();
    void Confirm();

private:
    static SettingsDialog *INSTANCE;
    explicit SettingsDialog(QWidget *parent = 0);
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
