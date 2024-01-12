#!/bin/bash

# Nom du fichier
fichier="data/data.csv"

# Option -l
if [ "$1" == "-l" ]; then

start_time=$(time (

    # Récupérer la liste des trajets avec la distance totale parcourue
    trajets_distances=$(awk -F ';' '{trajets[$1]+=$5} END {for (trajet in trajets) print trajet, trajets[trajet]}' "$fichier" | sort -n -k1,1 | sort -t ' ' -k2,2nr | head -n 10)

    # Créer le fichier de données pour le graphique
    echo "$trajets_distances" > temp/datal.txt

    # Créer le script GNU Plot
    cat > temp/HistogrammeBuilderL.gp <<EOL
set terminal pngcairo enhanced font "arial,10" size 800,600
set output "images/DistanceParTrajet.png"

set title "Distance totale par trajet"
set xlabel "Identifiant du trajet"
set ylabel "Distance totale (km)"
set style data histogram
set style fill solid border rgb "black"
plot 'temp/datal.txt' using 2:xtic(1) with boxes
EOL

    # Exécuter le script GNU Plot
    gnuplot temp/HistogrammeBuilderL.gp

    echo "Fichier de données et graphique générés : datal.txt, DistanceParTrajet.png"

) 2>&1 >/dev/null)
echo "Le temps d'exécution est $start_time"

else
    echo "Option non reconnue. Utilisez -l pour le traitement demandé."
fi
