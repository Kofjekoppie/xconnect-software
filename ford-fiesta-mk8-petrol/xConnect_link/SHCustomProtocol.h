/*
                           ______                            __ 
                     _  __/ ____/___  ____  ____  ___  _____/ /_
                    | |/_/ /   / __ \/ __ \/ __ \/ _ \/ ___/ __/
                   _>  </ /___/ /_/ / / / / / / /  __/ /__/ /_  
                  /_/|_|\____/\____/_/ /_/_/ /_/\___/\___/\__/  
                              SimHub Adaptation                        
                          Code modified by: InfoX1337            
    xConnect SimHub Adaptation by InfoX1337 is licensed under GNU GPL 3.0 
    Copyright (C) 2024 InfoX1337
    Contact me at: hi@infox.dev or support@xconnect.cc

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

// MODIFIED NCalc Formula: (paste into simhub "Custom Protocol"). Tested only on BeamNG Drive
/*
format(round([Rpms], 0),'0') + ';' +
isnull(round([SpeedKmh],2),'0') + ';' +
isnull(round([FuelPercent],0),'0') + ';' +
isnull(round([DataCorePlugin.GameRawData.waterTemp], 0)+65, '0') + ';' +
isnull([Gear],'0') + ';' +
isnull([TurnIndicatorLeft],'0') + ';' +
isnull([TurnIndicatorRight],'0') + ';' +
isnull([EngineIgnitionOn],'0') + ';' +
isnull([Handbrake],'0') + ';' +
isnull([ABSActive],'0') + ';' +
isnull([TCActive],'0') + ';' +
isnull([GameRawData.ShowLights],'0') + ';' +
if([CarSettings_RPMShiftLight1] > 0, 1, 0) + ';' +
isnull([DataCorePlugin.GameRawData.light_HighBeam],'0') + ';' +
isnull([DataCorePlugin.GameRawData.Drivetrain.CruiseControl],'0') + ';' +
isnull([GameRawData.light_Fog],'0') + ';' +
isnull([GameRawData.light_Oil],'0') + ';' +
if([GameRawData.wheel_isDeflated_fl] || [GameRawData.wheel_isDeflated_fR] || [GameRawData.wheel_isDeflated_rl] || [GameRawData.wheel_isDeflated_rr], 1, 0) + ';' +
isnull(round([DataCorePlugin.GameData.InstantConsumption_MPG_US],0),'0') + ';' +
isnull([InputStatus.JoystickPlugin.Logitech_G29_Driving_Force_Racing_Wheel_USB_B22],'0') + ';' +
isnull([InputStatus.JoystickPlugin.Logitech_G29_Driving_Force_Racing_Wheel_USB_B21],'0') + ';' +
isnull([InputStatus.JoystickPlugin.Logitech_G29_Driving_Force_Racing_Wheel_USB_B23],'0') + ';' +
isnull([DataCorePlugin.GameRawData.light_LowHighBeam],'0') + ';' 


*/


#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>
float avg1, avg2, avg3, avg4, avg5, avg6, avg7, avg8, avg9, avg10, speed;
String rpmS, speedS, fuel, fuelflowS, tempS, gearS, turnL, turnR, ignitionS, handbrakeS, showLights, shiftLight, highBeams, cruiseControl, ABSS, TCS, parklightS, foglightS, oillightS, tirewarningS, menupluS, menuminuS, okS;
int rpm, temp, fuelflow, blinkerL,  avgcounter,blinkerR, ignition, speedout, brakeApplied, oilWarn, tc, tpms, battWarn, fullBeam, rpmgate, finetune, distance, finetuner, distanceTravelled, gearInd, absLight, arrow, handbrake, gear, counter, foglight, oillight, daynightmode, tirewarning; 
bool handbrakeOn;
class SHCustomProtocol {
private:

public:
	void setup() { // Runs once

	}

