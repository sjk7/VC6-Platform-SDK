Make a NM call using X224 stack:
---------------------------------
1. Run the application on both machines.
2. Select the X224 radio button
3. Select which machine is going to listen and which machine is going to connect
4. Enter to the machine that is going to connect, the machine name 
   or ip address of the machine that is listenning (the machine that is listenning 
   completes its name automatically)
5. Click connect on the machine that is going to connect (the other
   machine is already listenning)
6. The Call button should be enabled (it was graying out till now) or you get an error
   if the connection has not been established
7. Make the NM call now using the connection that you just created 


Make a NM call using the PSTN stack:
------------------------------------
Connect the two machines using a null modem cable
(verify that the connection is ok by using rterm)
(Load NM (this is not necessary))

SDK application to SDK app
------------------
1. Run the application on both machines
2. On one side select PSTN, Listen and choose the com port you are going to use
3. On the other side select PSTN, Connect and enter the com port you are going to use
   and press the Connect button (the connect button must be pressed first 
   on the connect side)
4. Press the Connect button on the listenning side too
5. The Call button should be enabled (it was graying out till now) or you get an error
   if the connection has not been established
7. Make the NM call now using the connection that you just created 

NM2.11 calls the SDK app
------------------------
1. Unselect Tcp/ip protocol and select null modem protocol on the 2.11 side. 
   Go to COM properties from Tools->Options->Protocols and select speed 
   19200bps, 8 data bits, no parity, stop bits 1 and no flow control
2. Call "com1" or the port you use from NM2.11 using null modem first.
3. On the SDK application select PSTN, Listen and press the Connect button
4. Accept the incoming call on the SDK application side 

The SDK application calls NM2.11
------------------------
1. Unselect Tcp/ip protocol and select null modem protocol on the 2.11 side. 
   Go to COM properties from Tools->Options->Protocols and select speed 
   19200bps, 8 data bits, no parity, stop bits 1 and no flow control
2. On the SDK application select PSTN, Connect enter the com port you are using 
   and press the Connect button
3. Call "com1" or the port you use from NM2.11 using null modem.
4. Press the Call button on the SDK application and accept the incoming call to the 2.11 side


If you want to have conferences with more than 2 machines run multiple instances
of the SDK application