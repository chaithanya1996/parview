#!/bin/bash

apt-get update -y -q && \
    apt-get install -y -q --no-install-recommends \
      libboost-all-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists*
