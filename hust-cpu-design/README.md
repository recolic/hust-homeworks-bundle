# FOR main.circ

1. main.circ is the working circuit. Use this circ.

# working circuits:

`P` means "passing educoder.net", `W` means "working, runs benchmark correctly", `N` means "can not run benchmark correctly", `X` means "untested".

|         | default REGFILE (RisingEdge) | FallingEdge REGFILE | HACKED REGFILE (RisingEdge) |
| -----   | ---------------------------  | ------------------- | -------------- |
| 单周期MIPS | PW | X | N |
| 理想流水线 | PW | X | X |
| 气泡流水线 | N  | W | PW |
| 重定向流水线 | W | W | PW |



