#ifndef FORMULA_TABLE_HPP
#define FORMULA_TABLE_HPP
  
#include "parsing.hpp"
#include "universe.hpp"
  
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <iostream>
#include <vector>
#include <QMessageBox>

class BodyTable : public QWidget
{
    Q_OBJECT
private:
        QTableWidget* body_table = new QTableWidget;
        std::vector<int> bodies;
        QMessageBox* update_box = new QMessageBox;
        QGroupBox* body_add_widget;
        QLineEdit* mass_input;
        QLineEdit* pos_x_input;
        QLineEdit* pos_y_input;
        QLineEdit* vel_x_input;
        QLineEdit* vel_y_input;
        universe* u;
public:
        BodyTable(universe* v);
public slots:
    void show_body_table();
    void add_row();
    void del_row();
    void add_col();
    void del_col();
    void update();
};
#endif
