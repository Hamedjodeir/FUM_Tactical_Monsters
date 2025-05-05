#ifndef GAMEPLAYPAGE_H
#define GAMEPLAYPAGE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <vector>
#include <memory>
#include "agent.h"
#include <QVBoxLayout>

namespace Ui {
class GamePlayPage;
}

struct Cell {
    QGraphicsPolygonItem* tile;
    QGraphicsPolygonItem* agent;
    int row, col;
    char terrainType;
    std::shared_ptr<Agent> agentPtr;
};

class GamePlayPage : public QWidget
{
    Q_OBJECT

public:
    GamePlayPage(const QString& player1, const QString& player2, QWidget *parent = nullptr);
    ~GamePlayPage();

    void colorizeCells(const std::vector<std::tuple<int, int, char, int, int>>& cellsToColor);

signals:
    void agentSelected(std::shared_ptr<Agent> agent);
    void turnChanged(int team);
    void allAgentsPlaced();
    void agentMoved(std::shared_ptr<Agent> agent, int fromRow, int fromCol, int toRow, int toCol);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void handleAgentSelection(std::shared_ptr<Agent> agent);
    void handleCellClick(int row, int col);

private:
    Ui::GamePlayPage *ui;
    QGraphicsScene* scene;
    std::vector<std::vector<Cell>> gridCells;
    std::vector<std::shared_ptr<Agent>> team1Agents;
    std::vector<std::shared_ptr<Agent>> team2Agents;
    int currentTurn;
    std::shared_ptr<Agent> selectedAgent;
    QString player1Name;
    QString player2Name;
    bool placementPhase;
    bool agentSelectedForMovement;

    QPolygonF createHexagon(qreal x, qreal y, qreal size);
    void setupSidePanels();
    void createAgentWidget(QVBoxLayout* layout, std::shared_ptr<Agent> agent);
    void updateTurnLabel();
    void setupAgentSelection();
    void highlightAgent(std::shared_ptr<Agent> agent, bool highlight);
    void clearSelection();
    void setupCellClickHandling();
    void placeAgentOnBoard(std::shared_ptr<Agent> agent, int row, int col);
    void removeAgentFromPanel(std::shared_ptr<Agent> agent);
    void checkAllAgentsPlaced();
    bool isValidMove(std::shared_ptr<Agent> agent, int fromRow, int fromCol, int toRow, int toCol);
    void moveAgent(std::shared_ptr<Agent> agent, int fromRow, int fromCol, int toRow, int toCol);
    void highlightMovementOptions(int row, int col);
    void clearMovementHighlights();
    std::vector<std::pair<int, int>> getAdjacentCells(int row, int col);
};

#endif // GAMEPLAYPAGE_H
