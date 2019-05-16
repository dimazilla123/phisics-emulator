#include "interface.hpp"
#include <vector>

interface::interface (universe vers, int w, int h, double s)
{
    this->u = vers;
    this->speed = s;

    QGroupBox *canvas_box = new QGroupBox ("Universe");
    canvas_box->setMinimumSize (w, h);

    this->canvas = new Canvas (canvas_box);
    this->canvas->setMinimumSize (w, h);
    this->body_add_widget = new QGroupBox ("Add bodies");
    this->update_initor = new QCheckBox ("Update");
    this->mass_input = new QLineEdit ("Mass");
    this->pos_x_input = new QLineEdit ("X position");
    this->pos_y_input = new QLineEdit ("Y position");
    this->vel_x_input = new QLineEdit ("X velocity");
    this->vel_y_input = new QLineEdit ("Y velocity");

    QPushButton *add_body_button = new QPushButton ("Add body");

    QVBoxLayout *gloabal_layout = new QVBoxLayout;
    QVBoxLayout *body_add_layout = new QVBoxLayout;
    
    gloabal_layout->addWidget (canvas_box);
    gloabal_layout->addWidget (this->update_initor);

    body_add_layout->addWidget (this->mass_input);
    body_add_layout->addWidget (this->pos_x_input);
    body_add_layout->addWidget (this->pos_y_input);
    body_add_layout->addWidget (this->vel_x_input);
    body_add_layout->addWidget (this->vel_y_input);
    body_add_layout->addWidget (add_body_button);
    body_add_layout->addStretch (1);
    this->body_add_widget->setLayout (body_add_layout);

    gloabal_layout->addWidget (this->body_add_widget);
    gloabal_layout->addStretch (1);
    this->setLayout (gloabal_layout);

    QTimer *update_state_timer = new QTimer(this);
    QTimer *redraw_timer = new QTimer(this);

    QShortcut *up = new QShortcut (QKeySequence (Qt::Key_Up), this);
    QShortcut *down = new QShortcut (QKeySequence (Qt::Key_Down), this);
    QShortcut *left = new QShortcut (QKeySequence (Qt::Key_Left), this);
    QShortcut *right = new QShortcut (QKeySequence (Qt::Key_Right), this);

    connect (update_state_timer, SIGNAL(timeout ()), this, SLOT (update_universe ()));
    connect(redraw_timer, SIGNAL(timeout()), this, SLOT(update_canvas()));
    connect(add_body_button, SIGNAL(clicked ()), this, SLOT (addBody ()));

    connect (up, SIGNAL (activated ()), this, SLOT (move_up ()));
    connect (down, SIGNAL (activated ()), this, SLOT (move_down ()));
    connect (left, SIGNAL (activated ()), this, SLOT (move_left ()));
    connect (right, SIGNAL (activated ()), this, SLOT (move_right ()));

    update_state_timer->start(10);
    redraw_timer->start(10);
}

interface::~interface ()
{
}

void interface::move (double x, double y)
{
    vector2d offset (x, y);
    this->u.move_all (offset);
}

void interface::update_universe ()
{
    if (this->update_initor->checkState () == Qt::Checked)
    {
        this->u.update (this->time);
    }
}

void interface::update_canvas()
{
    std::vector<vector2d> positions;
    for (auto body_ptr : this->u.getBodies ())
    {
        positions.push_back (body_ptr->getPosition ());
    }
    this->canvas->draw_points(positions);
    positions.erase (positions.begin (), positions.end ());
}

void interface::addBody ()
{
    double mass, pos_x, pos_y, vel_x, vel_y;
    mass = this->mass_input->text ().toDouble ();
    pos_x = this->pos_x_input->text ().toDouble ();
    pos_y = this->pos_y_input->text ().toDouble ();
    vel_x = this->vel_x_input->text ().toDouble ();
    vel_y = this->vel_y_input->text ().toDouble ();

    vector2d pos (pos_x, pos_y), vel (vel_x, vel_y);
    body* b = new body (mass);
    b->setPosition (pos);
    b->setVelocity (vel);
    this->u.addBody (b);

    this->mass_input->setText ("Mass");
    this->pos_x_input->setText ("X position");
    this->pos_y_input->setText ("Y position");
    this->vel_x_input->setText ("X velocity");
    this->vel_y_input->setText ("Y velocity");

}

void interface::run (double time)
{
    this->show ();
    this->time = time;
}

void interface::move_up ()
{
    this->u.move_all (vector2d (0, this->speed));
    this->canvas->redraw ();
}
void interface::move_down ()
{
    this->u.move_all (vector2d (0, -(this->speed)));
    this->canvas->redraw ();
}
void interface::move_left ()
{
    this->u.move_all (vector2d (this->speed, 0));
    this->canvas->redraw ();
}
void interface::move_right ()
{
    this->u.move_all (vector2d (-(this->speed), 0));
    this->canvas->redraw ();
}
