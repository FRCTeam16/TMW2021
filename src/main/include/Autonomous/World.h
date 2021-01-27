#ifndef SRC_AUTONOMOUS_WORLD_H_
#define SRC_AUTONOMOUS_WORLD_H_

#include "FieldInfo.h"
#include "AutoPositions.h"


class AutoManager;

class World {
private:
	bool isRed;
	AutoStartPosition startPosition;

	double driveDistance = 0;
	double driveDistanceOvershoot = 0;

	CrabInfo lastCrab;
public:
	World();
	virtual ~World() {}

	void Init();							// perform world initialization
	double GetClock() const;				// time elapsed since Init() in seconds
	bool IsRed();

	AutoStartPosition GetStartPosition() { return startPosition; }
	void SetStartPosition(AutoStartPosition pos) { startPosition = pos; }

	void SetDriveDistance(double d) { driveDistance = d; }
	double GetDriveDistance() { return driveDistance; }

	void SetDriveDistanceOvershoot(double d) { driveDistanceOvershoot = d; }
	double GetDriveDistanceOvershoot() { return driveDistanceOvershoot; }

	void SetLastCrab(CrabInfo crabInfo) { lastCrab = crabInfo; }
	CrabInfo& GetLastCrab() { return lastCrab; }
};

#endif /* SRC_AUTONOMOUS_WORLD_H_ */
