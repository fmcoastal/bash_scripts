#!/bin/bash


GREEN=$'\e[32m'
RED=$'\e[31m'

NORMAL=$'\e[0m'


sync 

CHECK=$(mount |grep sdb)

if [ "$CHECK" == "" ] ; then
   echo $GREEN
   if [ ! -d /mnt/p1 ] ; then
	echo " creeate /mnt/p1 "
	mkdir -p /mnt/p1
   fi
   if [ ! -d /mnt/p2 ] ; then
	echo " creeate /mnt/p2 "
	mkdir -p /mnt/p2
   fi

   echo "+++++ MOUNT DRIVE +++++"
   mount /dev/sdb1 /mnt/p1
   mount /dev/sdb2 /mnt/p2
else
   echo $RED
   echo "----- UNMOUNT DRIVE -----"
   sync
   umount /mnt/p1
   umount /mnt/p2
   sync
   echo " delete /mnt/p1 "
   rm -rf /mnt/p1
   echo " delete /mnt/p1 "
   rm -rf /mnt/p2
fi
echo $NORMAL
echo "mount |grep sdb"
mount | grep sdb
