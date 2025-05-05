#include "agent.h"

Agent::Agent(int id, Type type, Team team, int hp, int dmg)
    : m_id(id), m_type(type), m_team(team), m_hp(hp), m_dmg(dmg), m_row(-1), m_col(-1)
{
}

int Agent::getId() const {
    return m_id;
}

Agent::Type Agent::getType() const {
    return m_type;
}

Agent::Team Agent::getTeam() const {
    return m_team;
}

int Agent::getHp() const {
    return m_hp;
}

int Agent::getDmg() const {
    return m_dmg;
}

QString Agent::getName() const {
    return QString("Agent %1").arg(m_id);
}

void Agent::setPosition(int row, int col) {
    m_row = row;
    m_col = col;
}

std::pair<int, int> Agent::getPosition() const {
    return {m_row, m_col};
}
