#include "gameplaypage.h"
#include "ui_gameplaypage.h"
#include "parser.h"
#include <QtMath>
#include <QBrush>
#include <QPen>
#include <QApplication>
#include <QScreen>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include "agentbuild.h"

GamePlayPage::GamePlayPage(const QString& player1, const QString& player2, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GamePlayPage)
    , currentTurn(1)
    , player1Name(player1)
    , player2Name(player2)
    , selectedAgent(nullptr)
    , placementPhase(true)
{
    ui->setupUi(this);
    setFixedSize(1350, 700);

    // Center main
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    move(x, 0);

    // top
    QWidget* topBarContainer = new QWidget();
    QHBoxLayout* topBarLayout = new QHBoxLayout(topBarContainer);
    topBarLayout->setContentsMargins(0, 0, 0, 0);
    topBarLayout->setSpacing(0);

    // Player 1 label
    QLabel* player1Label = new QLabel(player1);
    player1Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    player1Label->setStyleSheet("font-weight: bold; font-size: 12px;");
    topBarLayout->addWidget(player1Label);

    topBarLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Turn
    QLabel* turnLabel = new QLabel("TURN: " + player1);
    turnLabel->setObjectName("turnLabel");
    turnLabel->setAlignment(Qt::AlignCenter);
    turnLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; color: #8B4513; }");
    topBarLayout->addWidget(turnLabel);

    topBarLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Player 2 label
    QLabel* player2Label = new QLabel(player2);
    player2Label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    player2Label->setStyleSheet("font-weight: bold; font-size: 12px;");
    topBarLayout->addWidget(player2Label);

    QLayoutItem* child;
    while ((child = ui->horizontalLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    ui->horizontalLayout->addWidget(topBarContainer);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    const int rows = 5;
    const int cols = 9;
    const double hexSize = 40.0;
    const double w = 2 * hexSize;
    const double h = sqrt(3) * hexSize;

    gridCells.resize(rows, std::vector<Cell>(cols));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            double x = col * (3.0 / 4.0 * w);
            double y = row * h;
            if (col % 2 == 1) y += h / 2.0;

            QPolygonF hex = createHexagon(x, y, hexSize);
            QGraphicsPolygonItem* hexItem = scene->addPolygon(hex);
            hexItem->setBrush(Qt::lightGray);
            hexItem->setPen(QPen(Qt::black));

            gridCells[row][col] = { hexItem, nullptr, row, col, ' ', nullptr };
        }
    }

    // make agents
#include "agentBuild.h"   // at top of file

    // build all agents
    auto allAgents = AgentBuild::createAllAgents();

    // Split them between panels (or later allow players to draft/pick)
    for (int i = 0; i < allAgents.size(); ++i) {
        if (i % 2 == 0) {
            auto a = std::make_shared<Agent>(*allAgents[i]); // copy
            a->setTeam(Agent::Team1);
            team1Agents.push_back(a);
        } else {
            auto a = std::make_shared<Agent>(*allAgents[i]); // copy
            a->setTeam(Agent::Team2);
            team2Agents.push_back(a);
        }
    }


    Parser parser(6);
    auto cellData = parser.parse();
    colorizeCells(cellData);

    setupSidePanels();
    updateTurnLabel();
    setupAgentSelection();
    setupCellClickHandling();
}

GamePlayPage::~GamePlayPage()
{
    delete ui;
}

void GamePlayPage::updateTurnLabel() {
    QLabel* turnLabel = findChild<QLabel*>("turnLabel");
    if (turnLabel) {
        if (placementPhase) {
            turnLabel->setText("PLACEMENT: " + QString(currentTurn == 1 ? player1Name : player2Name) + "'s turn");
        } else {
            turnLabel->setText("BATTLE: " + QString(currentTurn == 1 ? player1Name : player2Name) + "'s turn");
        }
    }
}

