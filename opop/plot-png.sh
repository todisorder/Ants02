#File plot-png.sh
touch plots.plt
rm plots.plt
touch plots.plt;
touch ./Plots/foo
rm ./Plots/*
mv ./Resultados/* . &&
echo "reset" >> plots.plt
echo "set parametric" >> plots.plt
echo "Generating gnuplot source code..."

echo "set term png font \"arial,12\"  size 240, 840
#unset xtics
#unset ytics
set title ''
set output \"./Plots/AntPos.png\"
" >> plots.plt
echo "plot \"AntPos.txt"  >> plots.plt;

#echo "Done"
echo "set term x11" >> plots.plt
echo "Plotting..."
gnuplot plots.plt;
#echo "Done"
#echo "Building gifs..."
#convert -delay 2 -loop 0 ./Plots/U_1*.png ./Plots/myanimationU_1.gif;
#convert -delay 2 -loop 0 ./Plots/U_2*.png ./Plots/myanimationU_2.gif;
#convert -delay 2 -loop 0 ./Plots/U_food_c*.png ./Plots/myanimationU_food_conc.gif;
#convert -delay 2 -loop 0 ./Plots/U_food_p*.png ./Plots/myanimationU_food_phero.gif;
#echo "Done"

#echo "Building movs..."
#convert  -delay 5 ./Plots/U_1*.png ./Plots/myanimationU_1.mov
#convert  -delay 5 ./Plots/U_2*.png ./Plots/myanimationU_2.mov
#convert  -delay 5 ./Plots/U_food_p*.png ./Plots/myanimationU_food_phero.mov
#echo "Done"
echo "Copying files..."
rm ./Resultados/*
#mv Pr* ./Resultados
#mv Vel_* ./Resultados
#rm ~/Dropbox/Formigas/*.mov
#cp ./Plots/*.mov ~/Dropbox/Formigas/
#cp ./Plots/*.mov ~/"Google Drive/"
#echo "Done"
echo "Finished!"
