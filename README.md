# INF442

## Objectifs :

- Peut-on prédire l'emploi du temps des lignes mieux que l'application et le site web RATP ? Peut-on déterminer des meilleurs itinéraires plus rapidement avec les données en temps réel ? (Spoiler : oui)
- Quand est-ce que les trains tombent le plus souvent en panne ? sont en retard ? sont pas la ?
- Est-ce que les lignes respectent leur fréquences ? Les passages sont-il espacés régulièrement ? Peut-on utiliser cela pour voyager plus rapidement ?
- Le retard des lignes de bus peut-il prédire le traffic ?
- Quelles sont les chances que le train soit en retard ou en avance ? (>1min)
- Position des trains/bus en live sur une map (si on a le temps)
- Faire faire demi tour à un train / sauter des stations


## Trucs à faire (concrètement) :
- prendre en main l'API RATP, quelles données à disposition, etc ?
- regarder la tête des données et les prétraiter (distanceS ???)
- lecteur de fichier cpp 
- dire pourquoi

## algorithmes utiles :
### Clustering : 
 - K-means (retard en fonction des autres données (lignes/heure/jours) )