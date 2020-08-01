#ifndef FORMULA_TABLE
#define FORMULA_TABLE

#include "parsing.hpp"
#include "universe.hpp"
#include "semantics.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QTableWidget>
#include <iostream>
#include <vector>
#include <QMessageBox>


class FormulaTable : public QWidget
{
    Q_OBJECT
private:
    QTableWidget* forces_table;
    std::vector<std::string> formulas;
    QMessageBox* err_box = new QMessageBox;
    Universe* u;
public:
    FormulaTable(Universe* u);
    //~BodyTable();
public slots:
    void show_forces_table();
    void add_row();
    void del_row();
    void check();
    void reload();
};


#endif
