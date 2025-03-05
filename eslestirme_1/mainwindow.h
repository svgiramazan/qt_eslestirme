#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QtAlgorithms>
#include <qrandom.h>

#include <QMessageBox>

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
    QList<QPushButton*> buttons;
    QPushButton *firstButton;
    int matchedPairs;
    int attempts;

    void initializeGame();
    void handleButtonClick();
    void checkGameEnd();
};
#endif // MAINWINDOW_H
