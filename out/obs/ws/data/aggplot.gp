set term qt
set datafile separator ','
set xrange [0:100]
set yrange [0:40]
##plot for [i=0:999] i"agg.csv" using 1:2 w l
set key autotitle columnhead
plot "0agg.csv" every ::1 using 1:2

