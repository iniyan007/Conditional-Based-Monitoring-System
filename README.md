# Conditional-Based-Monitoring-System

Conditional based monitoring system - Tunnel Booster Fan - Present for SMART INDIA HACKATHON 2024

Problem Statement ID - SH1583

Problem statement: Condition-based monitoring and maintenance system

Description:
  
  Background: There are a large number of tunnel booster fans (TBF) of different capacity installed in tunnel area at underground metro stations. These IBFs have different maintenance schedules and frequency prescribed by OEM. The TBF's are not operated regularly but are tested during mock drills. The exercise of scheduled preventive maintenance of this equipment involves a large number of manpower and risk of working at height. The Condition-based maintenance in place of scheduled preventive maintenance would be very helpful in optimizing the maintenance and manpower cost involved. Description: To optimize the maintenance and manpower cost there is a great need of developing a condition-based monitoring and maintenance system. The historical data pertaining to failures along with the symptoms, the permissible limits of different parameters. the previous maintenance records of TBF shall be fed into the Al based condition monitoring system. The Al based system shall analyze and compare this historical data with parameter obtained at the time of operation during the testing/mock drill to predict any maintenance requirement based on the condition of TBF and the system shall also alert in case of any deviation from specified values. Expected Solution: Condition-based monitoring and maintenance system which can use machine learning & behavioural analytics to predict any maintenance requirement based on the condition of a particular system.

Key Points from Problem description:
  Various Parameters: Temperature, Humidity, RPM, Emissions from Road Surface and Vehicles, Excess Vibrations, Failure due to Overload 
  Condition Based Maintenance (CBM) in place of Time Based Maintenance (TBM)
  Collect Previous  Records (if available) and Record Current Data to Analysis and Alert using Deep Neural Network.

Proposed Solution:
  Secondary Research: Identified various reason for Tunnel Booster Fan (TBF) failures.
  Read and record the Data: RPM, Current, Noise & Vibration, temperature, Humidity and Thermal Image
  Data are analyzed using Deep Neural Network
  Data are visualized in Applications and may be recorded in cloud as per the requirement.
  Maintenances alert are sent through SMS and can be scheduled accordingly.

Flow Chart:
  ![image](https://github.com/user-attachments/assets/8d44737e-a741-400b-a179-b4717b50b219)

FEASIBILITY AND VIABILITY:
  Monitoring TBF is technically feasible as the sensors are  highly reliable, effective and economic.
  This system can be integrated with existing control system used for managing tunnel operations as like Building Management System (BMS).
  The potential  challenge: The data communication and connectivity, as the      tunnel structures may interfere with wireless signals.
  The challenge may be countered by incorporating Deep Neural Network (ANN) through Deep learning (DL) approach.

IMPACT AND BENEFITS:
Impact:
  Reduce unexpected downtime because it detects the small problems before it becomes a severe failure.
  Increases the equipment reliability and lifespan as the bearings, stator and rotor’s misalignment and wear are forecasted by the sensor.
  Advanced Prediction without Human Intervention.
  Less Risk as the accessing fan at higher altitude is reduced.
Benifits:
  Remove the risk of worktime accidents due to condition based maintenance.
  Reduces the maintenance cost due to AI prediction
  Ensured reliability during fire rescue period.
  Metro Commuters will not be affected due to less downtime.
  No harm to the atmosphere.
