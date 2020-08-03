F=$@
SF=$0
if [ "$F" = "" ]; then
	echo 'usage: '$SF' filename'
	exit	
fi
echo 'input data file name '$F
RF='sum.txt'
echo 'result output to file '$RF
ln=`wc -l $F | awk -F ' ' '{print $1}'`
echo 'all data '$ln' row'
echo 'calulate send rate'
echo -n 'max_rate=' > $RF
awk -F ',' '{print $1}' $F | sort -gu | tr -s '\n' | awk 'END {print}' | awk '{print$1"Mbps"}'>> $RF 
echo -n 'min_rate=' >> $RF
awk -F ',' '{print $1}' $F | sort -gur | tr -s '\n'| awk 'END {print}' | awk '{print$1"Mbps"}' >> $RF
awk -F ',' '{print $1}' $F | tr -s '\n' |awk '{sum +=$1}END {print"avgRate=", sum/NR}' | awk '{print$0"Mbps"}' >> $RF
echo 'calculate RTT'
echo -n 'max_RTT=' >> $RF
awk -F ',' '{print $2}' $F | sort -gu | tr -s '\n'| awk 'END {print}' | awk '{print$1"ms"}' >> $RF
echo -n 'min_RTT=' >> $RF
awk -F ',' '{print $2}' $F | sort -gur | tr -s '\n' |awk 'END {print}' | awk '{print$1"ms"}' >> $RF
awk -F ',' '{print $2}' $F | tr -s '\n'|awk '{sum +=$1}END {print"avgRTT=", sum/NR}' | awk '{print$0"ms"}' >> $RF
echo 'calculate pkt sent per second'
echo -n 'max_pkt_sent=' >> $RF
awk -F ',' '{print $7}' $F | sort -gu | tr -s '\n' | awk 'END {print}' | awk '{print$1"pkt"}' >> $RF
echo -n 'min_pkt_sent=' >> $RF
awk -F ',' '{print $7}' $F | sort -gur | tr -s '\n' | awk 'END {print}' | awk '{print$1"pkt"}' >> $RF
awk -F ',' '{print $7}' $F | tr -s '\n' |awk '{sum +=$1}END {print"avgPktSent=", sum/NR}' | awk '{print$0"pkt"}' >> $RF
echo 'calculate pkt loss'
echo -n 'max_pkt_snt_loss_rate=' >> $RF
awk -F ',' '{print $9*100/($7+1)}' $F | sort -gu | tr -s '\n' | awk 'END {print}' | awk '{print$1"%"}' >> $RF
echo -n 'min_pkt_snt_loss_rate=' >> $RF
awk -F ',' '{print $9*100/($7+1)}' $F | sort -gur | tr -s '\n' | awk 'END {print}' | awk '{print$1"%"}' >> $RF
echo 'calculate pkt loss percentile'
awk -F ',' '{print $9*100/($7+1)}' $F | sort -g |tr -s '\n' > tmp
#a=`awk -F ',' '{print $9*100/($7+1)}' $F | sort -g |tr -s '\n'`
a=`awk END'{print NR}' tmp`
#echo $a
b=$(echo "scale=4; $a*0.9"|bc)
c=$(echo "scale=4; $a*0.95"|bc)
d=$(echo "scale=4; $a*0.99"|bc)
#echo $b
echo -n 'p90_pkt_snt_loss_rate=' >> $RF
awk -v row="${b%.*}" 'NR==row{print $0"%"}' tmp >> $RF
echo -n 'p95_pkt_snt_loss_rate=' >> $RF
awk -v row="${c%.*}" 'NR==row{print $0"%"}' tmp >> $RF
echo -n 'p99_pkt_snt_loss_rate=' >> $RF
awk -v row="${d%.*}" 'NR==row{print $0"%"}' tmp >> $RF
echo 'del file tmp'
rm tmp
echo -e 'result as following:\n ******************'
cat $RF
echo ' ****************'
