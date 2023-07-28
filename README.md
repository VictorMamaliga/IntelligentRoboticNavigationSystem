# Intelligent Robotic Navigation System with Obstacle Avoidance and Line Following

## Overview

This project involves the design, development, and evaluation of a multi-functional robot capable of performing obstacle avoidance and line-following tasks. The robot uses an AT89S51 microcontroller, DC motors, L9110S Dual-Channel Driver Modules, a 9V battery, omnidirectional wheels, and various sensors including HC-SR04 ultrasound sensors and infrared sensors. 

## Features

- **Obstacle Avoidance:** The robot can autonomously navigate a maze using ultrasound and infrared sensors.
- **Line Following:** In line follower mode, the robot follows a predefined line on the floor using its infrared sensors.
- **Hardware Design:** Detailed block diagrams and pin configuration for various components are available.
- **Software Design:** The robot's control algorithms are written in C programming language. The code manages sensor data acquisition, motion control, and mode switching between obstacle avoidance, maze-solving, and line follower modes.

## Installation

1. Clone this repository to your local machine.
2. Open the project files in an appropriate C compiler that supports the AT89S51 microcontroller.
3. Compile and upload the code to the microcontroller.

## Usage

The robot can be operated in two modes: obstacle avoidance mode and line follower mode. You can toggle between these two modes using the switch button on the robot.

## Results

The robot has been tested in various environments, demonstrating high success rates in both obstacle avoidance and line following modes. The robot was able to adapt to different environments and improve its performance using mode switching functionality.

## Future Work

1. Improved Sensor Fusion: Improve the robot's performance by combining the strengths of both HC-SR04 ultrasound and infrared sensors.
2. Machine Learning and Adaptive Navigation: Incorporate machine learning algorithms or other advanced navigation techniques for efficient and effective tasks performance.
3. Integration of Additional Sensors: Adding more sensors, such as LiDAR or cameras, could enhance the robot's perception capabilities.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.