void GamePlayPage::setupSidePanels() {
    QVBoxLayout* leftLayout = new QVBoxLayout(ui->leftPanel);
    leftLayout->setContentsMargins(5, 5, 5, 5);
    leftLayout->setSpacing(5);

    QVBoxLayout* rightLayout = new QVBoxLayout(ui->rightPanel);
    rightLayout->setContentsMargins(5, 5, 5, 5);
    rightLayout->setSpacing(5);

    for (const auto& agent : team1Agents) {
        createAgentWidget(leftLayout, agent);
    }

    for (const auto& agent : team2Agents) {
        createAgentWidget(rightLayout, agent);
    }
}

void GamePlayPage::createAgentWidget(QVBoxLayout* layout, std::shared_ptr<Agent> agent) {
    QFrame* agentFrame = new QFrame();
    agentFrame->setStyleSheet("QFrame { background-color: #f5f5dc; border: 2px solid #d2b48c; border-radius: 5px; }"
                              "QFrame:hover { background-color: #e6d5b8; border: 2px solid #b8860b; }");
    agentFrame->setFixedHeight(100);
    agentFrame->setProperty("agentId", agent->getId());

    QHBoxLayout* agentLayout = new QHBoxLayout(agentFrame);
    agentLayout->setContentsMargins(5, 5, 5, 5);

    // --- IMAGE ---
    QLabel* imageLabel = new QLabel();
    QPixmap pix(agent->getImagePath());
    if (!pix.isNull()) {
        imageLabel->setPixmap(pix.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("No Img");
        imageLabel->setAlignment(Qt::AlignCenter);
    }
    agentLayout->addWidget(imageLabel);

    // --- INFO ---
    QLabel* agentInfo = new QLabel();
    agentInfo->setText(QString("%1\nHP: %2  DMG: %3")
                           .arg(agent->getName())
                           .arg(agent->getHp())
                           .arg(agent->getDmg()));
    agentInfo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    agentLayout->addWidget(agentInfo);

    layout->addWidget(agentFrame);
}

QPolygonF GamePlayPage::createHexagon(qreal x, qreal y, qreal size) {
    QPolygonF hex;
    for (int i = 0; i < 6; ++i) {
        double angle_rad = M_PI / 180 * (60 * i);
        hex << QPointF(x + size * cos(angle_rad),
                       y + size * sin(angle_rad));
    }
    return hex;
}

void GamePlayPage::colorizeCells(const std::vector<std::tuple<int, int, char, int, int>>& cellsToColor) {
    const double hexSize = 40.0;
    const double innerSize = 20.0;

    for (const auto& cellData : cellsToColor) {
        int row, col, agentType, team;
        char terrain;
        std::tie(row, col, terrain, agentType, team) = cellData;

        if (row >= gridCells.size() || col >= gridCells[0].size()) continue;

        Cell& cell = gridCells[row][col];

        QColor terrainColor = Qt::lightGray;
        switch (terrain) {
        case '1': terrainColor = Qt::yellow; break;
        case '2': terrainColor = Qt::darkMagenta; break;
        case '~': terrainColor = Qt::blue; break;
        case '#': terrainColor = QColor(139, 69, 19); break;
        }
        cell.tile->setBrush(terrainColor);
        cell.terrainType = terrain;

        if (cell.agent) {
            scene->removeItem(cell.agent);
            delete cell.agent;
            cell.agent = nullptr;
            cell.agentPtr.reset();
        }

        if (agentType > 0) {
            double x = cell.tile->boundingRect().center().x() + cell.tile->pos().x();
            double y = cell.tile->boundingRect().center().y() + cell.tile->pos().y();
            QPolygonF agentHex = createHexagon(x, y, innerSize);

            QColor agentColor = Qt::black;
            if (agentType == 2) agentColor = Qt::red;

            QColor borderColor = (team == 1) ? QColor(255, 140, 0) : Qt::magenta;
            QPen borderPen(borderColor, 4);

            QGraphicsPolygonItem* agentItem = scene->addPolygon(agentHex, borderPen, QBrush(agentColor));
            cell.agent = agentItem;


            auto agent = std::make_shared<Agent>(0,
                                                 static_cast<Agent::Type>(agentType),
                                                 static_cast<Agent::Team>(team));
            agent->setPosition(row, col);
            cell.agentPtr = agent;
        }
    }
}

void GamePlayPage::setupAgentSelection() {
    //  agent  click
    for (int i = 0; i < ui->leftPanel->layout()->count(); ++i) {
        QFrame* frame = qobject_cast<QFrame*>(ui->leftPanel->layout()->itemAt(i)->widget());
        if (frame) {
            frame->installEventFilter(this);
        }
    }

    for (int i = 0; i < ui->rightPanel->layout()->count(); ++i) {
        QFrame* frame = qobject_cast<QFrame*>(ui->rightPanel->layout()->itemAt(i)->widget());
        if (frame) {
            frame->installEventFilter(this);
        }
    }
}

bool GamePlayPage::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress) {
        for (int i = 0; i < ui->leftPanel->layout()->count(); ++i) {
            if (watched == ui->leftPanel->layout()->itemAt(i)->widget() && currentTurn == 1) {
                handleAgentSelection(team1Agents[i]);
                return true;
            }
        }

        for (int i = 0; i < ui->rightPanel->layout()->count(); ++i) {
            if (watched == ui->rightPanel->layout()->itemAt(i)->widget() && currentTurn == 2) {
                handleAgentSelection(team2Agents[i]);
                return true;
            }
        }

        //  click on cell
        if (watched == ui->graphicsView->viewport()) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());

            //  which cell click
            for (int row = 0; row < gridCells.size(); ++row) {
                for (int col = 0; col < gridCells[row].size(); ++col) {
                    if (gridCells[row][col].tile->contains(
                            gridCells[row][col].tile->mapFromScene(scenePos))) {
                        handleCellClick(row, col);
                        return true;
                    }
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void GamePlayPage::handleAgentSelection(std::shared_ptr<Agent> agent) {
    if (!placementPhase) return;

    if ((currentTurn == 1 && agent->getTeam() != Agent::Team1) ||
        (currentTurn == 2 && agent->getTeam() != Agent::Team2)) {
        return;
    }

    clearSelection();

    selectedAgent = agent;
    highlightAgent(agent, true);

    qDebug() << "Selected agent:" << agent->getName() << "from team" << agent->getTeam();
}

void GamePlayPage::highlightAgent(std::shared_ptr<Agent> agent, bool highlight) {
    QVBoxLayout* panelLayout = (agent->getTeam() == Agent::Team1) ?
                                   qobject_cast<QVBoxLayout*>(ui->leftPanel->layout()) :
                                   qobject_cast<QVBoxLayout*>(ui->rightPanel->layout());

    for (int i = 0; i < panelLayout->count(); ++i) {
        QFrame* frame = qobject_cast<QFrame*>(panelLayout->itemAt(i)->widget());
        if (frame && frame->property("agentId").toInt() == agent->getId()) {
            frame->setStyleSheet(highlight ?
                                     "QFrame {"
                                     "   background-color: #e6d5b8;"
                                     "   border: 3px solid #b8860b;"
                                     "   border-radius: 5px;"
                                     "}" :
                                     "QFrame {"
                                     "   background-color: #f5f5dc;"
                                     "   border: 2px solid #d2b48c;"
                                     "   border-radius: 5px;"
                                     "}"
                                     "QFrame:hover {"
                                     "   background-color: #e6d5b8;"
                                     "   border: 2px solid #b8860b;"
                                     "}");
            break;
        }
    }

    if (agent->getPosition().first != -1) {
        int row = agent->getPosition().first;
        int col = agent->getPosition().second;
        if (row < gridCells.size() && col < gridCells[0].size()) {
            QPen pen = highlight ? QPen(Qt::yellow, 4) :
                           (agent->getTeam() == Agent::Team1 ? QPen(QColor(255, 140, 0), 2) : QPen(Qt::magenta, 2));
            gridCells[row][col].agent->setPen(pen);
        }
    }
}

void GamePlayPage::clearSelection() {
    if (selectedAgent) {
        highlightAgent(selectedAgent, false);
        selectedAgent.reset();
    }
}

void GamePlayPage::setupCellClickHandling() {

    ui->graphicsView->viewport()->installEventFilter(this);
}


void GamePlayPage::handleCellClick(int row, int col) {
    if (row < 0 || row >= gridCells.size() || col < 0 || col >= gridCells[0].size()) {
        return;
    }

    if (placementPhase) {
        if (!selectedAgent) return;

        Cell& cell = gridCells[row][col];
        if ((currentTurn == 1 && cell.terrainType != '1') ||
            (currentTurn == 2 && cell.terrainType != '2')) {
            return;
        }
        if (cell.agentPtr) return;

        placeAgentOnBoard(selectedAgent, row, col);
    } else {
        Cell& cell = gridCells[row][col];

        if (!agentSelectedForMovement) {
            if (cell.agentPtr && cell.agentPtr->getTeam() == currentTurn) {
                selectedAgent = cell.agentPtr;
                agentSelectedForMovement = true;
                highlightAgent(selectedAgent, true);
                highlightMovementOptions(row, col);
            }
        }
        else {
            if (selectedAgent && isValidMove(selectedAgent,
                                             selectedAgent->getPosition().first,
                                             selectedAgent->getPosition().second,
                                             row, col)) {

                moveAgent(selectedAgent,
                          selectedAgent->getPosition().first,
                          selectedAgent->getPosition().second,
                          row, col);

                currentTurn = (currentTurn == 1) ? 2 : 1;
                updateTurnLabel();
            }
            clearMovementHighlights();
            clearSelection();
            agentSelectedForMovement = false;
        }
    }
}

bool GamePlayPage::isValidMove(std::shared_ptr<Agent> agent, int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow == toRow && fromCol == toCol) return false;

    if (gridCells[toRow][toCol].agentPtr) return false;

    if (gridCells[toRow][toCol].terrainType == '#') return false;

    if (gridCells[toRow][toCol].terrainType == '~') {
        if (agent->getId() != 2 && agent->getId() != 4) {
            return false;
        }
    }

    auto adjacent = getAdjacentCells(fromRow, fromCol);
    bool isAdjacent = false;
    for (const auto& cell : adjacent) {
        if (cell.first == toRow && cell.second == toCol) {
            isAdjacent = true;
            break;
        }
    }
    if (!isAdjacent) return false;

    return true;
}

void GamePlayPage::moveAgent(std::shared_ptr<Agent> agent, int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidMove(agent, fromRow, fromCol, toRow, toCol)) return;

    Cell& fromCell = gridCells[fromRow][fromCol];
    scene->removeItem(fromCell.agent);
    delete fromCell.agent;
    fromCell.agent = nullptr;
    fromCell.agentPtr.reset();

    // Add agent to cell
    Cell& toCell = gridCells[toRow][toCol];
    const double innerSize = 20.0;
    double x = toCell.tile->boundingRect().center().x() + toCell.tile->pos().x();
    double y = toCell.tile->boundingRect().center().y() + toCell.tile->pos().y();
    QPolygonF agentHex = createHexagon(x, y, innerSize);

    QColor agentColor = (agent->getType() == Agent::BlackAgent) ? Qt::black : Qt::red;
    QColor borderColor = (agent->getTeam() == Agent::Team1) ? QColor(255, 140, 0) : Qt::magenta;
    QPen borderPen(borderColor, 4);

    QGraphicsPolygonItem* agentItem = scene->addPolygon(agentHex, borderPen, QBrush(agentColor));
    toCell.agent = agentItem;
    toCell.agentPtr = agent;
    agent->setPosition(toRow, toCol);

    emit agentMoved(agent, fromRow, fromCol, toRow, toCol);
}

