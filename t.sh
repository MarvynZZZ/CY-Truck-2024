#!/bin/bash

# Verify if Gnuplot Is installed
if ! command -v gnuplot &> /dev/null; then
    echo "Gnuplot is not installed, please install it and retry"
    exit 1
fi

# Compile and execute the c program to sort the data
gcc -o t t.c && ./t

# Name of the CSV file
csv_file="temp/tempT.csv"

# Name of the output file 
output_file="histogramme_regroupe.png"

# Command Gnuplot to creat the graph
gnuplot <<EOF
set terminal pngcairo enhanced font 'arial,10' size 800,600
set output "$output_file"
set style data histograms
set style histogram cluster gap 1
set style fill solid border -1
set xlabel "Villes"
set ylabel "Nombre de Trajets"
set xtics rotate by -45
set key autotitle columnhead
plot '$csv_file' using 2:xtic(1) title "Nombre de Trajets Total", '' using 3 title "Nombre de Départs"
EOF

echo "Graphique généré : $output_file"
