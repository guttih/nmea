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
    **      ( 4 )         ( 3 )      **               **      ( 3 )         ( 4 )      **     
   *                                   *             *                                   *     
  *                                     *           *                                     *    
 *                                       *         *                                       *   
 *                 ( 5 )                 *         *                 ( 5 )                 *   
 *                                       *         *                                       *   
  *                                     *           *                                     *    
   *                                   *             *                                   *     
    **      ( 2 )         ( 1 )      **               **      ( 1 )         ( 2 )      **      
      **                           **                   **                           **        
        ***                      ***                      ***                      ***                   
           ****     |_|     ****                             ****     |_|     ****                        
             ******************                               ******************                            
```

**Legend:**

| Pin | Color | Standard Name | Typical NMEA 2000 Role |
| --- | ----- | ------------- | ---------------------- |
| 1   | brown |               | V+ (12 V power)        |
| 2   | white |               | CAN‑L (Net‑C)          |
| 3   | black |               | V– (Ground)            |
| 4   | blue  |               | CAN‑H (Net‑H)          |
| 5   | gray  |               | Shield / Drain         |


### 🔌 Expected Voltage Levels

Assuring oneself of which pin is which is important — especially when you're working with an unfamiliar cable or connector.
One reliable way to verify the pinout is by measuring voltage levels with a multimeter while the NMEA 2000 network is powered.

| Between Pins      | Expected Voltage | Description                                       |
| ------------------| ---------------- | ------------------------------------------------- |
| V+      ↔  V-     | \~12V DC         | Bus supply voltage                                |
| CAN\_H  ↔  CAN\_L | \~1–2V DC        | Differential CAN signal (fluctuates with traffic) |
| CAN\_H  ↔  V-     | \~2.5–3.5V DC    | CAN High line idle voltage                        |
| CAN\_L  ↔  V-     | \~1.5–2.5V DC    | CAN Low line idle voltage                         |
| Shield  ↔  V-     | 0V               | Should be 0V (chassis/earth reference)            |


#### Measured Voltage

I think there is no device on the bus, so maybe we need to experiment some more with the bus

| Over Vires    |  Measured Voltage  | Guesses after measurements |
| ------------- | ------------------ |                            |
| Black ↔ Gray  | \~0V DC            |                            |
| Blue  ↔ Black | \~2.352V DC        |                            |
| Blue  ↔ Gray  | \~2.25V DC         |                            |
| White ↔ Black | \~0V DC            |                            |
| White ↔ Gray  | \~1V               |                            |
| Brown ↔ Black | \~0V               |                            |