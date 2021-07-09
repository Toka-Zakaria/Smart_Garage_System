# Smart_Garage_System
based on ATmega32 microcontroller ,a garage consists of entrance and exit gates, entrance gate is responsible to check if there is a car or not using IR sensor, 
check if the existing car belongs to guest mode or subscriber mode to give it ID or ask it for ID, open the door of the garage, 
turn on/off LEDs in the hall, the exit gate has the same features of the entrance gate, 
in addition to calculating time for each car to ask them for fees for their time in the garage, 
the system also offers a Bluetooth application to connect with the MCU to enable users to do all the previous features with their mobiles, 
in addition to provide the owner of the garage with income everyday 
- Drivers designed for the project: Timer, LCD, Keypad, servo motor, Internal EEPROM and Bluetooth

- Here is the specs of the project:
**Default state:**
the dfault state of the garage is to display the message "**Smart Garage :D**" 
- **Entrance gate:**
When the IR sensor in the entrance detected a car:
1. The LCD will display a welcome message
2. Asking the user to select if he is subscriber or guest 
3. If he selected another mode LCD will display a wrong message and will return the program to step number 2 until he choose a right mode
4. if he selected **guest** mode:
 5. System will ask him to press a specefic button to get his ID from stored IDs in the system
 6. once he pressed the button, he will own his ID and the servo motor will open the gate 
 7. the door will be opened and the ligths will be on some seconds until the car passed 
 8. the door will be closed again and system will return to the default state "System is hold until open and close door"
 9. if he selected **subscriber** mode:
 10. System will ask him to enter his passcode 
 11. if he entered wrong ID the System will display wrong ID and return the system to 10 step until he entered right passcode
 12. if he entered right passcode, system will open the door same as 6 & 7 step
 - **Exit gate:**
 When the IR sensor in the exit detected a car:
 1. The LCD will display a welcome back message
2. Asking the user to select if he is subscriber or guest 
3. If he selected another mode LCD will display a wrong message and will return the program to step number 2 until he choose a right mode
4. if he selected **guest** mode:
5. it will ask him for his ID which he took when he entered
6. if he entered wrong ID, it will display a wrong message and return to 5 step
7. once he pressed the right ID, it will display the fees must be paid depending on car time in the garage and the servo motor will open the gate 
8. the door will be opened and the ligths will be on some seconds until the car passed 
9. the door will be closed again and system will return to the default state "System is hold until open and close door"
  9. if he selected **subscriber** mode:
 10. System will ask him to enter his passcode 
 11. if he entered wrong ID the System will display wrong ID and return the system to 10 step until he entered right passcode
 12. if he entered right passcode, system will open the door same as 6 & 7 step
  
