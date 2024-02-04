# Serial
Group that will work with serial to connect two components together
=======
# Serial
Group that will work with serial to connect two components together

* “i2c_encoder_test” uses the wire library in Arduino to communicate with the as5600 magnetic encoders and read the angular positions of the joints
* “stepper_motor_RAMPS_test” uses the Accelstepper and Multistepper Arduino libraries to control the stepper motors simultaneously 
* “tuning_drivers” is a script that runs nothing on the board that I use to tune the stepper drivers. To read a voltage on the drivers’ potentiometers, power must be sent to the board. This script can be uploaded if a previous script was uploaded to the board and you want to be able to tune the drivers without worrying about the arm moving.
* “two_motor_test” was a test script that Aryash and I created to control two stepper motors simultaneously without the Accelstepper library. I ultimately concluded that it was much easier to use Accelstepper, but the script still could potentially be useful at some point.
-AJ

## Run the ROS Package on your own system

0. Setup ROS on your system - check the ros tutorials website for creating a catkin_make directory and setting it up

1. Install rosserial_arduino, rosserial using apt-get

2. Copy the ArmControl folder into your src folder in your catkin_make directory

3. Source the setup files and make the package
