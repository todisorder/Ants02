#set parametric; plot "1/AntPos.txt" w l, "1.5/AntPos.txt" w l, "2/AntPos.txt" w l, "2.5/AntPos.txt" w l, "3/AntPos.txt" w l,  "3.5/AntPos.txt" w l,  "4/AntPos.txt" w l
#unset parametric; plot "1/AntPos.txt" using 2 w l, "1.5/AntPos.txt" using 2 w l, "2/AntPos.txt" using 2 w l, "2.5/AntPos.txt" using 2 w l, "3/AntPos.txt" using 2 w l,  "3.5/AntPos.txt" using 2 w l,  "4/AntPos.txt" using 2 w l
#unset parametric; plot "1/AntVelRadius.txt" w l, "1.5/AntVelRadius.txt" w l, "2/AntVelRadius.txt" w l, "2.5/AntVelRadius.txt" w l, "3/AntVelRadius.txt" w l,  "3.5/AntVelRadius.txt" w l,  "4/AntVelRadius.txt" w l

#set parametric; plot "popo/AntPos.txt" w l #, "popo3/AntPos.txt" w l

#http://stackoverflow.com/questions/33774180/transparent-background-picture-and-the-color-of-certain-points

# De:::::
#   http://www.gnuplotting.org/code/zoom_plot.gnu
#!/usr/bin/gnuplot
#
# Using multiplot to include a zoomed in version into your plot
#
# AUTHOR: Hagen Wierstorf

#reset
#set term x11
## wxt
##set terminal wxt size 350,262 enhanced font 'Verdana,10' persist
## png
##set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
##set output 'zoom_plot.png'
#
## color definitions
#set style line 2  lc rgb '#0025ad' lt 1 lw 2
#set style line 3  lc rgb '#0042ad' lt 1 lw 2
#set style line 4  lc rgb '#0060ad' lt 1 lw 2
#set style line 5  lc rgb '#007cad' lt 1 lw 2
#set style line 6  lc rgb '#0099ad' lt 1 lw 2
#set style line 7  lc rgb '#00ada4' lt 1 lw 2
#set style line 8  lc rgb '#00ad88' lt 1 lw 2
#set style line 9  lc rgb '#00ad6b' lt 1 lw 2
#set style line 10 lc rgb '#00ad4e' lt 1 lw 2
#set style line 11 lc rgb '#00ad31' lt 1 lw 2
#set style line 12 lc rgb '#00ad14' lt 1 lw 2
#set style line 13 lc rgb '#09ad00' lt 1 lw 2
#
#unset key
#
## Axes
#set style line 101 lc rgb '#808080' lt 1
#set border 3 back ls 101
##set tics nomirror out scale 0.75
## Grid
##set style line 102 lc rgb'#808080' lt 0 lw 1
##set grid back ls 102
#
##set format x '%gÂ°'
##set xlabel 'azimuth angle'
##set ylabel 'time / ms' offset 1,0
#
##set xrange [-90:0]
##set yrange [0:0.9]
#
##set label 1 'interaural time differences' at -15,0.85 front right
##set label 2 'f = 236Hz' at -28,0.45 textcolor ls 2
##set label 3 'f = 1296Hz' at -12,0.05 right textcolor ls 13
#
#set multiplot
#
## === large plot ===
## set white rectangle as a place holder for the small plot
##set object 1 rect from -0,0.03 to 1.,1.
##set object 1 rect fc rgb 'white' fillstyle solid 0.0 noborder
##set parametric; plot for [n=2:13] 'popo/AntPos.txt' u ($1)+n  w lines ls n
#set view map
#set grid
##set view 0,90,.6,1
#set isosamples 100, 100
#unset surface
#set style data pm3d
#set style function pm3d
#set ticslevel 0
#set pm3d implicit at b
#set palette negative nops_allcF maxcolors 0 gamma 1.5 gray
#splot "popo/Trail.txt"  notitle w pm3d
#
##plot '-' w p ps 3
##0 0
##e
#
#
## === small plot ===
#do for [n=2:13] { set style line n lw 1 }
#set origin .31,.325
#set size 0.45,0.4
#set size ratio -1
##set xrange [-10:0]
##set yrange [0:0.1]
#set grid
##unset grid
#unset colorbox
##unset xtics
#unset border
#unset xlabel
#unset ylabel
#unset label
##unset object 1
##set tics scale 0.5 front
##set xtics 10 offset 0,0.5
##set ytics 0.1 offset 0.5,0
#set parametric; plot  'popo/Antpos.txt'  w lines ls n
#
#unset multiplot
reset
set term png size 600,600
set palette gray negative
set output "Trail.png"
set size ratio -1
set view map
set lmargin at screen 0
set rmargin at screen 1
set bmargin at screen 0
set tmargin at screen 1
#There shold be no key tics and border
unset key
unset tics
unset border
unset colorbox
splot "popo/Trail.txt"  notitle w pm3d
#set term x11
set output "graph.png"
#splot "popo/Trail.txt"  notitle w pm3d
set palette 
plot "Trail.png" binary filetype=png with rgbimage, "popo/Antpos.txt"  using (10*($1)+300):(10*($2)+300) w l
set term x11
reset
