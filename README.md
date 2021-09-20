# Smart-Farmer-s-Assistant
We are a group of students from VIT,Vellore who worked on a project assisting farmers. In our work we have integrated the basic but very strongly needed values available from the farms to help the farmers with their farming to the maximum extent as they have the values stored lively and they can take informed decisions hereafter instead of believing in the age old wisdoms of nature and climate which are actually changing as time goes on.

Our prototype is so simple to use and easily upgradable to even bigger farms. Our website is very easy to use and graphical data shown can be interpreted by anyone and
easily understood. We have used simple hardware components to make the product cheap so that it is affordable to everyone. We have given option to know the weather details of the given location also using an API.

# About the System
There are 3 sensors used in this project namely, DHT11 sensor, Ultrasonic sensor, and Soil moisture sensor. 
All sensors are connected to the Arduino UNO board together with the help of bread board and jumpers. 
DHT11 and ultrasonic sensors are digital sensors and soil sensor is an Analog sensor and thus they are connected to their respective pins in the Arduino. 
Then an LED is connected to a digital pin to activate it when the temperature is more than 80oF and the soil moisture is less than 40% which indicates the irrigation system of the farm. 
Then 2 digital pins are connected to NodeMCU for serial communication transmission and reception.
The data from Arduino is received serially continuously by the NodeMCU. 
The Firebase Host ID and authorization key is taken from the Google Firebase database that we have created and
used for sending the values received by the board to their respective variables in the firebase.
The real time collected here is sent to the website to be displayed graphically. The code is
uploaded to NodeMCU using Arduino IDE.

We also applied a machine learning algorithm called Polynomial regression to a dataset whose features are parameters of soil and the output is the yield based on the parameters of soil recorded. 
