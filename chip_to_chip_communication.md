1. input - interrupt signal
2. input - chip addressing A
3. input - chip addressing B
4. input / output - data bus
5. input / output - data bus
6. input / output - data bus
7. input / output - data bus
8. input / output - data bus
9. input / output - data bus
10. input / output - data bus
11. input / output - data bus
12. input - data bus addressing
13. input - data bus addressing
14. input - data bus addressing
15. input - operation addressing
16. input - operation addressing

```
interrupt function
  am I being addressed (?)  // read chip addressing pins
    (yes)
    what operation is being performed (?)  // read the operation addressing pins
      { binary read }
        read word on data bus pins
        read word on data address pins
        shift data word to address
        OR data word into buffer
      {/binary read }
      { binary write }
        is the current index in bounds (?)
          (yes)
          set the current index on the data address pins
          increment the current index
          extract the byte from the buffer
          write data word on data bus pins
          (no)
          increment operation counter
      {/binary write }
    (/yes)
```
