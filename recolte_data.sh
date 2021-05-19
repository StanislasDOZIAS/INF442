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

if [ ! -e "train_set.csv" ] || [ ! -e "test_set.csv" ]; then
cd ..
python3 preprocessing.py 
fi

