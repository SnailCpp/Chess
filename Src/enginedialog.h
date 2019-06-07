#ifndef EngineDIALOG_H
#define EngineDIALOG_H

#include <QDialog>

namespace Ui {
class EngineDialog;
}

class EngineDialog : public QDialog
{
    Q_OBJECT

public:
    static EngineDialog *instance(QWidget *parent);
    ~EngineDialog();

    void ShowEngineName(QString* engineName);

signals:
    checked_checkBox(int &id);

private slots:
    void on_buttonBox_accepted();

private:
    static  EngineDialog * INSTANCE;
    explicit EngineDialog(QWidget *parent = 0);

    Ui::EngineDialog *ui;
};

#endif // EngineDIALOG_H
