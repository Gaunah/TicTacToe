#include "configurationdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QMessageBox>

void MainWindow::startNewGame()
{
    ConfigurationDialog dlg(this);
    if (dlg.exec() == QDialog::Rejected) return; //do nothing if dialog rejected

    ui->player1->setText(dlg.player1Name());
    ui->player2->setText(dlg.player2Name());
    ui->gameBoard->initNewGame();
    ui->gameBoard->setEnabled(true);

    updateNameLabels();
}

void MainWindow::updateNameLabels()
{
    QFont font = ui->player1->font();
    font.setBold(ui->gameBoard->currentPlayer() == Player1);
    ui->player1->setFont(font);

    font.setBold(ui->gameBoard->currentPlayer() == Player2);
    ui->player2->setFont(font);
}

void MainWindow::handleGameOver(Player winner)
{
    ui->gameBoard->setEnabled(false);
    QString msg;
    if (winner == Draw) {
        msg = "Game ended with a draw.";
    } else {
        msg = QString("%1 wins!").arg(winner == Player1 ? ui->player1->text() : ui->player2->text());
    }
    QMessageBox::information(this, "Info", msg);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect pos = frameGeometry();
    pos.moveCenter(QDesktopWidget().availableGeometry().center());
    move(pos.topLeft());

    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->gameBoard, SIGNAL(currentPlayerChanged(Player)), this, SLOT(updateNameLabels()));
    connect(ui->gameBoard, SIGNAL(gameOver(Player)), this, SLOT(handleGameOver(Player)));

    ui->gameBoard->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
