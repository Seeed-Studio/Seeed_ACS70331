Grove current sensor ACS70331
=================================  

![MPR121](https://github.com/Jenkinlu001/Grove_current_sensor_ACS70331/ACS70331_module.jpg)  


Introduction of sensor
----------------------------  
The current sensor is a direct current measuring no more than 2.5A.This can be used to measure system power consumption, realize current monitoring and so on.The current sensor outputs an analog voltage that varies linearly with current.

***
Usage:
==========  
Download all the source files. There are two examples for user to use.
>1. examples/Seeed_ACS70331_basis_Demo.ino ,open it in arduino IDE. Compile and download and run it on a arduino board.
>2. If you own an OLED, you can connect it to work with it.Open examples/Seeed_ACS70331_OLED_Demo.ino in arduino IDE. Compile and download and run it on a arduino board.

****
Notice:
=========
>1. This examples/Seeed_ACS70331_basis_Demo.ino is just a simple display demo by the serial port monitor.
>2. When there is no load, the display is not 0 and the error is large. You need to calibrate according to the following steps.
    1. The value of the sensorValue is read when there is no current load.
    2. Print out the initial voltage and assign it to the Vref.
>3. The maximum range is 2.5A
    Get more detail from **doc/ACS70331-Datasheet.pdf** 



***
This software is written by Jenkin for seeed studio<br>
Email:zhengxing.lu@seeed.cc
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>
****
Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.
****
Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>