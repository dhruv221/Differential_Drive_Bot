# Differential_Drive_Bot
This is a raspberry pi pico-based library for controlling two-wheeled differential drive robots using a smooth kinematic model to improve accuracy, repeatability, robustness, and efficiency.
I've done my best to keep the code as fast and memory-efficient as feasible.
It presently makes advantage of the dual core functionality to keep track of the odometry, but it may be effectively done on other mcu's using timers or other ISR trickery.

basic idea:
![image](https://github.com/dhruv221/Differential_Drive_Bot/assets/62287269/62fa21eb-1b9d-4fb4-94b3-f65d46e1552e)