	void read() { // Runs on every message sent 
		rpmS = FlowSerialReadStringUntil(';');
    rpm = rpmS.toInt();
    speedS = FlowSerialReadStringUntil(';');
    
    switch(avgcounter){//smooth out the speed signal to make the speedo needle very smooth
      case 1:
      avg1 = speedS.toInt();
      break;
      case 2:
      avg2 = speedS.toInt();
      break;
      case 3:
      avg3 = speedS.toInt();
      break;
      case 4:
      avg4 = speedS.toInt();
      break;
      case 5:
      avg5 = speedS.toInt();
      break;
      case 6:
      avg6 = speedS.toInt();
      break;
      case 7:
      avg7 = speedS.toInt();
      break;
      case 8:
      avg8 = speedS.toInt();
      break;
      case 9:
      avg9 = speedS.toInt();
      break;
      case 10:
      avg10 = speedS.toInt();
      break;
      
    }
    if(avgcounter++ > 5){avgcounter = 1;}
    speed = (avg1 + avg2 + avg3 + avg4 + avg5) / 5;
    //speed = speedS.toInt();
    fuel = FlowSerialReadStringUntil(';');
    tempS = FlowSerialReadStringUntil(';');
    temp = tempS.toInt();
    gearS = FlowSerialReadStringUntil(';');
    if(gearS != "N" || gearS != "R") {
      gear = gearS.toInt();
      gear++;
    } else {
      gear = 0;
    }
    turnL = FlowSerialReadStringUntil(';');
    turnR = FlowSerialReadStringUntil(';');
    ignitionS = FlowSerialReadStringUntil(';');
    handbrakeS = FlowSerialReadStringUntil(';');
    ABSS = FlowSerialReadStringUntil(';');
    TCS = FlowSerialReadStringUntil(';');
    showLights = FlowSerialReadStringUntil(';') + ";";
    shiftLight = FlowSerialReadStringUntil(';');
    highBeams = FlowSerialReadStringUntil(';');
    cruiseControl = FlowSerialReadStringUntil(';');
    foglightS = FlowSerialReadStringUntil(';');
    oillightS = FlowSerialReadStringUntil(';');
    tirewarningS = FlowSerialReadStringUntil(';');
    fuelflowS = FlowSerialReadStringUntil(';');
    fuelflow = fuelflowS.toInt();
    fuelflow = map(fuelflow, 0, fuelflow, 0, 60);
    menupluS = FlowSerialReadStringUntil(';');//these 3 are just for controlling the display with my steering wheel
    menuminuS = FlowSerialReadStringUntil(';');//these 3 are just for controlling the display with my steering wheel
    okS = FlowSerialReadStringUntil(';');///these 3 are just for controlling the display with my steering wheel
    parklightS = FlowSerialReadStringUntil(';');
    String concate = "";
    int p = 0;
    tc = 0x00;
    oilWarn = 0x00;
    if(ignitionS == "1" && rpm < 200 ){
battWarn = 0x01;
    }
    else{
    battWarn = 0x0;}
    absLight = 0x00;
    while(p < showLights.length() + 1) { // This is a parser for the ShowLights raw data from simhub.
      if(showLights[p] == ',' || showLights[p] == ';') {
        p+=2;
        if(concate == "DL_SHIFT") {

        } else if(concate == "DL_TC") {
          tc = B00000010;
        } else if(concate == "DL_OILWARN") {
          oilWarn = B00000100;
        } else if(concate == "DL_BATTERY") {
          battWarn = 17;
        } else if(concate == "DL_ABS") {
          absLight = B01000000;
        } else if(concate == "DL_HANDBRAKE") {
          handbrakeS = "1";
        } else if(concate == "DL_FULLBEAM") {
          highBeams = "1";
        }
        concate="";
        continue;
      }
      concate=concate+showLights[p];
      p++;
    }
    // Custom code for Ford MK8
   /* if(rpm < 0) {
      rpm = 0;
    }
    rpmgate = 96 + (int)(rpm / 500);  // Calculate the gate and cast to int
    finetune = (int)(rpm % 500) / 2;
    if (rpmgate > 115) {
      rpmgate = 115;
    }*/
    rpm = (rpm / 2) + 0x6000;
  /*  int ogSpeed = speed;
    speed  = ( speed / 2.66 ); // for kmph
    finetuner = ((speed * 3) - ogSpeed)*10; // Revisit in future due to inconsistency
    finetuner = finetuner - finetuner%100;    */
    speedout = speed*95;

    if(tirewarningS == "1" && ignitionS == "1"){
      tpms = 0x38;
    }
    else{
      tpms = 0;
    }
    if(turnL == "1") {
      blinkerL = B11111100;
    } else {
      blinkerL = B10111100;
    }
    if(turnR == "1") {
      blinkerR = B00001000;
    } else {
      blinkerR = 0x00;
    }
    if(highBeams == "1" && ignitionS == "1") {
      fullBeam = B00110000;
    } else {
      fullBeam = B00010000;
    }
    if(handbrakeS.toInt() > 1) {
      handbrakeOn = true;
    } else {
      handbrakeOn = false;
    }

    if(ABSS == "1") {
      absLight = B01000000;
    } else {
      absLight = 0x00;
    }

    if(TCS == "1") {
      tc = B00000010;
    }
    /*if(temp == 0 && battWarn == 17) {
      ignition = 0x00;
      battWarn = 0x00;
    } else if(temp != 0) {
      ignition = B01000000;
    }*/
    
    if(ignitionS == "1"){
      if(parklightS == "1"){
        daynightmode = 0x0B;
        if(foglightS == "1"){
          ignition = 0x46;
        }
        else{
        ignition = 0x44;}
      }
      else{
      ignition = 0x40;
      daynightmode = 0x10;
      }
    }
    else{
      ignition = 0x20;
    }

    if(shiftLight == "1") {
      arrow = 100;
    } else {
      arrow = 0;
    }

    if(oillightS == "1"){
      oillight = 0x44;
    }
else{
  oillight = 0;
}
   
	}

