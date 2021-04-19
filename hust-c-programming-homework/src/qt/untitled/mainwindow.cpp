#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CMD_INCLUDE_ONCE_CONFIRMER
#include "cmder.h"

#include <QMessageBox>
#include <QHeaderView>

class TaskInfo
{
public:
    QString subcmd;
    std::list<QString> required;
    std::list<QString> optional;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->hide();
    this->setWindowTitle("chw-qt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void QuickMessageBox(const QString &s)
{
    QMessageBox msgBox;
    msgBox.setText(s);
    msgBox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    QStringToList("123|666\n111|876", std::list<QString>{"t1", "t2"});
}

void MainWindow::QStringToList(const QString &stdout, const std::list<QString> &ListHeadTitle)
{
    QStringList lines = stdout.split('\n');
    auto rowSize = lines.size() + 1;
    auto colSize = ListHeadTitle.size();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(rowSize);
    ui->tableWidget->setColumnCount(colSize);

    auto cter = 0;
    auto rowCter = 1;
    auto colCter = 0;
    for(auto iter = ListHeadTitle.begin(); cter < colSize && iter != ListHeadTitle.end(); ++iter, ++cter)
    {//header
        ui->tableWidget->setItem(0, cter, new QTableWidgetItem(*iter));
    }
    for(auto rowIter = lines.begin(); rowCter < rowSize && rowIter != lines.end(); ++rowCter, ++rowIter)
    {
        QStringList elements = rowIter->split('|');
        for(auto colIter = elements.begin(); colCter < colSize && colIter != elements.end(); ++colCter, ++colIter)
        {
            ui->tableWidget->setItem(rowCter, colCter, new QTableWidgetItem(*colIter));
        }
        colCter = 0; //Fake scope clean.
    }
}

#include "../inputer/inputer.h"
#include <memory>
bool MainWindow::executeTask(const TaskInfo &task, bool isListing)
{
    return executeTask(task, isListing, std::list<QString>());
}
bool MainWindow::executeTask(const TaskInfo &task, bool isListing, const std::list<QString> &ListHeadTitle)
{ //TODO: isListing not implemented.
    std::unique_ptr<Inputer> inputerWin(new Inputer());
    for(auto & s : task.required)
        inputerWin.get()->AddPara(s, true);
    for(auto & s : task.optional)
        inputerWin.get()->AddPara(s, false);
    inputerWin.get()->show();
    if(inputerWin.get()->exec() != QDialog::Accepted)
        return false;
    auto params = inputerWin.get()->GetDatAndReset();

    QString cmd = "./chw-cli " + task.subcmd;
    auto iter = params.begin();
    for(auto & s : task.required)
    {
        if(iter->isEmpty())
        {
            QuickMessageBox("Error: Required argument '" + s + "' not provided.");
            return false;
        }
        cmd += " '" + *iter + "'";
        ++iter;
    }
    for(auto & s : task.optional)
    {
        if(iter->isEmpty())
        {
            ++iter;
            continue;
        }
        cmd += " --" + s + "='" + *iter + "'";
        ++iter;
    }
    //QuickMessageBox("Debug: CMD>" + cmd);
    QString result = cmder()(cmd);
    if(result.contains("Exception at"))
    {
        QuickMessageBox(result);
        return false;
    }
    if(isListing)
        QStringToList(result, ListHeadTitle);
    return true;
}

using strlist = std::list<QString>;

void MainWindow::on_cls_set_clicked()
{
    executeTask(TaskInfo{"veg-class-set", strlist{"classNumber", "className"}, strlist{}}, false);
}

void MainWindow::on_cls_ls_clicked()
{
    executeTask(TaskInfo{"veg-class-ls", strlist{}, strlist{"code"}}, true, strlist{"classNum", "className"});
}

void MainWindow::on_cls_rm_clicked()
{
    executeTask(TaskInfo{"veg-class-rm", strlist{"classNumber"}, strlist{}}, false);
}

void MainWindow::on_veg_set_clicked()
{
    executeTask(TaskInfo{"veg-info-set", strlist{"vegName", "classNumber", "nutrition"}, strlist{}}, false);
}

void MainWindow::on_veg_ls_clicked()
{
    executeTask(TaskInfo{"veg-info-ls", strlist{}, strlist{"name-keyword", "neu-keyword", "class-code"}}, true, strlist{"vegNumber", "vegName", "classNumber", "nutrition"});
}

void MainWindow::on_veg_rm_clicked()
{
    executeTask(TaskInfo{"veg-info-rm", strlist{"vegName"}, strlist{}}, false);
}

void MainWindow::on_job_set_clicked()
{
    executeTask(TaskInfo{"job-set", strlist{"jobNumber", "vegNumber", "area", "weight", "year"}, strlist{}}, false);
}

void MainWindow::on_job_ls_clicked()
{
    executeTask(TaskInfo{"job-ls", strlist{}, strlist{"veg-name-keyword", "veg-name", "year"}}, true, strlist{"jobNumber", "vegNumber", "vegName", "area", "weight", "year"});
}

void MainWindow::on_job_rm_clicked()
{
    executeTask(TaskInfo{"job-rm", strlist{"jobNumber"}, strlist{}}, false);
}

void MainWindow::on_rep1_clicked()
{
    executeTask(TaskInfo{"job-report-by-veg-class", strlist{}, strlist{}}, true, strlist{"className", "sumArea", "sumWeight"});
}

void MainWindow::on_rep2_clicked()
{
    executeTask(TaskInfo{"job-report-by-year-and-veg-name", strlist{"YearBegin", "YearEnd"}, strlist{}}, true, strlist{"vegName", "className", "sumArea", "sumWeight(decrease)"});
}

void MainWindow::on_rep3_clicked()
{
    executeTask(TaskInfo{"check-weight-by-veg-class", strlist{"classNumber"}, strlist{}}, true, strlist{"sumWeight"});
}

