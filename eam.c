#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <mach/mach_port.h>
#include <mach/mach_interface.h>
#include <mach/mach_init.h>

#include <IOKit/pwr_mgt/IOPMLib.h>
#include <IOKit/IOMessage.h>

io_connect_t  root_port; // a reference to the Root Power Domain IOService

void
MySleepCallBack( void * refCon, io_service_t service, natural_t messageType, void * messageArgument )
{
    switch ( messageType )
    {
        case kIOMessageSystemWillSleep:
            system("/usr/sbin/diskutil unmount /Volumes/External");

            IOAllowPowerChange( root_port, (long)messageArgument );
            break;

        case kIOMessageSystemHasPoweredOn:
       	    system("/usr/sbin/diskutil mount disk4s2");

            IOAllowPowerChange( root_port, (long)messageArgument );
            break;

        default:
            break;
    }
}

int main( int argc, char **argv )
{
    IONotificationPortRef  notifyPortRef;
    io_object_t            notifierObject;
    void*                  refCon;

    root_port = IORegisterForSystemPower( refCon, &notifyPortRef, MySleepCallBack, &notifierObject );
    if ( root_port == 0 )
    {
        printf("IORegisterForSystemPower failed\n");
        return 1;
    }
    // add the notification port to the application runloop
    CFRunLoopAddSource( CFRunLoopGetCurrent(), IONotificationPortGetRunLoopSource(notifyPortRef), kCFRunLoopCommonModes );
    CFRunLoopRun();
    return (0);
}
