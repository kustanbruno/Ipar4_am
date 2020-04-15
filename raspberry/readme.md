# Raspberry pi MPU9250

[i2c raspberryn](https://www.instructables.com/id/Raspberry-Pi-I2C-Python/)  
 
*Nekem elsőre nem működött az i2c mert a /dev/i2c-0-n kereste az i2c-t az i2cdetect, de egy symlinkkel átverhető*  
Nálam ennyi volt
```
sudo ln -s /dev/i2c-1 /dev/i2c-0
```

Két i2c van a raspberryn, nekem valamiért nem látszott a 0 -s

### Pinout
![](https://pinout.xyz/resources/raspberry-pi-pinout.png)

