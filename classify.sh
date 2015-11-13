#!/bin/bash
./pagemap2 $@ | grep : | awk '$4 > 0' | ./classify.pl
