#ifndef INPUTER_H
#define INPUTER_H

#include <QDialog>

namespace Ui {
class Inputer;
}

class Inputer : public QDialog
{
    Q_OBJECT

public:
    explicit Inputer(QWidget *parent = 0);
    ~Inputer();

    void AddPara(const QString &lName, bool must);
    std::vector<QString> GetDatAndReset() const;

private:
    auto IntToEle(int i) const;
    size_t counter = 0;
    Ui::Inputer *ui;
};

#endif // INPUTER_H
