#include "interface.hpp"
#include <QFileDialog>
#include <vector>

interface::interface (universe vers, int w, int h, double s)
{
    u = vers;
    speed = s;

    QGroupBox *canvas_box = new QGroupBox ("Universe");
    canvas_box->setMinimumSize (w, h);

    QVBoxLayout *canvas_layout = new QVBoxLayout;

    bar = new QMenuBar;
    QMenu* file_menu = bar->addMenu("File");
    QAction* save_act = file_menu->addAction("Save");
    QAction* load_act = file_menu->addAction("Load");
    connect(save_act, SIGNAL(triggered()), this, SLOT(save()));
    connect(load_act, SIGNAL(triggered()), this, SLOT(load()));

    canvas = new Canvas;
    canvas->setMinimumSize (w, h);
    canvas_layout->addWidget(canvas);
    canvas_box->setLayout(canvas_layout);

    body_add_widget = new QGroupBox ("Add bodies");
    update_initor = new QCheckBox ("Update");
    mass_input = new QLineEdit ("Mass");
    pos_x_input = new QLineEdit ("X position");
    pos_y_input = new QLineEdit ("Y position");
    vel_x_input = new QLineEdit ("X velocity");
    vel_y_input = new QLineEdit ("Y velocity");

    QPushButton *add_body_button = new QPushButton ("Add body");

    QVBoxLayout *gloabal_layout = new QVBoxLayout;
    QVBoxLayout *body_add_layout = new QVBoxLayout;
    
    gloabal_layout->setMargin(5);
    gloabal_layout->addWidget(bar);
    gloabal_layout->addWidget (canvas_box);
    gloabal_layout->addWidget (update_initor);

    body_add_layout->addWidget (mass_input);
    body_add_layout->addWidget (pos_x_input);
    body_add_layout->addWidget (pos_y_input);
    body_add_layout->addWidget (vel_x_input);
    body_add_layout->addWidget (vel_y_input);
    body_add_layout->addWidget (add_body_button);
    body_add_layout->addStretch (1);
    body_add_widget->setLayout (body_add_layout);

    gloabal_layout->addWidget (body_add_widget);
    gloabal_layout->addStretch (1);
    setLayout (gloabal_layout);

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
    u.move_all (offset);
}

void interface::update_universe ()
{
    if (update_initor->checkState () == Qt::Checked)
    {
        u.update (time);
    }
}

void interface::update_canvas()
{
    std::vector<vector2d> positions;
    for (auto body_ptr : u.getBodies ())
        positions.push_back (body_ptr.getPosition ());
    canvas->draw_points(positions);
    positions.erase (positions.begin (), positions.end ());
}

void interface::addBody ()
{
    double mass, pos_x, pos_y, vel_x, vel_y;
    mass = mass_input->text ().toDouble ();
    pos_x = pos_x_input->text ().toDouble ();
    pos_y = pos_y_input->text ().toDouble ();
    vel_x = vel_x_input->text ().toDouble ();
    vel_y = vel_y_input->text ().toDouble ();

    vector2d pos (pos_x, pos_y), vel (vel_x, vel_y);
    body b(mass);
    b.setPosition(pos);
    b.setVelocity(vel);
    u.addBody(b);

    mass_input->setText ("Mass");
    pos_x_input->setText ("X position");
    pos_y_input->setText ("Y position");
    vel_x_input->setText ("X velocity");
    vel_y_input->setText ("Y velocity");

}

void interface::run (double time_)
{
    show ();
    time = time_;
}

void interface::move_up ()
{
    u.move_all (vector2d (0, speed));
    canvas->redraw ();
}
void interface::move_down ()
{
    u.move_all (vector2d (0, -(speed)));
    canvas->redraw ();
}
void interface::move_left ()
{
    u.move_all (vector2d (speed, 0));
    canvas->redraw ();
}
void interface::move_right ()
{
    u.move_all (vector2d (-(speed), 0));
    canvas->redraw ();
}

void interface::save()
{
    std::cerr << "Save" << "\n";
    std::string filename = QFileDialog::getSaveFileName(this,
            tr("Save universe state"), "", tr("Emulator universe (*.univ)")).toStdString();
    u.save(filename);
}

void interface::load()
{
    std::cerr << "Load" << "\n";
    std::string filename = QFileDialog::getOpenFileName(this,
            tr("Open universe state"), "", tr("Emulator universe (*.univ)")).toStdString();
    u.clean();
    u.load(filename);
}
