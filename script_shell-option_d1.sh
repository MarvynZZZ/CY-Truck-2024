#!/bin/bash

# Nom du fichier
fichier="data/data.csv"

# Option -d1
if [ "$1" == "-d1" ]; then

start_time=$(time (

    # Récupérer la liste des conducteurs avec le nombre de trajets
    conducteurs_trajets=$(awk -F ';' '{if (!seen[$1,$6]++) conducteurs[$6]++} END {for (conducteur in conducteurs) print conducteur, conducteurs[conducteur]}' "$fichier" | sort -t ' ' -k3,3nr | head -n 10)

    # Créer le fichier de données pour le graphique
    echo "$conducteurs_trajets" > temp/datad1.txt

    # Créer le script GNU Plot
    cat > temp/HistogrammeBuilderD1.gp <<EOL
set terminal pngcairo enhanced font "arial,10" size 1300,600
set output "images/TrajetsParConducteur.png"

set title "Nombre de trajets par conducteur"
set xlabel "Nombre de trajets"
set ylabel "Conducteurs"
set ytics nomirror rotate by -45
set style data histogram
set style fill solid border rgb "black"
plot 'temp/datad1.txt' using 0:3:xticlabels(stringcolumn(1).' '.stringcolumn(2)) with boxes
EOL

    # Exécuter le script GNU Plot
    gnuplot temp/HistogrammeBuilderD1.gp

    echo "Fichier de données et graphique générés : datad1.txt, TrajetsParConducteur.png"

) 2>&1 >/dev/null)
echo "Le temps d'exécution est $start_time"

else
    echo "Option non reconnue. Utilisez -d1 pour le traitement demandé."
fi
