#!/bin/bash

# if a debug window exists delete it
if tmux list-windows | grep -q "debug"; then
    tmux kill-window -t "debug"
fi

# Create a debug window
tmux new-window -n "debug"

# Get number of windows
number_of_windows=$(tmux list-windows | wc -l)

# Split the new window horizontally
tmux split-window -t $number_of_windows -h

# Send commands to the new panes in the new window
tmux send-keys -t $number_of_windows.1 "tty" Enter
sleep 1 # Necessary
device=$(tmux capture-pane -t $number_of_windows.1 -p )


tmux send-keys -t $number_of_windows.1 "clear" Enter
dev=$(echo $device | awk '/dev/ { print $5 }')

rm .gdbinit.gdb
commands=("tui enable" "break main" "run < $dev > $dev")
for cmd in "${commands[@]}"; do
    echo $cmd >> .gdbinit.gdb
done

tmux send-keys -t $number_of_windows.0 "gdb --command .gdbinit.gdb ./stp" Enter

