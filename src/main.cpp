#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {7, 3},     // Left Chassis Ports (negative port will reverse it!)
    {-9, -11},  // Right Chassis Ports (negative port will reverse it!)

    2,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Uncomment the trackers you're using here!
// - `8` and `9` are smart ports (making these negative will reverse the sensor)
//  - you should get positive values on the encoders going FORWARD and RIGHT
// - `2.75` is the wheel diameter
// - `4.0` is the distance from the center of the wheel to the center of the robot
// ez::tracking_wheel horiz_tracker(8, 2.75, 4.0);  // This tracking wheel is perpendicular to the drive wheels
// ez::tracking_wheel vert_tracker(9, 2.75, 4.0);   // This tracking wheel is parallel to the drive wheels
pros::Motor lift(10);
pros::ADIDigitalOut claw('H');



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

pros::Controller master(pros::E_CONTROLLER_MASTER);

void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  //  - ignore this if you aren't using a horizontal tracker
  // chassis.odom_tracker_back_set(&horiz_tracker);
  // Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
  //  - change `left` to `right` if the tracking wheel is to the right of the centerline
  //  - ignore this if you aren't using a vertical tracker
  // chassis.odom_tracker_left_set(&vert_tracker);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  //REAL AUTONS HERE
  /*
  ez::as::auton_selector.autons_add({
      Auton("Autonomous 1\nDoes Something", testauton);
  });
  */
  /*
  ez::as::auton_selector.selected_auton_print(); 
  pros::lcd::register_btn0_cb(ez::as::page_down);
  pros::lcd::register_btn2_cb(ez::as::page_up);
  //Auton("Autonomous 3\nDoes Something More", auto3),
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);
  printf("Enabled? %i\n", ez::as::enabled()); // Returns false
  ez::as::initialize();
  printf("Enabled? %i\n", ez::as::enabled()); // Returns true
  */

  // Autonomous Selector using LLEMU
  /*
  ez::as::auton_selector.autons_add({
      {"Drive\n\nDrive forward and come back", drive_example},
      {"Turn\n\nTurn 3 times.", turn_example},
      {"Drive and Turn\n\nDrive forward, turn, come back", drive_and_turn},
      {"Drive and Turn\n\nSlow down during drive", wait_until_change_speed},
      {"Swing Turn\n\nSwing in an 'S' curve", swing_example},
      {"Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining},
      {"Combine all 3 movements", combining_movements},
      {"Interference\n\nAfter driving forward, robot performs differently if interfered or not", interfered_example},
      {"Simple Odom\n\nThis is the same as the drive example, but it uses odom instead!", odom_drive_example},
      {"Pure Pursuit\n\nGo to (0, 30) and pass through (6, 10) on the way.  Come back to (0, 0)", odom_pure_pursuit_example},
      {"Pure Pursuit Wait Until\n\nGo to (24, 24) but start running an intake once the robot passes (12, 24)", odom_pure_pursuit_wait_until_example},
      {"Boomerang\n\nGo to (0, 24, 45) then come back to (0, 0, 0)", odom_boomerang_example},
      {"Boomerang Pure Pursuit\n\nGo to (0, 24, 45) on the way to (24, 24) then come back to (0, 0, 0)", odom_boomerang_injected_pure_pursuit_example},
      {"Measure Offsets\n\nThis will turn the robot a bunch of times and calculate your offsets for your tracking wheels.", measure_offsets},
  });
`*/
  
  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  chassis.pid_drive_set(24_in, 110);
  /*
  Odometry and Pure Pursuit are not magic

  It is possible to get perfectly consistent results without tracking wheels,
  but it is also possible to have extremely inconsistent results without tracking wheels.
  When you don't use tracking wheels, you need to:
   - avoid wheel slip
   - avoid wheelies
   - avoid throwing momentum around (super harsh turns, like in the example below)
  You can do cool curved motions, but you have to give your robot the best chance
  to be consistent
  */

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);


