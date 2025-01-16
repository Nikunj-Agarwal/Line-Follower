# ESP32-based Line Follower Robot with Acute Angle Handling

This code implements a line follower robot using an ESP32 microcontroller, two IR sensors,
and a dual motor driver. The robot is designed to follow a black line on a light surface
and navigate through various path scenarios, including straight lines, curves, and acute angles.

![WhatsApp Image 2024-10-15 at 11 38 28_f5ff60d4](https://github.com/user-attachments/assets/cc5849b1-6194-4cd4-b542-c64c15c74510)

Key Components:
- ESP32 microcontroller
- Two IR sensors (LEFT_IR and RIGHT_IR)
- Dual motor driver (controlling left and right motors)

Functionality:
1. Straight Line: When both sensors detect a light surface (no black line), the robot moves forward.
2. Gentle Curves: 
   - If the left sensor detects the line (black), the robot turns right.
   - If the right sensor detects the line (black), the robot turns left.
3. Acute Angles: When both sensors detect black (at an acute angle junction), the robot continues
   its last action (forward, left turn, or right turn) to navigate through the angle without confusion.

How it works:
- The code continuously reads the state of both IR sensors.
- Based on the sensor readings, it decides the appropriate action (move forward, turn left, or turn right).
- For each action, it updates a 'lastAction' variable to keep track of the most recent movement.
- When an acute angle is detected (both sensors read black), instead of getting confused,
  the robot continues its last action. This allows it to smoothly navigate through sharp turns.

The speed of each motor can be adjusted using the leftMotorSpeed and rightMotorSpeed variables.
The turnSpeed variable allows for sharper turns when needed.

This approach ensures that the robot can handle various track layouts, including challenging
acute angles, without losing its path or getting stuck at junctions.
