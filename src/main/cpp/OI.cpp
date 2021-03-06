// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/AutoPos1LL.h"
#include "Commands/AutoPos1RL.h"
#include "Commands/AutoPos1RR.h"
#include "Commands/AutoPos2L2.h"
#include "Commands/AutoPos2R2.h"
#include "Commands/AutoRoutine1.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/ClimbDown.h"
#include "Commands/ClimbUp.h"
#include "Commands/CloseGrabber.h"
#include "Commands/DriveBackward.h"
#include "Commands/DriveForInches.h"
#include "Commands/DriveForward.h"
#include "Commands/DriveWithJoy.h"
#include "Commands/ElbowJoyControl.h"
#include "Commands/ElevatorJoyControl.h"
#include "Commands/LowerElbow.h"
#include "Commands/LowerElevator.h"
#include "Commands/OpenGrabber.h"
#include "Commands/PrintFeedback.h"
#include "Commands/RaiseElbow.h"
#include "Commands/RaiseElevator.h"
#include "Commands/ResetAHRS.h"
#include "Commands/ShiftDown.h"
#include "Commands/ShiftUp.h"
#include "Commands/StopElevator.h"
#include "Commands/SwingClimberUp.h"
#include "Commands/TurnTo.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    joystick2.reset(new frc::Joystick(1));
    
    spinR.reset(new frc::JoystickButton(joystick2.get(), 1));
    spinR->WhenPressed(new TurnTo(90));
    spinL.reset(new frc::JoystickButton(joystick2.get(), 4));
    spinL->WhenPressed(new TurnTo(90));
    haltElevator.reset(new frc::JoystickButton(joystick2.get(), 5));
    haltElevator->WhenReleased(new StopElevator());
    actuateElevator.reset(new frc::JoystickButton(joystick2.get(), 5));
    actuateElevator->WhileHeld(new ElevatorJoyControl());
    actuateElbow.reset(new frc::JoystickButton(joystick2.get(), 6));
    actuateElbow->WhileHeld(new ElbowJoyControl());
    openGrabber2.reset(new frc::JoystickButton(joystick2.get(), 2));
    openGrabber2->WhileHeld(new OpenGrabber());
    closeGrabber1.reset(new frc::JoystickButton(joystick2.get(), 1));
    closeGrabber1->WhenPressed(new CloseGrabber());
    joystick.reset(new frc::Joystick(0));
    
    printFeedData.reset(new frc::JoystickButton(joystick.get(), 8));
    printFeedData->WhenPressed(new PrintFeedback());
    swingClimberButton3.reset(new frc::JoystickButton(joystick.get(), 3));
    swingClimberButton3->WhileHeld(new SwingClimberUp());
    upShift6.reset(new frc::JoystickButton(joystick.get(), 6));
    upShift6->WhenPressed(new ShiftUp());
    downShift5.reset(new frc::JoystickButton(joystick.get(), 5));
    downShift5->WhenPressed(new ShiftDown());
    climbDownButton7.reset(new frc::JoystickButton(joystick.get(), 7));
    climbDownButton7->WhileHeld(new ClimbDown());
    resetAHRS4.reset(new frc::JoystickButton(joystick.get(), 4));
    resetAHRS4->WhenPressed(new ResetAHRS());
    climbUpButton2.reset(new frc::JoystickButton(joystick.get(), 2));
    climbUpButton2->WhileHeld(new ClimbUp());

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("AutoPos2R2", new AutoPos2R2());
    frc::SmartDashboard::PutData("AutoPos2L2", new AutoPos2L2());
    frc::SmartDashboard::PutData("AutoPos1RR", new AutoPos1RR());
    frc::SmartDashboard::PutData("AutoPos1RL", new AutoPos1RL());
    frc::SmartDashboard::PutData("AutoPos1LL", new AutoPos1LL());
    frc::SmartDashboard::PutData("PrintFeedback", new PrintFeedback());
    frc::SmartDashboard::PutData("StopElevator", new StopElevator());
    frc::SmartDashboard::PutData("SwingClimberUp", new SwingClimberUp());
    frc::SmartDashboard::PutData("Elevator Joy Control", new ElevatorJoyControl());
    frc::SmartDashboard::PutData("Elbow Joy Control", new ElbowJoyControl());
    frc::SmartDashboard::PutData("AutoRoutine1", new AutoRoutine1());
    frc::SmartDashboard::PutData("Drive With Joy", new DriveWithJoy());
    //frc::SmartDashboard::PutData("Drive Backward", new DriveBackward());
    frc::SmartDashboard::PutData("Drive Forward", new DriveForward());
    frc::SmartDashboard::PutData("Reset AHRS", new ResetAHRS());
    frc::SmartDashboard::PutData("Shift Down", new ShiftDown());
    frc::SmartDashboard::PutData("Shift Up", new ShiftUp());
    frc::SmartDashboard::PutData("Lower Elevator", new LowerElevator());
    frc::SmartDashboard::PutData("Raise Elevator", new RaiseElevator());
    frc::SmartDashboard::PutData("Close Grabber", new CloseGrabber());
    frc::SmartDashboard::PutData("Open Grabber", new OpenGrabber());
    frc::SmartDashboard::PutData("Lower Elbow", new LowerElbow());
    frc::SmartDashboard::PutData("Raise Elbow", new RaiseElbow());
    frc::SmartDashboard::PutData("Climb Down", new ClimbDown());
    frc::SmartDashboard::PutData("Climb Up", new ClimbUp());
    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getJoystick() {
   return joystick;
}

std::shared_ptr<frc::Joystick> OI::getJoystick2() {
   return joystick2;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
