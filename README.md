
#nom = in ou char ou combinaison des 2.
#room (int, char...) X Y.
#tube (nom1-nom2).
#com : #start .. #end.

#pas assez de donne : erreur ou premiere line non conforme ou vide = erreur.

#sortie standard :
 - nbre fourmis
 - salles
 - tubes

L1-2 = Ln_fourmi-noms_salles

#le cout = nbre chemins de start jusau'a current + le cout moyen (heuristique, < ou egal au cout de begin a current). Cout moyen = distance estime entre current et le point d'arrive, doit toujours etre inferieur ou
egal au cout reel pour atteindre le point d'arrive.

f(n)=g(n)+h(n)

f(n) = the evaluation function.
g(n) = the cost from the start node to the current node
h(n) = estimated cost from current node to goal.

#parsing : creer des nodes avec les donnes des tubes, et sort ces nodes.
#struct avec les coords, 
#

//une salle ne commencera jamais par le caractère L ou le caractère #.

// algo : deplace une fourmi, trouve le meilleur chemin : pas une autre fourmi a cette intersection et le +
// court chemin (nbre de deplacement nescessaire entre begin et end), sinon retour a l'intersection ou tout
// est ok : + court chemin / pas deja une fourmi.

// meme Y ou X pour les liens
// diff 1:(x + y), 2:(x + y). Si diff 1 > diff 2, diff 1 est le suivant.

// (4, 0) -> (2, 2) -> (0, 4).
		  -> (4, 2) -> (8, 2).

// (4, 2) -> (8, 2).
		  -> (4, 4).

// ceux qui ont les meme liens = salle. 
