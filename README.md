# Autonomous Differential Drive Robot with PID Control

## Project Overview

This project is designed to enable a differential drive robot to participate in autonomous robot competitions. The robot's motion and actions are meticulously controlled using PID (Proportional-Integral-Derivative) control principles, allowing for precise and efficient performance during matches.
The robot's core control system is built around an Arduino Mega, which acts as the brain to orchestrate the various actuators. These actuators include servo motors responsible for executing specific mechanical actions on the competition map, as well as motors that drive the robot's navigation on the map.

## Key Components and Features

- **Arduino Mega Control:** The central control unit of the robot is an Arduino Mega, which processes sensor inputs and computes control signals for the actuators.

- **Servo Motors for Mechanical Actions:** The robot's servo motors execute precise mechanical actions on the competition map, enhancing its performance and strategy during matches.

- **Motor Navigation with Rotary Encoders:** Rotary encoders, affixed to the same axis as the motors, provide crucial feedback about wheel rotations. This feedback allows the robot to determine its precise position on the competition map using odometry equations found in the source file `odometry.c`.

- **PID Control Functions:** The PID control scheme is a cornerstone of the robot's performance. PID functions are comprehensively detailed in the source file `pid.c`, ensuring accurate and stable control over the robot's movements.

- **Strategy Implementation in `main.c`:** The core logic and strategy for the robot's behavior during competition matches are defined in the `main.c` source file. This file leverages the functions defined in `odometry.c` and `pid.c` to orchestrate the robot's actions and decision-making.

## Getting Started

To explore and adapt this project for your needs, follow these steps:

1. Set up the Arduino Mega with the necessary libraries and tools.
2. Study the PID control functions detailed in the `pid.c` source file.
3. Understand the odometry equations and calculations presented in the `odometry.c` source file.
4. Examine the `main.c` source file to grasp the robot's strategy and behavior.
5. Customize the PID gains and parameters in the `pid.c` file to fine-tune the robot's control performance.
6. Modify the strategy in the `main.c` file to align with your desired competition approach.

## Contributions and Acknowledgments

This project has been a collaborative effort, benefiting from the contributions and insights of various individuals. Special thanks to:

- Farid Adwani ([@Farid](https://github.com/Farid-Adwani))

## License

This project is licensed under the [MIT License](LICENSE). Feel free to explore, modify, and adapt the code to suit your needs.

For questions or assistance, contact me at marouene.kaaniche@insat.ucar.tn .
