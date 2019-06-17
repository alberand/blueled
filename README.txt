
Be careful with connection between programmer Arduino and target Arduino. I had
a lot of corrupted bytes during uploading bootloader/application with ISCP.

Add bluetooth:

    $ sudo bluetoothctl
    $ power on
    $ scan on
    $ # You will see MAC of your HC-05
    $ trust <MAC>
    $ pair <MAC>
    $ # It will ask for pin
    $ # That's all!

Create serial port:

    sudo rfcomm bind rfcomm0 <MAC>

In case of problems with PC's bluetooth module try:

1. power on/off module through the bluetoothctl session
2. sudo rfkill unblock all
