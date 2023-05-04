# "Fixing" the Disk not Ejected Properly issue on OSX
<img src=https://user-images.githubusercontent.com/53486597/236287886-358360f5-456a-43bc-8463-73ef9b191023.png width="300" height="600">

This code is based on the following answer on Stack Overflow: https://stackoverflow.com/a/66686784 - I just changed the system() and cleaned up a few things.

It "fixes" the "Disk not Ejected Properly" issue on OSX. I use quotes because this isn't a permanent fix, I haven't patched OSX or anything of that sort. It's just an application that listens for OSX going to sleep and waking up and runs a system() call. This is extremely simple and rudimentary. It uses `kIOMessageSystemWillSleep` and `kIOMessageSystemHasPoweredOn`.

I really should be passing in the volume to eject & remount as command line arguments to the binary, or as a confgiuration. It is hardcoded for now. Change/Update the volume mount & disk in the source code to reflect your external disk.

Compile as follows:
```
gcc -o eam -framework IOKit -framework Cocoa eam.c
```
Run as follows:
```
./eam
```

Put your machine to sleep and then wake it up and you'll see similar output to the following:
```
☹  ./eam
Volume External on disk4s2 unmounted
Volume External on disk4s2 mounted
```

You may want to add a cron to ensure the binary is always running. If I get more time I'll add steps on how to do that.
