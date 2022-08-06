# Minishell - Project 42

Minihsell est une version tres minimaliste du fameux Bash. Il nous permeterra de le deplacement dans le disque et executer des fichiers binaires ainsi que des bultins (type cd, pwd, echo...)

L'idee et de recuperer une ligne de commande ecrite par l'utilisateur afin de l'executer.
Pour ce faire il existe plusieurs possibilitees, et donc algorithmes, comme tout programme.
Pour ce projet nous avons choisi de faire l'utilisation d'un arbre binaire.
L'arbre binaire va nous servir a effectuer ligne de commande dans un ordre precis en commancant l'execution de l'arbre en bas a gauche tout en remontant et en effectuant les partie de droite a chaque noeud si il en existe. Si dans la branche de droite contient d'autre branche nous allons donc repereter cette operation en y descendant tout en bas a gauche afin d'y remonter tout en effectuant la branche de droite a chaque noeud selon le type que nous verrons plus tard.
Pour construire l'arbre nous allons utiliser des priorites que nous allons potentiellement retrouver dans la ligne donne par l'utilisateur qui ont pour priorites:
###### 1. &&
###### 2. ||
###### 3. |
###### 4. les redirections

En cas de __parenthese__ nous devons isoler celle-ci afin d'en faire un bloc qui sera envoye et traiter dans l'arbre, comme un nouvel arbre (execution) au moment venu.
Apres le parssing et la creation de l'arbre binaire nous passons a sont execution.

-- Partie a faire quand nous y serrons...

## La structure de l'arbre:

*EN COURS DE CREATION*

```
typedef struct s_tree
{
	int				type;
	int				code_err;
	struct t_cmd	*cmd;
	struct s_pipe	*pipe[2];
	struct tree		*left;
	struct tree		*right;
}	t_tree;
```

## Le parssing:
Apre reception de la ligne de commande nous allons annalyser celle-ci et la retravailler afin de remplacer toutes demandes de variable(s) d'environement ou non par la variable en question;
Ex: *$LANG deviens donc fr_FR.UTF-8*
Si la variable n'existe pas nous effacerons simplement la demande.
Ex: *"I want $TOTO!" deviens "I want !"*

##### L'arbre binaire:
Commencons par la structure de cette arbre, rappelons qu'un arbre binaire contient une racine *(le pere)* et au maximum deux branches *(2 fils)* qui a leur tour peuvent devenir une racine d'un sous arbre et donc avoir egalement au maximum 2 branches et ainsi de suite...

__Voici un exemple d'une potentielle commande decoupe et integre dans un arbre binaire.__

![Binary tree](img/bt.png?raw=true "Title")

Pour creer et remplir cette arbre nous allons avoir besoin de notre structure et effectuer une recurssive qui va utiliser la priorite pour ainsi effectuer les actions de remplissage.

Voici un algo survole pour le remplissage de l'arbre:
ne pas oublier que ***les parenthese doivent etre considerer comme un bloc.***
```
start

if block is "&&"
  work <- take line before &&
  line <- *line after &&
  create node type && and afiliate to parent if exist
  recall this function argv (work, node->left)
if block is ||
  work <- take line before ||
  line <- *line after ||
  create node type || and afiliate to parent if exist
  recall this function argv (work, node->left)
if *line egale (
  work <- take block until the right parenthesis
  recall this fonction argv (work, thisnode->left)
if block is |
  work <- take line before |
  line <- *line after |
  create node type | and afiliate to parent if exist
  recall this function argv (work, node->left)
if block is redicrection (<, >, >>)
  create a node type leaf and afiliate to parent if exist
if line is not empty
  recall this function argv (line, node->right)

end
```
