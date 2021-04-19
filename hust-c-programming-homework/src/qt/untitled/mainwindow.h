#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TaskInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cls_set_clicked();

    void on_cls_ls_clicked();

    void on_cls_rm_clicked();

    void on_veg_set_clicked();

    void on_veg_ls_clicked();

    void on_veg_rm_clicked();

    void on_job_set_clicked();

    void on_job_ls_clicked();

    void on_job_rm_clicked();

    void on_rep1_clicked();

    void on_rep2_clicked();

    void on_rep3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void QStringToList(const QString &stdout, const std::list<QString> &ListHeadTitle);
    bool executeTask(const TaskInfo &, bool isListing, const std::list<QString> &parameterTitle);
    bool executeTask(const TaskInfo &, bool isListing);
};

#endif // MAINWINDOW_H
