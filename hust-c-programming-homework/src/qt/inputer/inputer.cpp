#include "inputer.h"
#include "ui_inputer.h"

Inputer::Inputer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inputer)
{
    ui->setupUi(this);
    this->setWindowTitle("uniform-inputer");
    ui->e1->hide();
    ui->e2->hide();
    ui->e3->hide();
    ui->e4->hide();
    ui->e5->hide();
    ui->l1->hide();
    ui->l2->hide();
    ui->l3->hide();
    ui->l4->hide();
    ui->l5->hide();
}

Inputer::~Inputer()
{
    delete ui;
}

auto Inputer::IntToEle(int i) const
{
    if(i > 4)
        throw std::runtime_error("IntToEle: overflow");
    decltype(ui->e1) editEle;
    decltype(ui->l1) labelEle;
#define _CODEGEN_COUNTER_TO_ELE(n) case n-1:editEle = ui->e##n; labelEle = ui->l##n; break;
    switch(i)
    {
    _CODEGEN_COUNTER_TO_ELE(1)
    _CODEGEN_COUNTER_TO_ELE(2)
    _CODEGEN_COUNTER_TO_ELE(3)
    _CODEGEN_COUNTER_TO_ELE(4)
    _CODEGEN_COUNTER_TO_ELE(5)
    default:
        throw std::runtime_error("If you're here, you're fucked.");
    }
#undef _CODEGEN_ADDPARA
    return std::make_pair(labelEle, editEle);
}

//Fake dynamic alloc
void Inputer::AddPara(const QString &lName, bool must)
{
    auto eles = IntToEle(counter);
    eles.first->setText(must ? lName + "*" : lName);
    eles.first->show();
    eles.second->show();
    ++counter;
}

std::vector<QString> Inputer::GetDatAndReset() const
{
    std::vector<QString> buf;
    for(size_t cter = 0; cter < 5; ++cter)
        buf.push_back(IntToEle(cter).second->text());
    return std::move(buf);
}
