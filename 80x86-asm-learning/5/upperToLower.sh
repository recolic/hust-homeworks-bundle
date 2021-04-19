#!/bin/sh

tr '[:upper:]' '[:lower:]' < origin_data.inc > /tmp/.d.inc
mv /tmp/.d.inc origin_data.inc

tr '[:upper:]' '[:lower:]' < origin_code.inc > /tmp/.c.inc
mv /tmp/.c.inc origin_code.inc
