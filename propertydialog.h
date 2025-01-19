#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include <QDialog>

namespace Ui {
class PropertyDialog;
}

class PropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertyDialog(QWidget *parent = nullptr);
    ~PropertyDialog();
    int getLineNum();
    int getRowNum();
    int getSpeedNum();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::PropertyDialog *ui;
};

#endif // PROPERTYDIALOG_H
