```mermaid
flowchart LR
 SW0
 SW1
 SW2
 OUT
 AND1(AND)
 AND2(and)
 OR1(or)
 SW0 & SW1 --> AND1
 SW1 & SW2 --> AND2
 AND1 & AND2 --> OR1
 OR1-->OUT
```


| SW0  | SW1  | SW2  | OUT  |
| ---- | ---- | ---- | ---- |
| 0    | 0    | 0    | 0    |
| 1    | 0    | 0    | 0    |
| 0    | 1    | 0    | 0    |
| 1    | 1    | 0    | 1    |
| 0    | 0    | 1    | 0    |
| 1    | 0    | 1    | 0    |
| 0    | 1    | 1    | 1    |
| 1    | 1    | 1    | 1    |

