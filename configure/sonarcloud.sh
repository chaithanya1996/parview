#!/bin/bash

export SONAR_SCANNER_VERSION=4.4.0.2170
export SONAR_SCANNER_HOME=$HOME/.sonar/sonar-scanner-$SONAR_SCANNER_VERSION-linux
curl --create-dirs -sSLo $HOME/.sonar/sonar-scanner.zip https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-$SONAR_SCANNER_VERSION-linux.zip
unzip -o $HOME/.sonar/sonar-scanner.zip -d $HOME/.sonar/
export PATH=$SONAR_SCANNER_HOME/bin:$PATH
export SONAR_SCANNER_OPTS="-server"

curl --create-dirs -sSLo $HOME/.sonar/build-wrapper-linux-x86.zip https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
unzip -o $HOME/.sonar/build-wrapper-linux-x86.zip -d $HOME/.sonar/
export PATH=$HOME/.sonar/build-wrapper-linux-x86:$PATH

build-wrapper-linux-x86-64 --out-dir build_wrapper_output_directory cmake --build parbuild/ --config Release

sonar-scanner \
  -Dsonar.organization=chaithanya1996 \
  -Dsonar.projectKey=chaithanya1996_parview \
  -Dsonar.sources=. \
  -Dsonar.login=${SONAR_TOKEN} \
  -Dsonar.projectName=parview \
  -Dsonar.cfamily.build-wrapper-output=build_wrapper_output_directory \
  -Dsonar.host.url=https://sonarcloud.io