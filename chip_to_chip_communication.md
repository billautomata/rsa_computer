2. input - interrupt signal

5. input - chip addressing A
6. input - chip addressing B

7. input / output - data bus
8. input / output - data bus
9. input / output - data bus
10. input / output - data bus
11. input / output - data bus
12. input / output - data bus
13. input / output - data bus
14. input / output - data bus

15.
18.
19.

```
interrupt function
  read chip address pins
  does the value of the address pins match mine?
  (yes)
    read the state of the pins
    shift the values into the buffer at the current index
    increment the index
    if the index == max, reset the index
```
