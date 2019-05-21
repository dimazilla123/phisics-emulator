#ifndef FORMULA_TABLE
#define FORMULA_TABLE
  
#include "parsing.hpp"
#include "universe.hpp"
  
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QTableWidget>
#include <iostream>
#include <vector>
#include <QMessageBox>

class ParameterTable : public QWidget
{
    Q_OBJECT
private:
        QTableWidget* parameter_table = new QTableWidget;
        std::vector<std::int> bodies;
        QMessageBox* update_box = new QMessageBox;
public:
        ParameterTable();
        //~ParameterTable();
public slots:
    void show parameter_table();
    add_row();
    del_row();
    add_col();
    del_col();
    update();
}

