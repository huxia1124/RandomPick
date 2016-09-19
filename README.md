# RandomPick
Better alternative of picking an item randomly from a set of candidates with pre-defined probability.

Instead of performing an **if** statement for every candidate, I use **std::lower_bound** as a better approach on performance.

```
Preparing 1000 candidates with random probability of being selected...
Picking 100000 random items from 1000 candidates
------------------------- Round 1 -------------------------
[FastRandomPick]         Time Elapsed = 0 Milliseconds
        Designed     Scaled Hits     Actual Hits
           11613           11888             196
            1303            1213              20
            6735            6611             109
            2586            2304              38
            4205            4912              81
[NormalRandomPick]       Time Elapsed = 31 Milliseconds
        Designed     Scaled Hits     Actual Hits
           11613           12312             203
            1303            1395              23
            6735            8067             133
            2586            2365              39
            4205            4185              69


Preparing 2000 candidates with random probability of being selected...
Picking 200000 random items from 2000 candidates
------------------------- Round 1 -------------------------
[FastRandomPick]         Time Elapsed = 31 Milliseconds
        Designed     Scaled Hits     Actual Hits
           10971           12662             105
            9948           12180             101
            9473            8441              70
            3465            3979              33
             715             361               3
[NormalRandomPick]       Time Elapsed = 125 Milliseconds
        Designed     Scaled Hits     Actual Hits
           10971           13265             110
            9948           10250              85
            9473            9406              78
            3465            2773              23
             715            1085               9


Preparing 4000 candidates with random probability of being selected...
Picking 400000 random items from 4000 candidates
------------------------- Round 1 -------------------------
[FastRandomPick]         Time Elapsed = 31 Milliseconds
        Designed     Scaled Hits     Actual Hits
           47192           46833             196
           42212           49461             207
           47339           47550             199
            1011            1194               5
           24118           29151             122
[NormalRandomPick]       Time Elapsed = 469 Milliseconds
        Designed     Scaled Hits     Actual Hits
           47192           46594             195
           42212           42054             176
           47339           51134             214
            1011            1194               5
           24118           24611             103


Preparing 8000 candidates with random probability of being selected...
Picking 800000 random items from 8000 candidates
------------------------- Round 1 -------------------------
[FastRandomPick]         Time Elapsed = 63 Milliseconds
        Designed     Scaled Hits     Actual Hits
           15725           15277              32
           39858           41057              86
           39097           47740             100
           15898           18618              39
           13778            8593              18
[NormalRandomPick]       Time Elapsed = 1766 Milliseconds
        Designed     Scaled Hits     Actual Hits
           15725           17186              36
           39858           52992             111
           39097           42489              89
           15898           19573              41
           13778           15277              32
```
