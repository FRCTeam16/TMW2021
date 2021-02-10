#pragma once
#include "../../Strategy.h"


class BounceAutoStrategy : public StepStrategy {
public:
	BounceAutoStrategy(std::shared_ptr<World> world);
	virtual ~BounceAutoStrategy() {}
	void Init(std::shared_ptr<World> world) override;

private:
};