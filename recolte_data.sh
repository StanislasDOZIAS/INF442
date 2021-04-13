#!/bin/bash

mkdir -p data
cd data



if [ ! -f "historical.csv" ]; then
curl http://www.lix.polytechnique.fr/Labo/Gleb.POGUDIN/files/RATP.txt --output historical.csv
fi

if [ ! -d "RATP_GTFS_FULL" ]; then
curl http://dataratp.download.opendatasoft.com/RATP_GTFS_FULL.zip --output RATP_GTFS_FULL.zip
unzip RATP_GTFS_FULL.zip -d RATP_GTFS_FULL
for f in $(find . -name "*.txt"); do 
    mv -- "$f" "RATP_GTFS_FULL/$(basename -- "$f" .txt).csv"
done
rm -rf RATP_GTFS_FULL.zip
fi


for i in 3 4 5 6 7 8 9; do
if [ ! -f "trafic-annuel-entrant-par-station-du-reseau-ferre-201$i.csv" ]; then
curl "https://data.ratp.fr/explore/dataset/trafic-annuel-entrant-par-station-du-reseau-ferre-201$i/download/?format=csv&timezone=Europe/Berlin&lang=fr&use_labels_for_header=true&csv_separator=%3B" --output trafic-annuel-entrant-par-station-du-reseau-ferre-201$i.csv
fi
done