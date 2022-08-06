Minishell - Project 42

Minihsell est une version tres minimaliste du fameux Bash. Il nous permeterra de ce deplacement dans le disque et d executer des fichiers binaires ainsi que des bultins (type cd, pwd, echo...)

L'idee et de recuperer une ligne de commande ecrite par l'utilisateur afin de l'executer.
Pour ce faire il existe plusieurs possibilite et donc algorithme comme tout programme.
Sur ce projet nous avons choisi de faire l'utilisation d'un arbre binaire.
L'arbre binaire va nous servir a effectuer ligne de commande dans un ordre precis en commancant l'execution de l'arbre en bas a gauche tout en remontant et en effectuant les partie droit a chaque noeud. Si dans la branche de droite contient d'autre branche nous allons donc repereter cette operation en y descendant tout en bas a gauche afin d'y remonter tout en effectuant la branche de droite a chaque noeud selon le type que nous verrons plus tard.
Pour construire l'arbre nous allons utiliser des priorite que nous allons potentiellement retrouver dans la ligne donne par l'utilisateur qui sont dans l'ordre:
1. &&
2. ||
3. |
4. le redirection
En cas de parenthese nous devons isoler celle-ci afin dans faire un bloque qui sera envoye et traiter dans l'arbre au moment venu.
Apres le parssing et la creation de l'arbre binaire nous passons a sont execution.

-- Partie a faire quand nous y serrons...

Le parssing:
Apre reception de la ligne de commande nous allons annalyser celle-ci et la retravailler afin de remplacer toutes demandes de variable(s) d'environement ou non par la variable en question;
Ex: $LANG deviens donc fr_FR.UTF-8
Si la variable n'existe pas nous effacerons simplement la demande.
Ex: "I want $TOTO!" deviens "I want !"

L'arbre binaire:
Commencons par la structure de cette arbre, rappelons qu'un arbre binaire contient un racine (le pere) et au maximum deux branche (2 fils) qui a leur tour peuvent devenir un racine d'un sous arbre et donc avoir egalement au maximum 2 branche et ainsi de suite.
Voici un exemple d'une potentielle commande decouper et integre dans un arbre binaire.

![Alt text](img/bt.png?raw=true "Title")
