# Ipar4 ESP8266 Accelerometer MPU92-65 9250

## Leírás
Az mpu9250 osztály segítségével könnyen olvashatjuk a szenzor által mért értékeket. A accelerometer.ino fileban található példa a használatára.

A vec3 osztály és i2c-helper haszonos lehet másik projektben is.

### Irodalom
[Standard C++ libary](https://github.com/maniacbug/StandardCplusplus/blob/master/README.md)  
[Board setup](https://www.marginallyclever.com/2017/02/setup-nodemcu-drivers-arduino-ide/)  
[Sensor tutorial](https://lucidar.me/en/inertial-measurement-unit/mpu-9250-and-arduino-9-axis-imu/)  
Pinout:  
![](https://i.pinimg.com/originals/48/98/73/48987376df86cd722862f2275cbdc79e.png)

### Jegyzetek


### Egy tanulmány arduinoval való rezgés mérésről
[Tanulmány](https://www.diva-portal.org/smash/get/diva2:839696/FULLTEXT01.pdf)

Itt analóg szenzorral dolgoznak, ők is eltárolnak valamennyi (512) adatot. És elküldik soroson. Viszont náluk nem korlátozza a sebességet az i2c, így tudnak ms-enként mérni.

### Megjegyzés

#### Arduino oop
Az arduino ide fordítója az összes .ino file-t behúzza és tudunk belőllük függvényeket hívni. Ha osztályt szeretnénk csinálni akkor mindenképp kell .h és .cpp fileokat írni. A .h-kba include guarddal.

#### I2C kommunikáció
Nincs visszacsatolás arról, hogy valóban a szenzorral kommunikálunk, így hibás csatlakozás esetén csupa 0-t olvasunk ki belőle. 



