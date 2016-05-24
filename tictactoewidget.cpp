#include "tictactoewidget.h"

#include <QSignalMapper>
#include <QDebug>

/*!
 * \brief TicTacToeWidget::handleButtonClick sets "X" or "O" and checkWinCondition
 * \param index of button
 */
void TicTacToeWidget::handleButtonClick(int index)
{
    if (index < 0 || index >= board.size()) return; //out of bound check
    QPushButton *button = board.at(index);

    if (button->text() != " ") return; //invalid move
    button->setText(currentPlayer() == Player1 ? "X" : "O");
    Player winner = checkWinCondition(index / 3, index % 3);
    if (winner == Invalid) {
        setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
        return; //switch players
    } else {
        emit gameOver(winner);
        qDebug() << winner;
    }
}

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
{
    setupBoard();
}

TicTacToeWidget::~TicTacToeWidget()
{
}

/*!
 * \brief initNewGame clears the board
 */
void TicTacToeWidget::initNewGame()
{
    for (int i = 0; i < 9; ++i) {
        board.at(i)->setText(" ");
    }
}

void TicTacToeWidget::setupBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    QSignalMapper *mapper = new QSignalMapper(this);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            button->setText(" ");
            gridLayout->addWidget(button, row, col);
            board.append(button);
            mapper->setMapping(button, board.count() - 1);
            connect(button, SIGNAL(clicked(bool)), mapper, SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
    setLayout(gridLayout);
}

Player TicTacToeWidget::checkWinCondition(int row, int col)
{
    QString symbol = currentPlayer() == Player1 ? "X" : "O";
    bool win = true;
    for (int i = 0; i < 3; ++i) {
        win = win && board.at(i + row * 3)->text() == symbol; //horizontal
    }
    if (win) return currentPlayer();

    win = true;
    for (int i = 0; i < 9; i += 3) {
        win = win && board.at(i + col)->text() == symbol; //vertical
    }
    if (win) return currentPlayer();

    win = true;
    for (int i = 0; i < 9; i += 4) {
        win = win && board.at(i)->text() == symbol; //diagonal 0 4 8
    }
    if (win) return currentPlayer();

    win = true;
    for (int i = 2; i < 7; i += 2) {
        win = win && board.at(i)->text() == symbol; //diagonal 2 4 6
    }
    if (win) return currentPlayer();

    bool openSpots = false;
    for (int i = 0; i < 9; ++i) {
        openSpots = openSpots || board.at(i)->text() == " ";
    }

    return openSpots ? Invalid : Draw;
}
