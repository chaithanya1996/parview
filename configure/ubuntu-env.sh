#!/bin/bash

apt-get update -y -q && \
    apt-get install -y -q --no-install-recommends \
      build-essential \
      libboost-all-dev \
      cmake && \
    apt-get clean && rm -rf /var/lib/apt/lists*
