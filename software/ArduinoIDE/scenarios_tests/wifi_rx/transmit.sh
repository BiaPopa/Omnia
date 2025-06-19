#!/bin/bash

while true; do
  echo -n "test" | socat - UDP-DATAGRAM:192.168.0.115:4210
  sleep 1
done

