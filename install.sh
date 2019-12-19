#!/bin/bash

mkdir -p ~/bin
if [ -d ~/bin/dse ]; then
rm -r ~/bin/dse
fi
cp -R ../dse ~/bin/dse
echo 'export PATH="$HOME/bin:$PATH"'>>~/.bashrc
echo 'export PATH="$HOME/bin/dse:$PATH"'>>~/.bashrc
exec bash
source ~/.bashrc
