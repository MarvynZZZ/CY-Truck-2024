#!/bin/bash

./trips_program > output.txt

# Générer le fichier de données pour le graphique
awk '{print $1, $3, $5}' output.txt > data.txt

# Générer le script gnuplot
echo 'set terminal png' > script.gp
echo 'set output "trips_histogram.png"' >> script.gp
echo 'set boxwidth 0.5' >> script.gp
echo 'set style fill solid' >> script.gp
echo 'set ytics 1' >> script.gp
echo 'set xlabel "Towns"' >> script.gp
echo 'set ylabel "Number of Trips"' >> script.gp
echo 'set title "Top 10 Towns with the Most Trips"' >> script.gp
echo 'plot "data.txt" using 2:xtic(1) title "Total Trips" with boxes, "" using 3 title "Depart Trips" with boxes' >> script.gp

# Exécuter le script gnuplot
gnuplot script.gp

# Nettoyer les fichiers temporaires
rm output.txt data.txt script.gp
