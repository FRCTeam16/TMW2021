#pragma once
#include "../../Strategy.h"


class GalacticSearchAutoStrategy : public StepStrategy {
public:
	GalacticSearchAutoStrategy(std::shared_ptr<World> world);
	virtual ~GalacticSearchAutoStrategy() {}
	void Init(std::shared_ptr<World> world) override;

private:
    enum DetectedPath { kRedA, kRedB, kBlueA, kBlueB, kUnknown };
    DetectedPath DetectPath();
    void RedA();
    void RedB();
    void BlueA();
    void BlueB();
};