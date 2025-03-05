#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPixmap>
#include <QTimer>
#include <qalgorithms.h>
#include <qrandom.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , matchedPairs(0)
    , attempts(0)
{
    ui->setupUi(this);

    initializeGame();
//  QStringList icons = {":/icons/ikonlarr/icon_1.png", ":/icons/ikonlarr/icon_2.png", ":/icons/ikonlarr/icon_3.png", ":/icons/ikonlarr/icon_4.png", ":/icons/ikonlarr/icon_5.png"};
    this->setStyleSheet("background-image: url(:/icons/ikonlarr/icon_7.png);"
                        "background-position: center;"
                        "background-repeat: no-repeat;"
                        "background-size: 100% 100%;");
}
MainWindow::~MainWindow()
{
    delete ui;
    //
}

void MainWindow::initializeGame()
{
  QStringList icons = {":/icons/ikonlarr/icon_1.png", ":/icons/ikonlarr/icon_2.png", ":/icons/ikonlarr/icon_3.png", ":/icons/ikonlarr/icon_4.png", ":/icons/ikonlarr/icon_5.png"};
    icons << icons; // Her resimden iki tane olacak

    std::shuffle(icons.begin(), icons.end(), std::default_random_engine(QTime::currentTime().msec()));

    buttons = {ui->icon1, ui->icon2, ui->icon3, ui->icon4, ui->icon5, ui->icon6, ui->icon7, ui->icon8, ui->icon9, ui->icon10};

    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i]->setProperty("iconPath", icons[i]);
        buttons[i]->setIconSize(buttons[i]->size());
        buttons[i]->setStyleSheet("border-image: url(:/icons/ikonlarr/icon_6.png); border: none;");
        connect(buttons[i], &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    }

    firstButton = nullptr;
    matchedPairs = 0;
    attempts = 0;
}

void MainWindow::handleButtonClick()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton || clickedButton == firstButton) return;

    QString iconPath = clickedButton->property("iconPath").toString();
    clickedButton->setIcon(QPixmap(iconPath).scaled(clickedButton->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    if (!firstButton) {
        firstButton = clickedButton;
    } else {
        attempts++;
        if (firstButton->property("iconPath") == clickedButton->property("iconPath")) {
            matchedPairs++;
            firstButton = nullptr;
            checkGameEnd();
        } else {
            QTimer::singleShot(1000, [=]() {
                firstButton->setIcon(QIcon());
                clickedButton->setIcon(QIcon());
                firstButton = nullptr;
            });
        }
    }
}
void MainWindow::checkGameEnd()
{
    if (matchedPairs == buttons.size() / 2) {
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Oyun Bitti",
                                                                     QString("Tebrikler! Oyun bitti.\nDeneme Sayısı: %1\n").arg(attempts));

    }

}
