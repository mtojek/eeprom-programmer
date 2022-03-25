# eeprom-programmer
EEPROM programmer based on Arduino

This repository contains Kicad schematics and .ino source files to build the EEPROM programmer using Arduino UNO R3. If you are following the Ben's Eater course to [build a 6502 computer](https://eater.net/6502), you will see that Ben uses a [TL866 II Plus](https://eater.net/6502) model, but it is possible to program memory chips using this homebrew board.

## Sample output

Check Arduino serial monitor to see memory content:

```
Reset
Run!
0000: a9 ff 8d 02 60 a9 50 8d    00 60 6a 8d 00 60 4c 0a    ⸮⸮⸮`⸮P⸮ 
0010: 80 00 00 00 00 00 00 00    00 00 00 00 00 00 00 00    ⸮
0020: 00 00 00 00 00 00 00 00    00 00 00 00 00 00 00 00    
...
7fc0: 00 00 00 00 00 00 00 00    00 00 00 00 00 00 00 00    
7fd0: 00 00 00 00 00 00 00 00    00 00 00 00 00 00 00 00    
7fe0: 00 00 00 00 00 00 00 00    00 00 00 00 00 00 00 00    
7ff0: 00 00 00 00 00 00 00 00    00 00 00 00 00 80 00 00    
```

## Kicad preview

<p float="left">
  <img src="/screenshots/pcb-3d-viewer.png?raw=true" height="256px">
  <img src="/screenshots/pcb-layout.png?raw=true" height="256px">
</p>

## Photos

<p float="left">
  <img src="/photos/1.jpg?raw=true" width="256px">
  <img src="/photos/2.jpg?raw=true" width="256px">
  <img src="/photos/3.jpg?raw=true" width="256px">
</p>
