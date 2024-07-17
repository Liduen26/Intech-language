# Projet théorie de la compilation

## Lancement du programme :

    Ctrl+maj+B avec VsCode

    sinon :
    
    $ gcc main.c lexer.c ast.c parser.c sym_table.c ressources/buffer.c ressources/utils.c writer.c -o a 
    $ a.exe

## Autre :

### Membres de l'équipe :

    Amaury Pinheiro et Raphaël Orieux 

### Langage source de notre compilateur :

    IntechLanguage

### Langage cible de notre compilateur :

    Notre compilateur va faire un fichier TypeScript (.ts)

### Langage dans lequel notre compilateur est implémenté : 

    Nous avons réalisé notre compilateur en C (.c)

### Liste précise et exhaustive des fonctionnalités que l'on a réussi à implémenter à notre compilateur et qui sont fonctionnelles : 

- opérateurs binaires
- appel de fonction
- définition de fonction
- déclaration de variable / initialisation
- affectation 
- branchement conditionnels (if / else)
- instruction composée
- retourner
- variable
- entier

### Remarques

    Pour les if, la logique du "else if" est théoriquement implémentée dans le parser, mais nous n'avons pas eu le temps de le tester/debuger. 
    Même chose pour le while.

    On peut activer ou désactiver une fonctionnalité de tracage pour savoir ce que fait le programme dans utils.c. 

    Une semaine pour faire le projet était très court :( 
    Malgrès cela, c'était un projet très intéressant et challengeant :)

    Comme on a commencé par écrire tout notre parser en Pseudo-code pour faciliter la réflexion, on a laissé le pseudo-code visible dans les fonctions. 