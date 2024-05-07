#!/bin/bash

mkdir tests_out
while true; do
    timestamp=$(date +%s)
    ./raytracer -t 14 > tests_out/test_${timestamp}.ppm
done