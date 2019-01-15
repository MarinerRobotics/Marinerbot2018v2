// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <iostream>
#include <string>

#include "Subsystems/DriveBase.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/DriveWithJoy.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveBase::DriveBase() : frc::Subsystem("DriveBase") {
    driveTrainLeftTalonSlave.reset(new WPI_TalonSRX(10));
    driveTrainRightTalonSlave.reset(new WPI_TalonSRX(11));
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    driveTrainLeftTalon.reset(new WPI_TalonSRX(0));
    driveTrainRightTalon.reset(new WPI_TalonSRX(1));
    driveTrain.reset(new frc::DifferentialDrive(*driveTrainLeftTalon, *driveTrainRightTalon));
    ultrasonicLeft.reset(new frc::AnalogInput(1));
    ultrasonicRight.reset(new frc::AnalogInput(2));
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    driveBackSpeed = -1.0;
    driveStraightSpeed = 1.0;
    distanceToLeftObject = 0;
    piggy.reset(new PigeonIMU(0));
    //piggy.reset(new PigeonIMU(*driveTrainLeftTalon));
   // piggy = new PigeonIMU(driveTrainLeftTalon);
   stringy.reset(new frc::AnalogPotentiometer(0,3600,30));
}

void DriveBase::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveWithJoy());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
        driveTrainLeftTalonSlave->Follow(*driveTrainLeftTalon);
        driveTrainRightTalonSlave->Follow(*driveTrainRightTalon);
        
        //Left DriveTrain
        driveTrainLeftTalon->SetInverted(true);
        driveTrainLeftTalonSlave->SetInverted(true);

        //Right DriveTrain
        driveTrainRightTalon->SetInverted(true);
        driveTrainRightTalonSlave->SetInverted(true);

        driveTrainLeftTalon->SetSensorPhase(true);
        driveTrainRightTalon->SetSensorPhase(true);

        const int kTimeoutMs = 30;
        piggy->SetFusedHeading(0.0, kTimeoutMs); /* reset heading, angle measurement wraps at plus/minus 23,040 degrees (64 rotations) */
        _goStraight = GoStraightOff;
}

void DriveBase::Periodic() {
    // Put code here to be run every loop
   }

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveBase::showInfo(){ //formally called PrintEncoderSpeed
int leftPos = driveTrainLeftTalon->GetSelectedSensorPosition(0);
int rightPos = driveTrainRightTalon->GetSelectedSensorPosition(1);



int distance = getCurrentEncoderPos();
double dir = getCurrentAngle();
double frontUltrasonic = getInchesToObject();
int elpos = Robot::elevator->GetElPosition();
double stringPotVal = stringy->Get();
    //int stringPotVal = stringy->Get();
std::cout 	<< "stringy : " << stringPotVal << std::endl;

std::cout 	<< "dir : " << dir << std::endl;
std::cout 	<< "leftPos : " << leftPos << std::endl;
std::cout 	<< "rightPos : " << rightPos << std::endl;
std::cout 	<< "distance : " << distance << std::endl;
std::cout 	<< "frontUltrasonic : " << frontUltrasonic << std::endl;
std::cout 	<< "elpos : " << elpos << std::endl;
}

void DriveBase::resetAhrs(){
    
}

double DriveBase::getCurrentEncoderPos(){
    double encoderReading = driveTrainLeftTalon->GetSelectedSensorPosition(0);
    return encoderReading / 1831.645; //convert the sensor reading to inches
}

double DriveBase::getInchesToObject(){
    double voltage = ultrasonicLeft->GetAverageVoltage();
    double dist_mm = voltage/0.977*1000;
    double dist_in = dist_mm/25.4;
    return dist_in;
}

void DriveBase::DriveStraight(double driveStraightSpeed){
    driveTrain->TankDrive(driveStraightSpeed, driveStraightSpeed);
}

void DriveBase::Halt(){
    driveTrain->TankDrive(0.0,0.0);
}

