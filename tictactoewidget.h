#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

enum Player {
    Invalid,
    Player1,
    Player2,
    Draw
};

class TicTacToeWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Player)
    Q_PROPERTY(Player currentPlayer READ currentPlayer WRITE setCurrentPlayer
               NOTIFY currentPlayerChanged)

signals:
    void currentPlayerChanged(Player);
    void gameOver(Player);

public slots:
    /*!
    * \brief TicTacToeWidget::handleButtonClick sets "X" or "O" and checkWinCondition
    * \param index of button
    */
    void handleButtonClick(int index);

public:
    explicit TicTacToeWidget(QWidget *parent = 0);
    ~TicTacToeWidget();

    /*!
     * \brief initNewGame clears the board
     */
    void initNewGame();
    Player currentPlayer() const;
    void setCurrentPlayer(const Player &currentPlayer);

private:
    Player m_currentPlayer;
    QList<QPushButton *> board;
    void setupBoard();
    Player checkWinCondition(int row, int col);
};

#endif // TICTACTOEWIDGET_H
