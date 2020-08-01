#include "formula_table.hpp"

FormulaTable::FormulaTable(Universe* u_)
{
    u = u_;
    QPushButton* add_button = new QPushButton("Add");
    QPushButton* del_button = new QPushButton("Del");
    QPushButton* check_button = new QPushButton("Check");
    QGridLayout* grid = new QGridLayout;

    forces_table = new QTableWidget(0, 1);
    err_box->setText("Formula Error");

    grid->addWidget(add_button, 0, 0);
    grid->addWidget(check_button, 0, 2);
    grid->addWidget(del_button, 0, 1);
    grid->addWidget(forces_table, 1, 0, 1, 3);
    
    connect(add_button, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(delRow()));
    connect(check_button, SIGNAL(clicked()), this, SLOT(check()));

    this->setLayout(grid);
}

void FormulaTable::showForcesTable()
{
    this->show();
}

void FormulaTable::addRow()
{
    forces_table->insertRow(forces_table->rowCount());
    forces_table->setItem(0, forces_table->rowCount(), new QTableWidgetItem);
}

void FormulaTable::delRow()
{
    auto item = forces_table->currentItem();
    int row = -1;
    if (item)
        row = item->row();
    if (row == -1 && forces_table->rowCount() != 0)
        row = forces_table->rowCount() - 1;
    if (row != -1) {
        forces_table->removeRow(row);
        if (u->forces.size() > 0) {
            u->forces.erase(u->forces.begin() + row);
            u->forcename.erase(u->forcename.begin() + row);
        }
    }
}

void FormulaTable::check()
{
    u->forces.clear();
    u->forcename.clear();
    bool flag = false;
    for (int i = 0; i < forces_table->rowCount(); i++)
        if (forces_table->item(i, 0) == nullptr || formula(forces_table->item(i, 0)->text().toStdString(), 0).is_failed)
        {
            forces_table->setItem(i, 0, new QTableWidgetItem);
            forces_table->item(i, 0)->setBackground(Qt::red);
            flag = true;
        }
        else
        {
            std::cerr << "Adding force" << "\n";
            forces_table->item(i, 0)->setBackground(Qt::green);
            auto parsed = formula(forces_table->item(i, 0)->text().toStdString(), 0);
            auto f = createFuncFromCalc(parsed.data);
            u->addForce(f, forces_table->item(i, 0)->text().toStdString());
        }
    if (flag)
        err_box->show();
}

void FormulaTable::reload()
{
    forces_table->clear();
    for (int i = 0; i < u->forces.size(); i++) {
        addRow();
        forces_table->setItem(i, 0, new QTableWidgetItem(QString(u->forcename[i].c_str())));
    }
}