void DriveBase::JoyDrive(double myX, double myY){
    //myX = myX *1;
    //myY = myY *-1;

		double forwardThrottle = myX * 1.0; /* sign so that positive is forward */
		double turnThrottle = myY * -1.0; /* sign so that positive means turn left */

		PigeonIMU::GeneralStatus genStatus;
		double xyz_dps[3];
		piggy->GetGeneralStatus(genStatus);
		piggy->GetRawGyro(xyz_dps);
        PigeonIMU::FusionStatus *stat = new PigeonIMU::FusionStatus();
		piggy->GetFusedHeading(*stat);
		double currentAngle = stat->heading;
		bool angleIsGood = (piggy->GetState() == PigeonIMU::Ready) ? true : false;
		double currentAngularRate = xyz_dps[2];
        bool userWantsGoStraight = Robot::oi->getJoystick()->GetRawButton(5); /* top left shoulder button */

		/* deadbands so centering joysticks always results in zero output */
		forwardThrottle = DB(forwardThrottle);
		turnThrottle = DB(turnThrottle);
		switch (_goStraight) {

			/* go straight is off, better check gamepad to see if we should enable the feature */
			case GoStraightOff:
				if (userWantsGoStraight == false) {
					/* nothing to do */
				} else if (angleIsGood == false) {
					/* user wants to servo but Pigeon isn't connected? */
					_goStraight = GoStraightSameThrottle; /* just apply same throttle to both sides */
				} else {
					/* user wants to servo, save the current heading so we know where to servo to. */
					_goStraight = GoStraightWithPidgeon;
					_targetAngle = currentAngle;
				}
				break;
	
			/* we are servo-ing heading with Pigeon */
			case GoStraightWithPidgeon:
				if (userWantsGoStraight == false) {
					_goStraight = GoStraightOff; /* user let go, turn off the feature */
				} else if (angleIsGood == false) {
					_goStraight = GoStraightSameThrottle; /* we were servoing with pidgy, but we lost connection?  Check wiring and deviceID setup */
				} else {
					/* user still wants to drive straight, keep doing it */
				}
				break;
	
			/* we are simply applying the same throttle to both sides, apparently Pigeon is not connected */
			case GoStraightSameThrottle:
				if (userWantsGoStraight == false) {
					_goStraight = GoStraightOff; /* user let go, turn off the feature */
				} else {
					/* user still wants to drive straight, keep doing it */
				}
				break;
		}
/* if we can servo with IMU, do the math here */
		if (_goStraight == GoStraightWithPidgeon) {
			/* very simple Proportional and Derivative (PD) loop with a cap,
			 * replace with favorite close loop strategy or leverage future Talon <=> Pigeon features. */
			turnThrottle = (_targetAngle - currentAngle) * kPgain - (currentAngularRate) * kDgain;
			/* the max correction is the forward throttle times a scalar,
			 * This can be done a number of ways but basically only apply small turning correction when we are moving slow
			 * and larger correction the faster we move.  Otherwise you may need stiffer pgain at higher velocities. */
			double maxThrot = MaxCorrection(forwardThrottle, kMaxCorrectionRatio);
			turnThrottle = Cap(turnThrottle, maxThrot);
		} else if (_goStraight == GoStraightSameThrottle) {
			/* clear the turn throttle, just apply same throttle to both sides */
			turnThrottle = 0;
		} else {
			/* do nothing */
		}


    driveTrain->ArcadeDrive(forwardThrottle,turnThrottle);
    //driveTrain->ArcadeDrive(myX, myY);
   // driveTrain->TankDrive(myX, myY);
}

/** @return 10% deadband */
double DriveBase::DB(double axisVal) {
    if (axisVal < -0.10)
        return axisVal;
    if (axisVal > +0.10)
        return axisVal;
    return 0;
}

double DriveBase::Cap(double value, double peak) {
    if (value < -peak)
        return -peak;
    if (value > +peak)
        return +peak;
    return value;
}

double DriveBase::MaxCorrection(double forwardThrot, double scalor) {
    /* make it positive */
    if (forwardThrot < 0) {
        forwardThrot = -forwardThrot;
    }
    /* max correction is the current forward throttle scaled down */
    forwardThrot *= scalor;
    /* ensure caller is allowed at least 10% throttle,
        * regardless of forward throttle */
    if (forwardThrot < 0.10)
        return 0.10;
    return forwardThrot;
}


void DriveBase::turnToAngle(double degree){
    double c = getCurrentAngle();
    double e;
    time_t start = time(NULL);
    e=c+degree;
    if(degree>=0){
        while(getCurrentAngle()<e){
            driveTrain->TankDrive(0.6,-0.6);
            time_t taken = time(NULL) - start;
            if (taken > 5){//Sanity Check
                break;
            }
        }
    }
    else{
        while(getCurrentAngle()>e){
            driveTrain->TankDrive(-0.6,0.6);
            time_t taken = time(NULL) - start;
            if(taken>5){
                break;
            }
        }
    }
}

double DriveBase::getCurrentAngle(){
    //double heading = piggy->GetFusedHeading;
 double ypr[3];
piggy->GetYawPitchRoll(ypr); //gets yaw,pitch/roll
 double heading = ypr[0];
   return heading;

    //return 0.0;
}