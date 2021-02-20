#pragma once
#include "../../Strategy.h"


class SlalomAutoStrategy : public StepStrategy {
public:
	SlalomAutoStrategy(std::shared_ptr<World> world);
	virtual ~SlalomAutoStrategy() {}
	void Init(std::shared_ptr<World> world) override;

private:
};