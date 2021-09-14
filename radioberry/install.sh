sudo modprobe -r radioberry
sudo cp ./radioberry.ko /lib/modules/$(uname -r)/kernel/drivers/sdr/.
sudo cp ./radioberry.rbf /lib/firmware/.
sudo modprobe radioberry
sudo chmod 666 /dev/radioberry

