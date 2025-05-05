#ifndef AGENT_H
#define AGENT_H

#include <QString>

class Agent
{
public:
    enum Team {
        NoTeam = 0,
        Team1 = 1,
        Team2 = 2
    };

    enum Type {
        NoAgent = 0,
        BlackAgent = 1,
        RedAgent = 2
    };

    Agent(int id, Type type, Team team, int hp = 100, int dmg = 20);

    int getId() const;
    Type getType() const;
    Team getTeam() const;
    int getHp() const;
    int getDmg() const;
    QString getName() const;
    void setPosition(int row, int col);
    std::pair<int, int> getPosition() const;

private:
    int m_id;
    Type m_type;
    Team m_team;
    int m_hp;
    int m_dmg;
    int m_row;
    int m_col;
};

#endif // AGENT_H
