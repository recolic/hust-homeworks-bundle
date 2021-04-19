#!/bin/bash
cat main.circ | sed "s|$(pwd)/||g" | xclip -sel c