/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  bool claw_open = false;

  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  uint32_t start_time = pros::millis();
  
  chassis.opcontrol_joystick_practicemode_toggle(false);
  chassis.pid_tuner_enable();
  chassis.pid_tuner_print_brain_set(true);
  chassis.pid_tuner_print_terminal_set(true);

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    ez_template_extras();
    printf("LY: %d | RX: %d\n",
           master.get_analog(ANALOG_LEFT_Y),
           master.get_analog(ANALOG_RIGHT_X));

    chassis.opcontrol_arcade_flipped(ez::SPLIT);  // Arcade control
    // chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

  // PID tuner code

    if (!pros::competition::is_connected()) { 
      // Enable / Disable PID Tuner
      if (master.get_digital_new_press(DIGITAL_X)) 
        chassis.pid_tuner_toggle();
        
      // Trigger the selected autonomous routine
      if (master.get_digital_new_press(DIGITAL_B)) 
        autonomous();

      chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    } 

    // . . .
    // Put more user control code here!
    // . . .
    if (master.get_digital(DIGITAL_UP)) {
      lift.move(33);
    }
    else if (master.get_digital(DIGITAL_DOWN)) {
      lift.move(-33);
    }
    else {
      lift.move(0);
      lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
    pros::delay(20);


    if (master.get_digital_new_press(DIGITAL_R1)) {
      claw_open = !claw_open;
      claw.set_value(claw_open);
    }

    pros::delay(20);

    /*
    //1 minute and 45 seconds total = 105,000 milliseconds
    uint32_t elapsed = pros::millis() - start_time;

    if (elapsed > 85000) { //final 20 seconds of match
      master.print(0, 0, "ENDGAME");
      //add something to cap speed maybe
    }
    */
    
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

/*
Macro idea from AI (I think it's ok)

enum MacroState { IDLE, DEPOSITING, RELEASING, RESETTING };
MacroState current_macro_state = IDLE;

// Global tracker for stack layers (0 = Floor, 1 = Layer One, 2 = Layer Two, etc.)
int stack_layer = 0; 

// Lookup array or formula for your arm encoder targets per layer
// Adjust these numbers based on physical testing with Override Pins/Cups
const int LAYER_HEIGHTS[] = { 150, 300, 450, 600, 750 }; 
const int MAX_LAYERS = 5;

void dynamic_macro_task(void* param) {
    uint32_t start_time = pros::millis();
    bool command_sent = false; // Prevents motor command spamming
    
    while (true) {
        int dynamic_target = LAYER_HEIGHTS[stack_layer];

        switch (current_macro_state) {
            case IDLE:
                command_sent = false; // Reset toggle for next launch
                break;
                
            case DEPOSITING:
                // Send the move command EXACTLY ONCE when entering this state
                if (!command_sent) {
                    arm_motor.move_absolute(dynamic_target, 100);
                    command_sent = true; 
                }
                
                // Keep checking the encoder until it reaches the target window
                if (std::abs(arm_motor.get_position() - dynamic_target) < 10) {
                    start_time = pros::millis(); // Reset timer for pneumatic delay
                    command_sent = false;        // Reset toggle for next state
                    current_macro_state = RELEASING;
                }
                break;
                
            case RELEASING:
                claw_pneumatic.set_value(true);
                
                // Wait 150ms for air pressure to clear the physical stack
                if (pros::millis() - start_time > 150) {
                    current_macro_state = RESETTING;
                }
                break;
                
            case RESETTING:
                if (!command_sent) {
                    int clear_height = dynamic_target + 80; // Small upward pop
                    arm_motor.move_absolute(clear_height, 100);
                    command_sent = true;
                }
                
                int clear_height = dynamic_target + 80;
                if (std::abs(arm_motor.get_position() - clear_height) < 15) {
                    claw_pneumatic.set_value(false); // Close claw for next intake
                    
                    // Auto-increment to the next stack layer list index
                    if (stack_layer < MAX_LAYERS - 1) {
                        stack_layer++; 
                    }
                    
                    current_macro_state = IDLE; // Successfully completed!
                }
                break;
        }
        pros::delay(20); // Safeguards the processor from locking up
    }
}    

void opcontrol() {
    while (true) {
        // Standard EZ-Template drive setup
        chassis.set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));

        // TRIGGER THE MACRO
        if (master.get_digital_new_press(DIGITAL_R1) && current_macro_state == IDLE) {
            current_macro_state = DEPOSITING;
        }

        // MANUAL HEIGHT ADJUSTMENT (Overriding the auto-increment)
        if (master.get_digital_new_press(DIGITAL_UP)) {
            if (stack_layer < MAX_LAYERS - 1) stack_layer++;
            master.rumble("."); // Give physical vibration feedback to the driver
        }
        if (master.get_digital_new_press(DIGITAL_DOWN)) {
            if (stack_layer > 0) stack_layer--;
            master.rumble("-"); // Different rumble pattern for down
        }
        
        // RESET BUTTON (If you back away and start a completely new stack on the floor)
        if (master.get_digital_new_press(DIGITAL_X)) {
            stack_layer = 0;
            arm_motor.move_absolute(0, 90); // Bring arm back to zero
        }

        // Standard driver manual arm overrides go here...
        pros::delay(EZ_TEMPLATE_LOOP_DELAY);
    }
}


*/