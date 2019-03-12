# lem-in
⚙ ︎Optimized max flow solver and router for minimizing movement time of a given number of agents through a graph.

## Purpose
The purpose of this program is to take specifically formatted input files describing large maps of interconnected rooms, then find optimized paths to move a specified number of agents through the map in the shortest number of turns. An agent can only move across one link per turn and each room can only be occupied by one agent at a time. Start and end rooms are marked in the map, and there are no limits to how many agents can leave the start room or enter the end room per turn as long as only one agent moves across a single link in a turn.

## Installation
`git clone --recurse-submodules https://github.com/jacksonwb/lem-in.git; cd lem-in; make`

## Input Map
The map map will be in the following format
```
# of agents
room section
name of room x y
link section
room1-room2
```

`##start` indicates that the room on the following line is the start room

`##end` indicates that the room on the following line is the end room

Rooms with errors such as no rooms, no links, no ant number, invalid room positions, and no viable paths will be rejected with an error.

The following input describes the map below:
```
4
3 2 2
##start
start 4 0
##end
end 4 6
4 0 4
1 4 2
2 4 4
5 8 2
6 8 4
start-1
3-4
2-4
1-5
6-5
end-6
1-2
2-end
3-start
```

```
[start]
  /  |
 [3] [1]--[5]
 /    |    |
[4]--[2]  [6]
      |   /
     [end]
```

## Output
The output describes the movement of agents through the map.
A movement is of the form `L[agent number]-[room name]`, with all movements in a turn occuring on a line.

The following outpute describes movement through the above map:
```
L1-3 L2-1
L1-4 L2-2 L3-3 L4-1
L1-2 L2-end L3-4 L4-5
L1-end L3-2 L4-6
L3-end L4-end
```

## Usage
A map is read from STDIN
`./lem-in [-qld] < map.in`

The `-q` option suppresses the map in the output

The `-l` option also prints the number of lines used to complete the output

The `-d` option prints debugging information