	void loop() { // Called once per arduino loop
    opSend(0x591, 0x91, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);

    //Ignition
    opSend(0x3B2, ignition, 0x00, 0x00, daynightmode, blinkerR, 0x00, blinkerL, 0x00);
    // Byte 4 B00000001 means dim, B0000100 means less dim, B0001000 means even less dim B0010000 means full brightness 
    // Last byte: B00000001 fog lights
    // First byte: B01000010 fog light 2, B01000100 means day lights, B01000000 screen on, B10000000 screen off, B01000001 door ajar light

    //Coolant
    opSend(0x156, temp, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00);
    //Byte 1: Temperature

    //Airbag
    opSend(0x04C, 0x00, B01010101, B01010101, 0x00, 0x00, 0x00, 0x00, 0x00);
    //Byte 2&3: 85=All Seatbelts applied (5)

    //Parking Brake (Fusion 2013)
    opSend(0x213, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    if(speed > 5 && handbrakeOn && counter < HANDBRAKE_FLASH_PERIOD) {
      handbrake = B00010000;
      brakeApplied = B11111111;
      counter++;
    } else if(speed > 5 && handbrakeOn && counter < HANDBRAKE_FLASH_PERIOD * 2) {
      handbrake = 0x00;
      brakeApplied = B11111111;
      counter++;
    } else if(counter >= HANDBRAKE_FLASH_PERIOD * 2) {
      counter = 0;
    } else if(handbrakeOn) {
      handbrake = B00010000;
      brakeApplied = 0x00;
    } else {
      handbrake = 0x00;
      brakeApplied = 0x00;
    }
    //Vehicle Alarm + Parking Brake
    opSend(0x3C3, 0x00, B11111111, handbrake, brakeApplied, 0x00, 0x00, 0x00, 0x00);
    //Bytes 1/2: B11111111=Alarm
    //Byte 3: B00010000=Park Brake

    //ABS
    opSend(0x416, 0x0E, 0x00, 0x00, 0x00, 0x00, tc, absLight, 0x00);
    //Byte 6: B00000100=Slow flashing TC, B00000010=Solid TC Light
    //Byte 7: B10000000=Rapid flashing ABS, B01000000=Solid ABS

    //TPMS
    opSend(0x3b4, tpms, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    //Byte 1: 49=Shows Low Tire Pressure Menu, B00000100 shows still tire warning, B00001000 shows flashing tire warning
    //Byte 2: Highlights Front R and L tires
    //Byte 3: Same as above but rear

    //ECU
    opSend(0x421, oilWarn, 0x00, oillight, 0x00, 0x00, 0x00, 0x00, 0x00);
    //Byte 1: B00001000=Flashing CEL, B00000100=Solid CEL

    //Charging System
    opSend(0x42C, 0x00, battWarn, 0xA6, 0x00, 0x00, 0x00, 0x00, 0x00);
    //Byte 2: 17=Charge Light (No Message on Screen)

    //Power Steering
    opSend(0x877, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

    //Language?
    opSend(0x191, 65, 17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    //Byte 1: Units; 65=KM and CELSIUS
    //Byte 2: 17=English, 35=German

    //Outside Temp
    opSend(0x3B3, 0x00, 0x00, 0x00, 0x00, 125, 0x00, 0xFF, 0x00);
    //Byte 5: Outside Temp Value -> 125=22°C

    //Front Camera
    opSend(0x3D8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

    //Tractioncontrol
    opSend(0x46A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

    //High Beam + Auto Hed
    opSend(0x46B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, fullBeam);
    //Byte 8: B00110000=High Beam
    
    // Rear Park Pilot
    opSend(0x3AA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); 

    //trans
   // opSend(0x431, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //message from the transmission. For some reason, enabling this line causes occasional glitches, not sure why. Might be my setup (32U4 + MCP2515)

    // Reset autoStop system
    opSend(0x166, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

    // Reset MyKey system
    opSend(0x432, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); 

    // RPM
    //opSend(0x42F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, rpmgate, finetune);
    opSend(0x42F, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, highByte(rpm), lowByte(rpm));
    // Speedometer 
    opSend(0x202, 0x11, 0x00, 0x00, 0x00, distance, distance, highByte(speedout), lowByte(speedout));
    
    if(distance++ > 200) { // Make sure the distance doesnt get out of range
      distance = 0;
    }

    // Gears, show upshift and downshift symbol
    if(arrow == 100) {
      gearInd = (gear+1)*10;
      if(gear >= 7) { // Disable the gear selector number when gear is 6 or more, since the cluster only supports 6 gears
        gearInd = 0;
      } else if(gear >= 5) {
        gearInd += 10;
      }
      
    }
//disabling this part of the code made the gear indicator work properly for me		
     /*else if(rpm > 6500 && gear > 1) {
      gearInd = (gear+1)*10;
      if(gear >= 7) { // Disable the gear selector number when gear is 6 or more, since the cluster only supports 6 gears
        gearInd = 0;
      } else if(gear >= 5) {
        gearInd += 10;
      } 
      arrow=100;
    } else if(rpm < 700 && battWarn == 0x00) {
      gearInd = (gear)*10;
      if(gear >= 8) { // Disable the gear selector number when gear is 6 or more, since the cluster only supports 6 gears
        gearInd = 0;
      } else if(gear >= 6) {
        gearInd += 20;
      } else if(gear >= 5) {
        gearInd += 10;
      } 
      arrow = 150;
    } else {
      arrow = 0;
    }*/
    if(distance % 10 == 0) {
      distanceTravelled += (int)(speed/5);
    }
    if((int)(distanceTravelled / 500) > 100) {
      distanceTravelled = (int)(distanceTravelled / 500);
    }
    // Odometer0x179
    opSend(0xF979, arrow, 0, 0, 0, 200, distanceTravelled, gearInd, fuelflow);//fuelflow kinda needs to be looked at, seems not as accurate as it should be. BeamNG 0.33 update changed this behavior as well. Cluster does react to writing a value in this byte

    // Button events, modified these to work with my specific setup, G29 steering wheel, so the cluster's display can be controlled with the red dial and the enter button.
    if (okS == "1" ) {//ok
      opSend(0x082, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    } else if (menupluS == "1") {//plus
      opSend(0x082, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    } else if (menuminuS == "1") {//min
      opSend(0x082, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    } else if (digitalRead(OK_BTN_PIN== LOW)) {//menu
      opSend(0x082, 0x00, 255, 255, 0x00, 0x00, 0x00, 0x00, 0x00);
    } else if (digitalRead(BACK_BTN_PIN) == LOW) {//back
      opSend(0x082, 0x00, 76, 0, 0x00, 0x00, 0x00, 0x00, 0x00);
    } else {
      opSend(0x082, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    }

	}

	// Called once between each byte read on arduino, do not add any code here, unless you know what you are doing.
	void idle() {}
};

#endif
