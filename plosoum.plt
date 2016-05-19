#set term png font "arial,12"  size 340, 840
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

unset key
unset tics
unset border
unset colorbox
splot "./LastResult/Trail.txt"  notitle w pm3d

set output "Tudo.png"
set palette
plot "./LastResult/Plots/Trail.png" binary filetype=png with rgbimage, "./LastResult/AntPos.txt"  using (10*($1)+300):(10*($2)+300) w lp
set term x11