make &&
touch ./U_SoPaNaoChatearComErrosDoRM.txt
rm U_*;

echo "Results folder name:"
read Folder
mkdir "$Folder"
cp formigas13  "$Folder"
cp plot-png.sh  "$Folder"
cp plots-Mass.plt  "$Folder"
cd "$Folder"

./formigas13 &&
mkdir Plots
mkdir Resultados
sh plot-png.sh &&
gnuplot plots-Mass.plt
cp ../LogsLast.txt .


#cd "$Folder"
