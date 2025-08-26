#ifndef AGENTBUILD_H
#define AGENTBUILD_H

#include "agent.h"
#include <memory>
#include <vector>

class AgentBuild
{
public:
    // Returns all predefined agents (with stats from Phase 2 PDF)
    static std::vector<std::shared_ptr<Agent>> createAllAgents();

    // Find an agent definition by name
    static std::shared_ptr<Agent> createByName(const QString& name);
};

#endif // AGENTBUILD_H
