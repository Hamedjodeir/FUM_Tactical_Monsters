#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QPixmap>

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
        // later you can expand with named heroes like Billy, Medusa, etc.
    };

    enum MovementType {
        Grounded,
        WaterWalking,
        Flying,
        Floating
    };
    Agent(int id, Type type, Team team);
    Agent(int id,
          Type type,
          Team team,
          int hp,
          int dmg,
          int mobility,
          int attackRange,
          MovementType moveType,
          const QString& name,
          const QString& imagePath);

    void setTeam(Team newTeam) { m_team = newTeam; }
    // getters
    int getId() const;
    Type getType() const;
    Team getTeam() const;
    int getHp() const;
    int getDmg() const;
    int getMobility() const;
    int getAttackRange() const;
    MovementType getMovementType() const;
    QString getName() const;
    QString getImagePath() const;
    QPixmap getPixmap() const;

    // setters
    void setHp(int hp);
    void setPosition(int row, int col);
    std::pair<int, int> getPosition() const;

private:
    int m_id;
    Type m_type;
    Team m_team;
    int m_hp;
    int m_dmg;
    int m_mobility;
    int m_attackRange;
    MovementType m_moveType;
    QString m_name;
    QString m_imagePath;

    int m_row;
    int m_col;
};

#endif // AGENT_H
