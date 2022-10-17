#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    login = "login";
    password = "password";
    anim = nullptr;

    ui->setupUi(this);
    ui->login->setPlaceholderText("login");
    ui->login->setAlignment(Qt::AlignCenter);
    ui->password->setPlaceholderText("password");
    ui->password->setAlignment(Qt::AlignCenter);
    ui->password->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->ok->setFocus();

    connect(ui->ok, SIGNAL(clicked()), this, SLOT(push_OK()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete anim;
}

QSequentialAnimationGroup *MainWindow::controlText(QLineEdit *ln, const QString &key)
{
    if(ln->text() == key) {
        ln->setStyleSheet("border: 2px solid green;");
        return nullptr;
    }
    ln->setStyleSheet("border: 2px solid red;");
    QSequentialAnimationGroup * group = new QSequentialAnimationGroup();
    QPropertyAnimation * temp;
    QRect r1 = ln->geometry();
    QRect r2 = ln->geometry();

    temp = new QPropertyAnimation(ln, "geometry");

    r2.moveLeft(r2.x() - 5);
    temp->setDuration(50);
    temp->setStartValue(r1);
    temp->setEndValue(r2);
    group->addAnimation(temp);

    temp = new QPropertyAnimation(ln, "geometry");
    r1.moveLeft(r1.x() + 5);
    temp->setDuration(100);
    temp->setStartValue(r2);
    temp->setEndValue(r1);
    group->addAnimation(temp);

    temp = new QPropertyAnimation(ln, "geometry");
    temp->setDuration(50);
    temp->setStartValue(r1);
    temp->setEndValue(ln->geometry());
    group->addAnimation(temp);

    return group;
}

void MainWindow::push_OK()
{
    if(anim != nullptr && anim->state() == QAbstractAnimation::Running)
        return;
    delete anim;
    anim = new QParallelAnimationGroup();
    QSequentialAnimationGroup * temp;
    temp = controlText(ui->login, login);
    if(temp != nullptr)
        anim->addAnimation(temp);
    temp = controlText(ui->password, password);
    if(temp != nullptr)
        anim->addAnimation(temp);
    if(anim->animationCount() != 0)
        anim->start();
}

