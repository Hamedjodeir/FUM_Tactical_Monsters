#include "agent.h"

Agent::Agent(int id, Type type, Team team,
             int hp, int dmg, int mobility, int attackRange,
             MovementType moveType,
             const QString& name,
             const QString& imagePath)
    : m_id(id), m_type(type), m_team(team),
    m_hp(hp), m_dmg(dmg),
    m_mobility(mobility), m_attackRange(attackRange),
    m_moveType(moveType),
    m_name(name), m_imagePath(imagePath),
    m_row(-1), m_col(-1)
{
}
Agent::Agent(int id, Type type, Team team)
    : m_id(id), m_type(type), m_team(team),
    m_hp(100), m_dmg(20), m_mobility(2), m_attackRange(1),
    m_moveType(Grounded),
    m_name(QString("Agent %1").arg(id)),
    m_imagePath(":/Assets/agents/default.png"),
    m_row(-1), m_col(-1)
{
}


int Agent::getId() const { return m_id; }
Agent::Type Agent::getType() const { return m_type; }
Agent::Team Agent::getTeam() const { return m_team; }
int Agent::getHp() const { return m_hp; }
int Agent::getDmg() const { return m_dmg; }
int Agent::getMobility() const { return m_mobility; }
int Agent::getAttackRange() const { return m_attackRange; }
Agent::MovementType Agent::getMovementType() const { return m_moveType; }
QString Agent::getName() const { return m_name; }
QString Agent::getImagePath() const { return m_imagePath; }
QPixmap Agent::getPixmap() const { return QPixmap(m_imagePath); }

void Agent::setHp(int hp) { m_hp = hp; }

void Agent::setPosition(int row, int col) {
    m_row = row;
    m_col = col;
}

std::pair<int, int> Agent::getPosition() const {
    return {m_row, m_col};
}
