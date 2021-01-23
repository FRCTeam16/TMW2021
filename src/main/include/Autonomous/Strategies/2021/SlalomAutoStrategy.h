

#ifndef SRC_AUTONOMOUS_SLALOMAUTOSTRATEGY_H_
#define SRC_AUTONOMOUS_SLALOMAUTOSTRATEGY_H_

#include "../../Strategy.h";


class SlalomAutoStrategy : public StepStrategy {
public:
	SlalomAutoStrategy(std::shared_ptr<World> world);
	virtual ~SlalomAutoStrategy() {}
	void Init(std::shared_ptr<World> world) override;

private:
};

#endif /* SRC_AUTONOMOUS_SlalomAUTOSTRATEGY_H_ */
