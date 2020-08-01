#include "body_table.hpp"
#include <QVBoxLayout>

BodyTable::BodyTable(Universe* v)
{
    u = v;
    QPushButton* addRow_button = new QPushButton("Add body");
    QPushButton* delRow_button = new QPushButton("Del body");
    QPushButton* addCol_button = new QPushButton("Add parameter");
    QPushButton* delCol_button = new QPushButton("Del parameter");
    QPushButton* update_button = new QPushButton("update");

    body_table = new QTableWidget(1, 2);
    update_box->setText("update was complited");

    body_table->setItem(0, 0, new QTableWidgetItem("Parameter"));
    body_table->setItem(0, 1, new QTableWidgetItem("m"));
    body_table->closePersistentEditor(body_table->item(0, 0));
    body_table->closePersistentEditor(body_table->item(0, 1));

    body_add_widget = new QGroupBox("Add bodies");
    mass_input = new QLineEdit("Mass");
    pos_x_input = new QLineEdit("X position");
    pos_y_input = new QLineEdit("Y position");
    vel_x_input = new QLineEdit("X velocity");
    vel_y_input = new QLineEdit("Y velocity");
    QVBoxLayout* body_layout = new QVBoxLayout;
    body_layout->addWidget(addRow_button);
    body_layout->addWidget(mass_input);
    body_layout->addWidget(pos_x_input);
    body_layout->addWidget(pos_y_input);
    body_layout->addWidget(vel_x_input);
    body_layout->addWidget(vel_y_input);
    body_add_widget->setLayout(body_layout);

    QGridLayout* grid = new QGridLayout;

    grid->addWidget(delRow_button, 0, 1);
    grid->addWidget(addCol_button, 0, 2);
    grid->addWidget(delRow_button, 0, 3);
    grid->addWidget(update_button,  0, 4);
    grid->addWidget(body_table, 0, 1, 1, 5);

    grid->addWidget(body_add_widget, 0, 0);

    connect(addRow_button, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(delRow_button, SIGNAL(clicked()), this, SLOT(delRow()));
    connect(addCol_button, SIGNAL(clicked()), this, SLOT(addCol()));
    connect(delCol_button, SIGNAL(clicked()), this, SLOT(delCol()));
    connect(update_button, SIGNAL(clicked()), this, SLOT(update()));

    this->setLayout(grid);
}

void BodyTable::showBodyTable()
{
    this->show();
}

void BodyTable::addRow()
{
    body_table->insertRow(body_table->rowCount());
}

void BodyTable::delRow()
{
    body_table->removeRow(body_table->rowCount());
    // del body
}

void BodyTable::addCol()
{
    body_table->insertColumn(body_table->columnCount());
    // add parameter
}

void BodyTable::delCol()
{
    body_table->removeColumn(body_table->columnCount());
    // del parameter
}

void BodyTable::update()
{
    for (int i = 1; i < body_table->rowCount(); i++)
    {
        for (int j = 1; j < body_table->columnCount(); j++)
        {
            // add body
        }
    }
    update_box->show();
}
