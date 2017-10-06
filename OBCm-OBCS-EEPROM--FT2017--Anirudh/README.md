# Storage and Transmission of Health Monitoring (HM) data

## Problem Statement
1. To be able to send HM data from master to slave using SPI. 
2. Read and write HM data into EEPROM using slave via I2C communication.
3. Read HM data from a particular moment from EEPROM and send it slave when told to do so.

## Master and slave Codes
1. OBCm--SPI--Anirudh contains the master code for SPI communication.
2. OBCs--SPI--Anirudh contains the slave code for SPI communication.
3. OBCs--EEPROM--Anirudh contains the slave code for reading and writing int EEPROM.

## Problems faced
- **SPI sending garbage value after programming the master**
    - **Solution** :
      _Restart the OBC_
    - **Reason** :
    _We use SPI protocol to program the micro-controller so after programming the OBC the buffer gets partially filled and we get garbage output. Restarting the OBC clears the buffer._

- **Programmer led red while programming the slave.**
    - Solution
     _Erase the master chip first._