void GamePlayPage::highlightMovementOptions(int row, int col) {
    auto adjacent = getAdjacentCells(row, col);
    for (const auto& cell : adjacent) {
        int r = cell.first;
        int c = cell.second;
        if (r >= 0 && r < gridCells.size() && c >= 0 && c < gridCells[0].size()) {
            if (isValidMove(selectedAgent, row, col, r, c)) {
                gridCells[r][c].tile->setPen(QPen(Qt::green, 3));
            }
        }
    }
}

void GamePlayPage::clearMovementHighlights() {
    for (auto& row : gridCells) {
        for (auto& cell : row) {
            if (cell.terrainType == '1') {
                cell.tile->setBrush(Qt::yellow);
                cell.tile->setPen(QPen(Qt::black, 1)); // Set border to black
            } else if (cell.terrainType == '2') {
                cell.tile->setBrush(Qt::darkMagenta);
                cell.tile->setPen(QPen(Qt::black, 1)); // Set border to black
            } else {
                cell.tile->setPen(QPen(Qt::black, 1));
            }
        }
    }
}

std::vector<std::pair<int, int>> GamePlayPage::getAdjacentCells(int row, int col) {
    std::vector<std::pair<int, int>> adjacent;

    if (col % 2 == 0) {
        adjacent = {
            {row-1, col-1}, {row-1, col}, {row-1, col+1},
            {row, col-1},                  {row, col+1},
            {row+1, col}
        };
    } else {
        adjacent = {
            {row-1, col},
            {row, col-1},                  {row, col+1},
            {row+1, col-1}, {row+1, col}, {row+1, col+1}
        };
    }

    adjacent.erase(std::remove_if(adjacent.begin(), adjacent.end(),
                                  [this](const std::pair<int, int>& pos) {
                                      return pos.first < 0 || pos.first >= gridCells.size() ||
                                             pos.second < 0 || pos.second >= gridCells[0].size();
                                  }), adjacent.end());

    return adjacent;
}


