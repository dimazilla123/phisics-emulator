#include "formula_table.hpp"

FormulaTable::FormulaTable()
{
    QPushButton* add_button = new QPushButton;
    QPushButton* del_button = new QPushButton;
    QPushButton* check_button = new QPushButton;
    QGridLayout* grid = new QGridLayout;

    forces_table = new QTableWidget(0, 1);
    err_box->setText("Formula Error");

    grid->addWidget(add_button, 0, 0);
    grid->addWidget(check_button, 0, 2);
    grid->addWidget(del_button, 0, 1);
    grid->addWidget(forces_table, 1, 0, 0, 3);
    
    connect(add_button, SIGNAL(clicked()), this, SLOT(add_row));
    connect(del_button, SIGNAL(clicked()), this, SLOT(del_row));
    connect(check_button, SIGNAL(clicked()), this, SLOT(check));

    this->setLayout(grid);
}

void FormulaTable::show_forces_table()
{
    this->show();
}

void FormulaTable::add_row()
{
    forces_table->insertRow(forces_table->rowCount());
    forces_table->setItem(0, forces_table->rowCount(), new QTableWidgetItem);

    formulas.push_back("item");
}

void FormulaTable::del_row()
{
    forces_table->removeRow(forces_table->rowCount());
    formulas.pop_back();
}

void FormulaTable::clicked()
{
    bool flag = false;
    for (int i = 0; i < formulas.size(); i++)
    if (forces_table->item(0, i) == nullptr || formula(forces_table->item(0, i)->text().toStdString(), 0).is_failed)
    {
        forces_table->setItem(0, i, new QTableWidgetItem);
        forces_table->item(0, i)->setBackground(Qt:red);
    }
    else
    {
        forces_table->item(0, i)->setBackground(Qt::green);
        forceFunction f = createFuncFromCalc(formula(forces_table->item(0, i)->text().toStdString(), 0).data);
        u->addForce(f, s);
    }
}
