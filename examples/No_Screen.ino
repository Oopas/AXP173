/**
 * @file No_Screen.ino
 * @author By Oopas
 * @brief  This is AXP173 PMU Simple Test
 * IRQ_PIN 12
 * SDA&SCA hardwareIIC
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "AXP173.h"

/* IIC pin(ESP8266) */
// SCL  5   D1
// SDA  4   D2

AXP173 AXP173_Chip;

void setup()
{

    /* Init Serial */
    Serial.begin(9600); //设置波特率为 115200

    /* Init IIC */
    Wire.begin(); // IIC初始化

    /* Init PMU */
    AXP173_Chip.begin(&Wire); // AXP173 iic初始化(不包含ADC以及电源)
                      // iic.I2C_dev_scan();     //扫描IIC设备地址

}

void loop(){
    printPmuInfo();
    //KeyPressIRQEvent();               //按键中断事件判断
}

void printPmuInfo(){ //需要打印在屏幕上的芯片信息
    /* Get PMU temp info */
    Serial.printf("Temperature: %.2f °C.\n",AXP173_Chip.getAXP173Temp()); //芯片温度

    /* Get VBUS info */
    Serial.printf("VBUS Voltag: %.2f mV.\n",AXP173_Chip.getVBUSVoltage()); //VBUS输入电压
    Serial.printf("VBUS Current: %.2f mA.\n",AXP173_Chip.getVBUSCurrent()); //VBUS输入电流
    Serial.printf("Battery State: %d.\n",AXP173_Chip.isBatExist()); //电池是否存在

    if(AXP173_Chip.isBatExist()){
        //  display.println("Battery :Battery Exist");                         //电池接入状态
        /* Get Battery info */
        Serial.printf("Charging State: %d.\n",AXP173_Chip.isCharging()); //充电状态

        Serial.printf("Bat Voltag: %.2f mV.\n",AXP173_Chip.getBatVoltage()); //电池电压

        Serial.printf("Bat Current: %.2f mA.\n",AXP173_Chip.getBatCurrent()); //电池电流  正为充电，负为放电

        Serial.printf("Battery Level: %.2f %.\n",AXP173_Chip.getBatLevel()); //电池电量百分比显示 （电压检测法，非库仑计算法，充电时会显示100%）

        Serial.printf("Battery Power: %.2f.\n",AXP173_Chip.getBatPower());            //电池瞬时功率

        Serial.printf("Battery Coulomb Input: %.2f.\n",AXP173_Chip.GetBatCoulombInput()); // Get Coulomb charge Data

        Serial.printf("Battery Coulomb Output: %.2f.\n",AXP173_Chip.GetBatCoulombOutput());       //Get Coulomb Discharge Data

        Serial.printf("Battery Coulometer Data: %.2f.\n",AXP173_Chip.getCoulometerData()); // get coulomb val affter calculation
    }
}
