# nmea





# 5 Wire NMEA 2000 Pinout connector

This pin mapping is based ont the male connector of a 5-wire NMEA 2000 cable, which because we have colored wires and 
can do a connetivity test on that, then we just connected those wires to a T-connector, which will allow us to do a 
connectivity test for the female connector as well.



```
              ****************                                 *****************               
           ****              ****                           ****               ****                 
        ***     (  FEMALE  )    ***                       ***      (   MALE   )    ***               
      **                           **                   **                            **       
    **       ( 4 )        ( 3 )      **               **       ( 3 )        ( 4 )      **     
   *                                   *             *                                   *     
  *                                     *           *                                     *    
 *                 ( 5 )                 *         *                 ( 5 )                 *   
 *                                       *         *                                       *   
 *                                       *         *                                       *   
  *                                     *           *                                     *    
   *                                   *             *                                   *     
    **       ( 2 )        (  1 )     **               **       ( 1 )        ( 2 )      **      
      **                           **                   **                           **        
        ***                      ***                      ***                      ***                   
           ****     |_|     ****                             ****     |_|     ****                        
             ******************                               ******************                            
```

**Legend:**

| Pin | Color | Standard Name | Description          |
| --- | ----- | ------------- | -------------------- |
| 1   | brown |               | Shield / drain wire  |
| 2   | white |               | CAN Low (data)       |
| 3   | black |               | CAN High (data)      |
| 4   | blue  |               | DC negative (Ground) |
| 5   | gray  |               | DC positive (+12V)   |


### 🔌 Expected Voltage Levels

Assuring oneself of which pin is which is important — especially when you're working with an unfamiliar cable or connector.
One reliable way to verify the pinout is by measuring voltage levels with a multimeter while the NMEA 2000 network is powered.

| Between Pins                      | Expected Voltage | Description                    |
| --------------------------------- | ---------------- | ------------------------------ |
| V+      ↔  V-     | \~12V DC      | Bus supply voltage                                |
| CAN\_H  ↔  CAN\_L | \~1–2V DC     | Differential CAN signal (fluctuates with traffic) |
| CAN\_H  ↔  V-     | \~2.5–3.5V DC | CAN High line idle voltage                        |
| CAN\_L  ↔  V-     | \~1.5–2.5V DC | CAN Low line idle voltage                         |
| Shield  ↔  V-     | 0V            | Should be 0V (chassis/earth reference)            |


