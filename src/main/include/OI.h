// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "frc/WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	std::shared_ptr<frc::Joystick> joystick2;
	std::shared_ptr<frc::JoystickButton> spinR;
	std::shared_ptr<frc::JoystickButton> spinL;
	std::shared_ptr<frc::JoystickButton> haltElevator;
	std::shared_ptr<frc::JoystickButton> actuateElevator;
	std::shared_ptr<frc::JoystickButton> actuateElbow;
	std::shared_ptr<frc::JoystickButton> openGrabber2;
	std::shared_ptr<frc::JoystickButton> closeGrabber1;
	std::shared_ptr<frc::Joystick> joystick;
	std::shared_ptr<frc::JoystickButton> printFeedData;
	std::shared_ptr<frc::JoystickButton> swingClimberButton3;
	std::shared_ptr<frc::JoystickButton> upShift6;
	std::shared_ptr<frc::JoystickButton> downShift5;
	std::shared_ptr<frc::JoystickButton> climbDownButton7;
	std::shared_ptr<frc::JoystickButton> resetAHRS4;
	std::shared_ptr<frc::JoystickButton> climbUpButton2;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::Joystick> getJoystick();
	std::shared_ptr<frc::Joystick> getJoystick2();
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
