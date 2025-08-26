#include "agentBuild.h"

std::vector<std::shared_ptr<Agent>> AgentBuild::createAllAgents()
{
    std::vector<std::shared_ptr<Agent>> agents;

    // ========== WATER WALKING ==========
    agents.push_back(std::make_shared<Agent>(1, Agent::NoAgent, Agent::NoTeam,
                                             320, 90, 3, 1, Agent::WaterWalking, "Billy", ":/Assets/agents/billy.png"));
    agents.push_back(std::make_shared<Agent>(2, Agent::NoAgent, Agent::NoTeam,
                                             320, 80, 2, 2, Agent::WaterWalking, "Reketon", ":/Assets/agents/reketon.png"));
    agents.push_back(std::make_shared<Agent>(3, Agent::NoAgent, Agent::NoTeam,
                                             400, 100, 2, 1, Agent::WaterWalking, "Angus", ":/Assets/agents/angus.png"));
    agents.push_back(std::make_shared<Agent>(4, Agent::NoAgent, Agent::NoTeam,
                                             320, 100, 2, 2, Agent::WaterWalking, "Duraham", ":/Assets/agents/duraham.png"));
    agents.push_back(std::make_shared<Agent>(5, Agent::NoAgent, Agent::NoTeam,
                                             400, 100, 2, 1, Agent::WaterWalking, "Colonel Baba", ":/Assets/agents/colonel_baba.png"));
    agents.push_back(std::make_shared<Agent>(6, Agent::NoAgent, Agent::NoTeam,
                                             320, 90, 2, 2, Agent::WaterWalking, "Medusa", ":/Assets/agents/medusa.png"));
    agents.push_back(std::make_shared<Agent>(7, Agent::NoAgent, Agent::NoTeam,
                                             320, 100, 3, 1, Agent::WaterWalking, "Bunka", ":/Assets/agents/bunka.png"));
    agents.push_back(std::make_shared<Agent>(8, Agent::NoAgent, Agent::NoTeam,
                                             320, 100, 3, 1, Agent::WaterWalking, "Sanka", ":/Assets/agents/sanka.png"));

    // ========== GROUNDED ==========
    agents.push_back(std::make_shared<Agent>(9, Agent::NoAgent, Agent::NoTeam,
                                             320, 110, 3, 1, Agent::Grounded, "Sir Lamorak", ":/Assets/agents/sir_lamorak.png"));
    agents.push_back(std::make_shared<Agent>(10, Agent::NoAgent, Agent::NoTeam,
                                             400, 120, 2, 1, Agent::Grounded, "Kabu", ":/Assets/agents/kabu.png"));
    agents.push_back(std::make_shared<Agent>(11, Agent::NoAgent, Agent::NoTeam,
                                             320, 130, 2, 1, Agent::Grounded, "Rajakal", ":/Assets/agents/rajakal.png"));
    agents.push_back(std::make_shared<Agent>(12, Agent::NoAgent, Agent::NoTeam,
                                             400, 80, 2, 1, Agent::Grounded, "Salih", ":/Assets/agents/salih.png"));
    agents.push_back(std::make_shared<Agent>(13, Agent::NoAgent, Agent::NoTeam,
                                             320, 90, 2, 1, Agent::Grounded, "Khan", ":/Assets/agents/khan.png"));
    agents.push_back(std::make_shared<Agent>(14, Agent::NoAgent, Agent::NoTeam,
                                             400, 100, 2, 1, Agent::Grounded, "Boi", ":/Assets/agents/boi.png"));
    agents.push_back(std::make_shared<Agent>(15, Agent::NoAgent, Agent::NoTeam,
                                             240, 100, 2, 2, Agent::Grounded, "Eloi", ":/Assets/agents/eloi.png"));
    agents.push_back(std::make_shared<Agent>(16, Agent::NoAgent, Agent::NoTeam,
                                             160, 100, 2, 2, Agent::Grounded, "Kanar", ":/Assets/agents/kanar.png"));
    agents.push_back(std::make_shared<Agent>(17, Agent::NoAgent, Agent::NoTeam,
                                             320, 140, 2, 2, Agent::Grounded, "Elsa", ":/Assets/agents/elsa.png"));
    agents.push_back(std::make_shared<Agent>(18, Agent::NoAgent, Agent::NoTeam,
                                             280, 80, 2, 2, Agent::Grounded, "Karissa", ":/Assets/agents/karissa.png"));
    agents.push_back(std::make_shared<Agent>(19, Agent::NoAgent, Agent::NoTeam,
                                             400, 100, 2, 1, Agent::Grounded, "Sir Philip", ":/Assets/agents/sir_philip.png"));
    agents.push_back(std::make_shared<Agent>(20, Agent::NoAgent, Agent::NoTeam,
                                             260, 80, 2, 2, Agent::Grounded, "Frost", ":/Assets/agents/frost.png"));
    agents.push_back(std::make_shared<Agent>(21, Agent::NoAgent, Agent::NoTeam,
                                             400, 100, 2, 1, Agent::Grounded, "Tusk", ":/Assets/agents/tusk.png"));

    // ========== FLYING ==========
    agents.push_back(std::make_shared<Agent>(22, Agent::NoAgent, Agent::NoTeam,
                                             320, 120, 3, 1, Agent::Flying, "Rambo", ":/Assets/agents/rambo.png"));

    // ========== FLOATING ==========
    agents.push_back(std::make_shared<Agent>(23, Agent::NoAgent, Agent::NoTeam,
                                             320, 100, 3, 1, Agent::Floating, "Sabrina", ":/Assets/agents/sabrina.png"));
    agents.push_back(std::make_shared<Agent>(24, Agent::NoAgent, Agent::NoTeam,
                                             240, 120, 3, 2, Agent::Floating, "Death", ":/Assets/agents/death.png"));

    return agents;
}

std::shared_ptr<Agent> AgentBuild::createByName(const QString& name)
{
    auto all = createAllAgents();
    for (auto& agent : all) {
        if (agent->getName().compare(name, Qt::CaseInsensitive) == 0) {
            return agent;
        }
    }
    return nullptr;
}
