#!/bin/bash

# Nom du fichier
fichier="data/data.csv"

# Option -d2
if [ "$1" == "-d2" ]; then

start_time=$(time (

    # Récupérer la liste des conducteurs avec la distance totale parcourue par chacun d'entre eux
    conducteurs_distance=$(awk -F ';' '{conducteurs[$6]+=$5} END {for (conducteur in conducteurs) print conducteur, conducteurs[conducteur]}' "$fichier" | sort -t ' ' -k3,3nr | head -n 10)

    # Créer le fichier de données pour le graphique
    echo "$conducteurs_distance" > temp/datad2.txt

    # Créer le script GNU Plot
    cat > temp/HistogrammeBuilderD2.gp <<EOL
set terminal pngcairo enhanced font "arial,10" size 1300,600
set output "images/DistanceParConducteur.png"

set title "Distance totale parcourue par conducteur"
set xlabel "Distance totale parcourue"
set ylabel "Conducteurs"
set ytics nomirror rotate by -45
set style data histogram
set style fill solid border rgb "black"
plot 'temp/datad2.txt' using 0:3:xticlabels(stringcolumn(1).' '.stringcolumn(2)) with boxes
EOL

    # Exécuter le script GNU Plot
    gnuplot temp/HistogrammeBuilderD2.gp

    echo "Fichier de données et graphique générés : datad2.txt, DistanceParConducteur.png"

) 2>&1 >/dev/null)
echo "Le temps d'exécution est $start_time"

else
    echo "Option non reconnue. Utilisez -d2 pour le traitement demandé."
fi
