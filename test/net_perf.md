## 1. net traffic
## 1.1 basic data
- no load  
client ping server , run 2min
```
TTL=55 time=56ms  
126 packets transmitted, 125 received, 0% packet loss, time 125153ms  
```

- add load   
all data 2326row   
1s per row, 2326s=40min

| item | value |  
| -- | -- |  
| max_rate  | 206.10Mbps |   
| min_rate | 0Mbps |    
| avg_rate |  98.8Mbps |    
| max_RTT | 592ms |    
| min_RTT | 60.6ms |   
| avg_RTT | 269.4ms  |
| max_pkt_sent |  17690pkt |   
| min_pkt_sent | 0pkt |   
| avg_pkt_sent | 8481.52pkt |   
| max_pkt_snt_loss_rate | 4960.24% |   
| min_pkt_snt_loss_rate | 0%  |  

## 1.2 percentile  
| item | value |  
| -- | -- |
| p50_pkt_snt_loss_rate | 1.281% |   
| p60_pkt_snt_loss_rate | 3.5096% |   
| p65_pkt_snt_loss_rate | 13% |    
| p70_pkt_snt_loss_rate | 61% |  
| p80_pkt_snt_loss_rate | 86.86%  |  
| p90_pkt_snt_loss_rate | 171.519% |  
| p95_pkt_snt_loss_rate | 272% |  
| p99__pkt_snt_loss_rate | 624% |


## 1.3 percentile error  
- 624% analysis  

| snt  |	loss 	|	time_line(s) | if error |
| -- | --| -- | -- |
|98	|		0 	|		1 | -|
|2905|	8195 | 		2|- |  
| 13261 |	57 |	3 | - |   
| 1270	|	7938 | 4 | error occurred |  
| 11980 | 11 | 5  | -|   
| 12936 | 60 | 6 | - |  	

- 4960.24% analysis  

| snt  |	loss 	|	time_line(s) | if error |
| -- | --| -- | -- |  
| 13223 | 49  | 1 | - |  
| 8872 | 601 | 2 | - |  
| 165 | 8234 | 3 | error occurred |  
| 16142 |  32 | 4 | - |

## 2. time line graphic
from 				to  
client	=>	server
10s内UDT大的波动为3次，其中一次将为0  
when UDT is running，
client  ping 	server   
time= 423ms, 346ms, 356ms, 55.4ms, 146ms, 284ms  
after udt stoped  transferring data,  
client ping erver  
time = 55ms  
```
 Net traffic(MB/s)
  ^  
  |_ 31.5   
  | 				   ''  
  |_max_ _ _ _ _ _ _ _'_ ._ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ '_'_ _ _ _ _ _ _   
  |					 '   '									   '	'   
  |_ 15.7 ' .   	.     .       '		  ''  ''   '''		  '		  ' 	 '.   
  |           '    . 	  '      '  '' . '  '	'.'			 '			'''   
  |			   '  . 	  '     '			 ''		 ''		.   
  | 			'' 	   	   '   '					  '.  '   
  |-----------|-----------|-..'---------|-----------|----.'-------|-----------|----> time(s)
  60 		 50 		 40 			30 	 		 20  		 10     	  0
```

## 3. env  
## 3.1 Hardware and OS  
```
CPU core:8C(8 threads)  
CPU type:Intel(R) Core(M)i7-7700 cpu@3.65GHz 64 bit  
Mem:25GB  
```
## 3.2 Runtime  
20200725 13:54 client start run

| PID	| %cpu | %Mem	| Net-traffic |  	 
| -- | -- | -- | -- |   
| client | 2.7%~3.0%	| 0.1% | 2.2Mbps~170Mbps  |