void GamePlayPage::placeAgentOnBoard(std::shared_ptr<Agent> agent, int row, int col) {
    const double innerSize = 20.0;
    Cell& cell = gridCells[row][col];

    if (cell.agent) {
        scene->removeItem(cell.agent);
        delete cell.agent;
        cell.agent = nullptr;
    }

    double x = cell.tile->boundingRect().center().x() + cell.tile->pos().x();
    double y = cell.tile->boundingRect().center().y() + cell.tile->pos().y();
    QPolygonF agentHex = createHexagon(x, y, innerSize);

    QColor agentColor = (agent->getType() == Agent::BlackAgent) ? Qt::black : Qt::red;
    QColor borderColor = (agent->getTeam() == Agent::Team1) ? QColor(255, 140, 0) : Qt::magenta;
    QPen borderPen(borderColor, 4);

    QGraphicsPolygonItem* agentItem = scene->addPolygon(agentHex, borderPen, QBrush(agentColor));
    cell.agent = agentItem;
    cell.agentPtr = agent;
    agent->setPosition(row, col);

    removeAgentFromPanel(agent);

    clearSelection();
    currentTurn = (currentTurn == 1) ? 2 : 1;
    updateTurnLabel();

    checkAllAgentsPlaced();
}

void GamePlayPage::removeAgentFromPanel(std::shared_ptr<Agent> agent) {
    QVBoxLayout* panelLayout = (agent->getTeam() == Agent::Team1) ?
                                   qobject_cast<QVBoxLayout*>(ui->leftPanel->layout()) :
                                   qobject_cast<QVBoxLayout*>(ui->rightPanel->layout());

    for (int i = 0; i < panelLayout->count(); ++i) {
        QFrame* frame = qobject_cast<QFrame*>(panelLayout->itemAt(i)->widget());
        if (frame && frame->property("agentId").toInt() == agent->getId()) {
            panelLayout->removeWidget(frame);
            frame->deleteLater();

            auto& agents = (agent->getTeam() == Agent::Team1) ? team1Agents : team2Agents;
            agents.erase(std::remove_if(agents.begin(), agents.end(),
                                        [&](const std::shared_ptr<Agent>& a) { return a->getId() == agent->getId(); }),
                         agents.end());
            break;
        }
    }
}

void GamePlayPage::checkAllAgentsPlaced() {
    if (placementPhase && team1Agents.empty() && team2Agents.empty()) {
        placementPhase = false;
        qDebug() << "All agents placed! Starting game...";
        emit allAgentsPlaced();

        updateTurnLabel();
    }
}
