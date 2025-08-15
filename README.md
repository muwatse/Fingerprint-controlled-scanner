Fingerprint-Controlled Medication Dispenser

An Arduino-based smart medication management device designed to help elderly users and arthritis patients securely and easily access their prescribed medication. The system uses biometric authentication, a keypad interface, and a precise dispensing mechanism to improve safety, accessibility, and adherence to medication schedules.

🚀 Features

Biometric Security – Integrated optical fingerprint scanner for authorized access.

User-Friendly Interface – Backlit LED screen and keypad for scheduling and PIN entry.

Accurate Timekeeping – Real-Time Clock (RTC) for precise dispensing at scheduled times.

Automated Dispensing – Stepper motor and solenoid lock ensure one dose per dispense.

Accessibility-Driven Design – Ergonomic 3D-printed enclosure designed for users with limited dexterity.

Modular Electronics – Custom PCB for clean wiring and easy component replacement.

🛠 Hardware Components

Arduino Nano Every microcontroller

Optical Fingerprint Scanner (UART)

4x4 Keypad (via MCP23017 I/O Expander)

I2C 20x4 LCD Display

DS3231 RTC module

ULN2003 Stepper Motor Driver + Stepper Motor

Solenoid Lock

Custom PCB & 3D-printed enclosure

📂 Code Structure

fingerprint.cpp – Functions for enrolling, storing, and authenticating fingerprints.

keypad.cpp – Row/column scanning with debounce for accurate keypress detection.

main.cpp – Core logic for scheduling, authentication, and dispensing flow.

display.cpp – LCD interface for prompts and feedback.

motor.cpp – Stepper motor control for dose rotation.

🧪 Testing & Validation

Fingerprint recognition tested with multiple users (low false accept/reject rates).

Keypad input verified with debounce logic to avoid false triggers.

RTC accuracy confirmed with <1s drift over several days.

Mechanical dispensing validated to align with correct dose slot each time.

📸 Project Highlights

Placed 2nd in university-wide engineering competition.

Recognized by faculty for innovative, user-centric design.