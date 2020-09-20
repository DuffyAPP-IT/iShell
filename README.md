# iShell
A basic wrapper for iLibX v2 - interface with your jailbroken device with ease!

./iShell

-send	localfile.txt /myfiles/
Send a local file from the macOS Host to the connected device.

-fetch	/myfiles/remote.txt nowlocal.txt
Fetch a remote file on the connected device and transmit to local storage.

-mkdir	/myfiles/newdirectory
Create a new directory of your choosing on the connected device.

-ecid	(no args required)
retrieve the ECID of the connected device.

-shsh	(no args required)
Uses tsschecker to retrieve shsh2 blobs for the connected device.

-c		COMMAND
Execute a custom command of your choosing on the connected device.
