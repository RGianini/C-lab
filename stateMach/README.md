| State / Event/ Next State | Interface nok | Interface ok | Pckt RX ok | Pckt RX nok | Pckt RX noAnsw |
|---------------------------|---------------|--------------|------------|-------------|----------------|
| 1. Link Down              |       1       |       2      |      1     |      1      |        1       |
| 2. Send Start             |       1       |       -      |      3     |      2      |        2       |
| 3. Send config            |       1       |       -      |      4     |      3      |        2       |
| 4. Send Keep Alive        |       1       |       -      |      4     |      2      |        2       |
