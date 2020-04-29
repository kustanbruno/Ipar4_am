# Ipar4 ESP8266 Accelerometer MPU92-65 9250

## Leírás
Az mpu9250 osztály segítségével könnyen olvashatjuk a szenzor által mért értékeket. A accelerometer.ino fileban található példa a használatára.

A vec3 osztály és i2c-helper haszonos lehet másik projektben is.

### Irodalom
[Standard C++ libary](https://github.com/maniacbug/StandardCplusplus/blob/master/README.md)  
[Board setup](https://www.marginallyclever.com/2017/02/setup-nodemcu-drivers-arduino-ide/)  
[Sensor tutorial](https://lucidar.me/en/inertial-measurement-unit/mpu-9250-and-arduino-9-axis-imu/)  
[Sensor Datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf)  
Pinout:  
![](https://i.pinimg.com/originals/48/98/73/48987376df86cd722862f2275cbdc79e.png)

### Jegyzetek


### Egy tanulmány arduinoval való rezgés mérésről
[Tanulmány](https://www.diva-portal.org/smash/get/diva2:839696/FULLTEXT01.pdf)  
Itt analóg szenzorral dolgoznak, ők is eltárolnak valamennyi (512) adatot. És elküldik soroson. Viszont náluk nem korlátozza a sebességet az i2c, így tudnak ms-enként mérni.  

[NTP lib](https://lastminuteengineers.com/esp8266-ntp-server-date-time-tutorial/)  

### Megjegyzés

#### Arduino oop
Az arduino ide fordítója az összes .ino file-t behúzza és tudunk belőllük függvényeket hívni. Ha osztályt szeretnénk csinálni akkor mindenképp kell .h és .cpp fileokat írni. A .h-kba include guarddal.

#### I2C kommunikáció
Nincs visszacsatolás arról, hogy valóban a szenzorral kommunikálunk, így hibás csatlakozás esetén csupa 0-t olvasunk ki belőle. 



#### Sebességproblémák
A szenzor I2C-n 400Khz-el érhető el. Spi-n 1Mhz-el.
Jelenleg ESP8266 -al átlagosan 0.56ms ESP32-vel 0.4ms körüli gyakorisággal tudunk mérni.

Az i2c kommunikációt kiiktatva csak a láncoltlistát feltöltve, 0.01ms körüli gyakoriság jön ki, így valószínűleg nem az adattárolás a szűk keresztmetszet.


Kiválasztandó boardok:  
8266  NodeMcu1.0
esp32 


#### A yield() függvény  
Az esp-ben van beépítve egy watchdog, ami újraindítja a rendszert, ha hosszab ideig tart a loop. Ezt nem érdemes kikapcsolni. Ehelyett a hosszabb műveletünkben hívjuk meg a yield() függvényt lehetőleg minél gyakrabban.