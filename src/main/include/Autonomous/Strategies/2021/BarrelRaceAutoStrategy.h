#pragma once
#include "../../Strategy.h"


class BarrelRaceAutoStrategy : public StepStrategy {
public:
	BarrelRaceAutoStrategy(std::shared_ptr<World> world);
	virtual ~BarrelRaceAutoStrategy() {}
	void Init(std::shared_ptr<World> world) override;

private:
};