# GPS Tracker
This program sets up the UART interface for the GPS sensor and creates a task that continuously reads data from the UART interface.

To parse the GPS data and extract the coordinates, we will need to analyze the NMEA sentences that the GPS sensor sends over UART. NMEA sentences contain various fields that provide information about
 the GPS location, time, speed, etc.

Here is an example code that shows how to parse the GGA (Global Positioning System Fix Data) sentence and extract the latitude, longitude, and altitude