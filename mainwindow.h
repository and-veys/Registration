#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QParallelAnimationGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString password;
    QString login;
    QParallelAnimationGroup * anim;
    QSequentialAnimationGroup * controlText(QLineEdit * ln, const QString & key);

private slots:
    void push_OK();
};
#endif // MAINWINDOW_H
